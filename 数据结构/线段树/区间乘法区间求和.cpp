#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

class SegmentTree {
private:
    int n;
    vector<long long> tree; 
    vector<long long> lazy; 
    void push_up(int p) {
        tree[p] = (tree[p * 2] + tree[p * 2 + 1]) % MOD; 
    }
    void push_down(int p) {
        if (lazy[p] != 1) { 
            lazy[p * 2] = (lazy[p * 2] * lazy[p]) % MOD;
            lazy[p * 2 + 1] = (lazy[p * 2 + 1] * lazy[p]) % MOD;
            tree[p * 2] = (tree[p * 2] * lazy[p]) % MOD;
            tree[p * 2 + 1] = (tree[p * 2 + 1] * lazy[p]) % MOD;
            lazy[p] = 1;
        }
    }

    void update(int L, int R, long long val, int p, int l, int r) {
        if (L <= l && r <= R) { 
            tree[p] = (tree[p] * val) % MOD; 
            lazy[p] = (lazy[p] * val) % MOD; 
            return;
        }
        push_down(p);
        int mid = l + (r - l) / 2;
        if (L <= mid) update(L, R, val, p * 2, l, mid);
        if (R > mid) update(L, R, val, p * 2 + 1, mid + 1, r);
        push_up(p); 
    }
    long long query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) { 
            return tree[p];
        }
        push_down(p); 
        int mid = l + (r - l) / 2;
        long long res = 0;
        if (L <= mid) res = (res + query(L, R, p * 2, l, mid)) % MOD;
        if (R > mid) res = (res + query(L, R, p * 2 + 1, mid + 1, r)) % MOD;
        return res;
    }
    void build(vector<long long>& arr, int p, int l, int r) {
        if (l == r) {
            tree[p] = arr[l] % MOD;
            return;
        }
        int mid = l + (r - l) / 2;
        build(arr, p * 2, l, mid);
        build(arr, p * 2 + 1, mid + 1, r);
        push_up(p);
    }
public:
    SegmentTree(vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 1); 
        build(arr, 1, 0, n - 1);
    }
    void update(int L, int R, long long val) { // L, R 从 0 开始
        update(L, R, val, 1, 0, n - 1);
    }
    long long query(int L, int R) { // L, R 从 0 开始
        return query(L, R, 1, 0, n - 1);
    }
};
