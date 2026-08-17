// 例题：https://ac.nowcoder.com/acm/contest/139206/F
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int l, r;
    int cnt[3];
    int lc, rc;
    int lazy;
};

class SegmentTree {
private:
    vector<Node> tr;
    int n;
    string s;

    void pushup(int u) {
        for (int i = 0; i < 3; i++) {
            tr[u].cnt[i] = tr[u << 1].cnt[i] + tr[u << 1 | 1].cnt[i];
            if (tr[u << 1].rc == i && tr[u << 1 | 1].lc == i) {
                tr[u].cnt[i]--;
            }
        }
        tr[u].lc = tr[u << 1].lc;
        tr[u].rc = tr[u << 1 | 1].rc;
    }

    void apply(int u, int add) {
        int temp[3];
        for (int i = 0; i < 3; i++) {
            temp[(i + add) % 3] = tr[u].cnt[i];
        }
        for (int i = 0; i < 3; i++) {
            tr[u].cnt[i] = temp[i];
        }
        tr[u].lazy = (tr[u].lazy + add) % 3;
        tr[u].lc = (tr[u].lc + add) % 3;
        tr[u].rc = (tr[u].rc + add) % 3;
    }

    void pushdown(int u) {
        if (tr[u].lazy) {
            apply(u << 1, tr[u].lazy);
            apply(u << 1 | 1, tr[u].lazy);
            tr[u].lazy = 0;
        }
    }

    void build(int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        tr[u].lazy = 0;
        if (l == r) {
            int val = s[l - 1] - 'A';
            for (int i = 0; i < 3; i++) {
                tr[u].cnt[i] = (i == val) ? 1 : 0;
            }
            tr[u].lc = val;
            tr[u].rc = val;
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void modify(int u, int l, int r, int add) {
        if (tr[u].l >= l && tr[u].r <= r) {
            apply(u, add);
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (l <= mid)
            modify(u << 1, l, r, add);
        if (r > mid)
            modify(u << 1 | 1, l, r, add);
        pushup(u);
    }
    int query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) {
            return tr[u].cnt[0];
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        int res = 0;
        if (l <= mid)
            res += query(u << 1, l, r);
        if (r > mid)
            res += query(u << 1 | 1, l, r);
        return res;
    }

public:
    SegmentTree(int size, string str) : n(size), s(str) {
        tr.resize(4 * n + 1); 
        build(1, 1, n);
    }

    void modify(int l, int r, int add) { modify(1, l, r, add); }

    int queryGlobalA() { return tr[1].cnt[0]; }
    int query(int l, int r) { return query(1, l, r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q))
        return 0;
    string s;
    cin >> s;

    // 不要传 n+1, s是0-based的，SegmentTree内部会处理1-based索引
    SegmentTree seg(n, s);

    while (q--) {
        int op, l, r;
        cin >> op;
        if (op == 2) {
            cout << seg.queryGlobalA() << "\n";
        } else {
            cin >> l >> r;
            seg.modify(l, r, 1);
        }
    }
    return 0;
}