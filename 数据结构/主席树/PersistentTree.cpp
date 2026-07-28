#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ====================================================================
// 工具类：泛型离散化器 (Discretizer)
// 作用：将任何大范围的值映射到 1 ~ N 的紧凑区间，处理主席树值域过大的必备工具
// ====================================================================
template<typename T>
struct Discretizer {
    vector<T> vals;

    // 新增：预分配内存空间，避免 vector 动态扩容带来的性能损耗
    Discretizer(size_t n = 0) { if (n > 0) vals.reserve(n); }

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
// 核心数据结构：主席树 / 可持久化权值线段树 (Persistent Segment Tree)
// 作用：极其稳定、安全的版本控制线段树
// ====================================================================
struct PersistentTree {
    struct Node {
        int l, r;  // 左右子节点的索引 (在 tr 数组中的下标)
        int cnt;   // 维护的区间信息：这里是区间内元素的个数
    };

    vector<Node> tr;    // 动态节点池，彻底告别全局大数组
    vector<int> root;   // 存储每个版本的根节点索引

    // 构造函数预分配空间，提升性能
    // max_nodes: 预估的最大节点数，一般为 N * 40
    // max_versions: 预估的最大版本数，一般等于操作次数 N
    PersistentTree(int max_nodes = 0, int max_versions = 0) {
        if (max_nodes > 0) tr.reserve(max_nodes);
        if (max_versions > 0) root.reserve(max_versions + 1);
        
        // 塞入 0 号节点作为“空节点哨兵”，非常优雅地处理边界情况
        tr.push_back({0, 0, 0});
        root.push_back(0); 
    }

    // 核心：复制一个节点并返回新节点的索引
    int clone(int p) {
        tr.push_back(tr[p]);
        return tr.size() - 1; 
    }

    // 建空树 (值域 [l, r])
    // 很多时候权值线段树可以省略建空树，这里为了模板的完备性保留
    int build(int l, int r) {
        int p = tr.size();
        tr.push_back({0, 0, 0});
        if (l == r) return p;
        
        int mid = l + (r - l) / 2;
        tr[p].l = build(l, mid);
        tr[p].r = build(mid + 1, r);
        return p;
    }

    // 核心操作：在前一个版本 pre_root 的基础上，在值域 [l, r] 中插入离散化后的值 val_id
    // 返回新版本的根节点
    int insert(int pre, int l, int r, int val_id) {
        int p = clone(pre); // 沿途复制节点，这就是主席树的灵魂
        tr[p].cnt++;        // 当前路径上节点所管辖的区间元素数 + 1

        if (l == r) return p; // 抵达叶子节点

        int mid = l + (r - l) / 2;
        if (val_id <= mid) {
            tr[p].l = insert(tr[pre].l, l, mid, val_id);
        } else {
            tr[p].r = insert(tr[pre].r, mid + 1, r, val_id);
        }
        return p;
    }

    // 外部调用插入接口，自动记录新版本 root
    void add_version(int val_id, int val_domain_size) {
        int new_root = insert(root.back(), 1, val_domain_size, val_id);
        root.push_back(new_root);
    }

    // 核心查询：在版本 u (左端点 L-1) 和版本 v (右端点 R) 之间，查询 [l, r] 值域内的第 k 小
    int query_kth(int u, int v, int l, int r, int k) const {
        if (l == r) return l; // 找到了！返回具体的离散化 ID

        // 通过两个版本的节点计数相减，得到查询区间内的实际情况 (前缀和思想)
        int left_cnt = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        int mid = l + (r - l) / 2;

        if (left_cnt >= k) {
            // 第 k 小在左边
            return query_kth(tr[u].l, tr[v].l, l, mid, k);
        } else {
            // 第 k 小在右边，需要扣除左边的元素数量
            return query_kth(tr[u].r, tr[v].r, mid + 1, r, k - left_cnt);
        }
    }
};

// ====================================================================
// 测试及使用示例：如何用这个模板解决上面的题目 (静态区间中位数)
// ====================================================================
int main() {
    // 提速必备
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    Discretizer<int> d(n); // 实例化我们的离散化工具

    // 1. 读取数据并收集到离散化器中
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        d.add(a[i]);
    }

    // 2. 执行离散化
    d.build();
    int m = d.size(); // 得到值域的范围 1 ~ m

    // 3. 实例化主席树 (预分配内存: max_nodes 预估 N*40，max_versions 预估 N)
    PersistentTree pt(n * 40, n);
    
    // 初始化版本 0 为一棵值域为 1~m 的空树 (权值线段树可以省略这一步)
    pt.root[0] = pt.build(1, m);

    // 4. 构建所有历史版本
    for (int i = 1; i <= n; i++) {
        int id = d.get_id(a[i]);
        // pt.add_version() 会自动在前一个版本基础上插入，并保存新版本
        pt.add_version(id, m);
    }

    // 5. 应对查询
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        
        int len = r - l + 1;
        int k = (len + 1) / 2; // 中位数就是第 (len+1)/2 小

        // 核心查询逻辑：拿出第 R 个版本，减去第 L-1 个版本，找第 k 小
        int ans_id = pt.query_kth(pt.root[l - 1], pt.root[r], 1, m, k);
        
        // 查出来的是 ID，别忘了用工具类换回真实值
        cout << d.get_val(ans_id) << "\n";
    }

    return 0;
}
