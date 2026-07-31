#include <vector>
using namespace std;
// 树状数组（Fenwick Tree）
class FenwickTree {
private:
    int n;
    vector<long long> tree;
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    int lowbit(int x) {
        return x & (-x);
    }
    void update(int idx, long long val) {
        while (idx <= n) {
            tree[idx] += val;
            idx += lowbit(idx); 
        }
    }

    long long q(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= lowbit(idx); 
        }
        return res;
    }

    long long query(int l, int r) {
        return q(r) - q(l - 1);
    }

};

