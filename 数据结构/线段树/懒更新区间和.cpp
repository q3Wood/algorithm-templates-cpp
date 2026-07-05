#include <vector>
#include <iostream>
using namespace std;

class SegmentTree {
private:
    long long n;
    vector<long long> tree; 
    vector<long long> lazy; 

    
    void push_up(int p) {
        tree[p] = tree[p * 2] + tree[p * 2 + 1]; // 求和
        // 如果是求最大值: tree[p] = max(tree[p*2], tree[p*2+1]);
    }

    void push_down(int p, int l, int r) {
        if (lazy[p] != 0) {
            int mid = l + (r - l) / 2;
            
            tree[p * 2] += lazy[p] * (mid - l + 1); // 区间和要乘长度
            lazy[p * 2] += lazy[p];
            
            tree[p * 2 + 1] += lazy[p] * (r - mid);
            lazy[p * 2 + 1] += lazy[p];
            
            lazy[p] = 0;
        }
    }

    void build(const vector<long long>& a, int p, int l, int r) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, p * 2, l, mid);
        build(a, p * 2 + 1, mid + 1, r);
        push_up(p);
    }

    void update(int L, int R, long long v, int p, int l, int r) {
        if (L <= l && r <= R) {
            tree[p] += v * (r - l + 1); // 区间和更新
            lazy[p] += v;
            return;
        }
        push_down(p, l, r); // 访问子节点前必须下放标记
        int mid = l + (r - l) / 2;
        if (L <= mid) update(L, R, v, p * 2, l, mid);
        if (R > mid) update(L, R, v, p * 2 + 1, mid + 1, r);
        push_up(p);
    }

    long long query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) return tree[p];
        push_down(p, l, r); // 访问子节点前必须下放标记
        int mid = l + (r - l) / 2;
        long long res = 0;
        if (L <= mid) res += query(L, R, p * 2, l, mid);
        if (R > mid) res += query(L, R, p * 2 + 1, mid + 1, r);
        return res;
    }

public:
    SegmentTree(const vector<long long>& a) {
        n = a.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        // 注意：外部数组通常 0-indexed，线段树内部递归通常用 0~n-1 表示范围
        build(a, 1, 0, n - 1); 
    }

    // 接口：区间 [L, R] 加上 v
    void update(int L, int R, long long v) {
        update(L, R, v, 1, 0, n - 1);
    }

    // 接口：查询 [L, R] 的和
    long long query(int L, int R) {
        return query(L, R, 1, 0, n - 1);
    }
};