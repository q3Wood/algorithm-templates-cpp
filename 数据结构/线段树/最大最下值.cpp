#include <vector>
#include <iostream>
#include <algorithm> // 包含 max 和 min
#include <climits>   // 包含 LLONG_MIN 和 LLONG_MAX

using namespace std;

class SegmentTree {
private:
    int n;
    vector<long long> tree_max; // 存区间最大值
    vector<long long> tree_min; // 存区间最小值
    vector<long long> lazy;     // 存懒标记（区间加法）

    // 向上更新：同时求最大和最小
    void push_up(int p) {
        tree_max[p] = max(tree_max[p * 2], tree_max[p * 2 + 1]); 
        tree_min[p] = min(tree_min[p * 2], tree_min[p * 2 + 1]); 
    }

    // 向下传递：懒标记下放
    void push_down(int p, int l, int r) {
        if (lazy[p] != 0) {
            // 左孩子：最大值和最小值都加上 lazy[p]
            tree_max[p * 2] += lazy[p]; 
            tree_min[p * 2] += lazy[p];
            lazy[p * 2] += lazy[p];
            
            // 右孩子：最大值和最小值都加上 lazy[p]
            tree_max[p * 2 + 1] += lazy[p];
            tree_min[p * 2 + 1] += lazy[p];
            lazy[p * 2 + 1] += lazy[p];
            
            lazy[p] = 0;
        }
    }

    void build(const vector<int>& a, int p, int l, int r) {
        if (l == r) {
            tree_max[p] = a[l];
            tree_min[p] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, p * 2, l, mid);
        build(a, p * 2 + 1, mid + 1, r);
        push_up(p);
    }

    void update(int L, int R, int v, int p, int l, int r) {
        if (L <= l && r <= R) {
            // 区间被完全覆盖时，最大和最小同时加上 v
            tree_max[p] += v; 
            tree_min[p] += v;
            lazy[p] += v;
            return;
        }
        push_down(p, l, r);
        int mid = l + (r - l) / 2;
        if (L <= mid) update(L, R, v, p * 2, l, mid);
        if (R > mid) update(L, R, v, p * 2 + 1, mid + 1, r);
        push_up(p);
    }

    // 查询返回 pair：first 为最大值，second 为最小值
    pair<long long, long long> query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) return {tree_max[p], tree_min[p]};
        push_down(p, l, r);
        int mid = l + (r - l) / 2;
        
        // 初始化极小值和极大值
        long long res_max = LLONG_MIN; 
        long long res_min = LLONG_MAX;
        
        if (L <= mid) {
            auto left_res = query(L, R, p * 2, l, mid);
            res_max = max(res_max, left_res.first);
            res_min = min(res_min, left_res.second);
        }
        if (R > mid) {
            auto right_res = query(L, R, p * 2 + 1, mid + 1, r);
            res_max = max(res_max, right_res.first);
            res_min = min(res_min, right_res.second);
        }
        return {res_max, res_min};
    }

public:
    SegmentTree(const vector<int>& a) {
        n = a.size();
        tree_max.resize(4 * n);
        tree_min.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(a, 1, 0, n - 1); 
    }

    void update(int L, int R, int v) {
        update(L, R, v, 1, 0, n - 1);
    }

    // 接口：返回 {最大值, 最小值}
    pair<int, int> query(int L, int R) {
        return query(L, R, 1, 0, n - 1);
    }
};