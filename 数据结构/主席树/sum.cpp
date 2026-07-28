#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ====================================================================
// 工具类：泛型离散化器 (Discretizer)
// ====================================================================
template<typename T>
struct Discretizer {
    vector<T> vals;

    void add(T x) { vals.push_back(x); }
    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }
    int get_id(T x) const { return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1; }
    T get_val(int id) const { return vals[id - 1]; }
    int size() const { return vals.size(); }
};

// ====================================================================
// 核心数据结构：主席树 / 可持久化权值线段树
// ====================================================================
struct PersistentTree {
    struct Node {
        int l, r;       // 左右子节点的索引
        int cnt;        // 区间内元素的个数
        long long sum;  // 新增：区间内元素的真实值总和 (注意用 long long)
    };

    vector<Node> tr;    
    vector<int> root;   

    PersistentTree(int max_nodes = 0, int max_versions = 0) {
        if (max_nodes > 0) tr.reserve(max_nodes);
        if (max_versions > 0) root.reserve(max_versions + 1);
        
        // 0号哨兵节点，sum 也要初始化为 0
        tr.push_back({0, 0, 0, 0LL});
        root.push_back(0); 
    }

    int clone(int p) {
        tr.push_back(tr[p]); // 这一步会自动把旧节点的 cnt 和 sum 都复制过来
        return tr.size() - 1; 
    }

    int build(int l, int r) {
        int p = tr.size();
        tr.push_back({0, 0, 0, 0LL});
        if (l == r) return p;
        
        int mid = l + (r - l) / 2;
        tr[p].l = build(l, mid);
        tr[p].r = build(mid + 1, r);
        return p;
    }

    // 新增：多传了一个 real_val 用于累加 sum
    int insert(int pre, int l, int r, int val_id, long long real_val) {
        int p = clone(pre); 
        tr[p].cnt++;               // 个数 + 1
        tr[p].sum += real_val;     // 新增：累加真实值

        if (l == r) return p; 

        int mid = l + (r - l) / 2;
        if (val_id <= mid) {
            tr[p].l = insert(tr[pre].l, l, mid, val_id, real_val);
        } else {
            tr[p].r = insert(tr[pre].r, mid + 1, r, val_id, real_val);
        }
        // 如果不是权值线段树，而是普通线段树，这里通常会写 push_up:
        // tr[p].sum = tr[tr[p].l].sum + tr[tr[p].r].sum;
        // 但在单点修改的权值线段树中，直接累加更高效。
        return p;
    }

    // 外部接口同步修改，接收真实值
    void add_version(int val_id, int val_domain_size, long long real_val) {
        int new_root = insert(root.back(), 1, val_domain_size, val_id, real_val);
        root.push_back(new_root);
    }

    // 经典查询 1：求第 k 小
    int query_kth(int u, int v, int l, int r, int k) const {
        if (l == r) return l; 

        int left_cnt = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        int mid = l + (r - l) / 2;

        if (left_cnt >= k) {
            return query_kth(tr[u].l, tr[v].l, l, mid, k);
        } else {
            return query_kth(tr[u].r, tr[v].r, mid + 1, r, k - left_cnt);
        }
    }

    // 扩展查询 2：求区间内前 k 小的元素的总和 (利用新增的 sum 变量)
    long long query_sum_kth(int u, int v, int l, int r, int k) const {
        if (l == r) {
            // 到达叶子节点，叶子节点可能包含多个相同的值，按比例取 sum
            // 或者直接用: k * 叶子节点代表的真实值 (这里假设离散化还原能在外部做，但为了模板自洽我们提供思路)
            // 这里为了严谨，我们用 cnt 计算单价，再乘以 k
            int count = tr[v].cnt - tr[u].cnt;
            long long total_sum = tr[v].sum - tr[u].sum;
            if (count == 0) return 0;
            return total_sum / count * k; 
        }

        int left_cnt = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        long long left_sum = tr[tr[v].l].sum - tr[tr[u].l].sum; // 左子树的真实值总和
        int mid = l + (r - l) / 2;

        if (left_cnt >= k) {
            // 前 k 小全部在左子树，只递归左边
            return query_sum_kth(tr[u].l, tr[v].l, l, mid, k);
        } else {
            // 左子树全部包括，并加上右子树中的前 (k - left_cnt) 小
            return left_sum + query_sum_kth(tr[u].r, tr[v].r, mid + 1, r, k - left_cnt);
        }
    }
};

// ====================================================================
// 测试示例
// ====================================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    Discretizer<int> d; 

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        d.add(a[i]);
    }

    d.build();
    int m = d.size(); 

    PersistentTree pt(n * 40, n);
    pt.root[0] = pt.build(1, m);

    for (int i = 1; i <= n; i++) {
        int id = d.get_id(a[i]);
        // 注意这里：除了传入 id，还把真实的 a[i] 传了进去，用于累加 sum
        pt.add_version(id, m, a[i]);
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        
        int len = r - l + 1;
        int k = (len + 1) / 2; 

        int ans_id = pt.query_kth(pt.root[l - 1], pt.root[r], 1, m, k);
        cout << "中位数为: " << d.get_val(ans_id) << "\n";

        // 你现在也可以调用新增的查询接口了！
        // cout << "区间前 " << k << " 小的数字之和为: " << pt.query_sum_kth(pt.root[l - 1], pt.root[r], 1, m, k) << "\n";
    }

    return 0;
}