// template Created by q3Wood on 2026/7/7
#include <bits/stdc++.h>

#define int long long
#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define i128 __int128
#define uint unsigned long long

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const int knight_moves[8][2] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                                {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int dirs[8][2] = {{0, 1}, {1, 0},  {0, -1}, {-1, 0},
                        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
struct Node {
    int x, y;
    bool operator<(const Node& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};

int n;
vector<int> c;
vector<int> w;
vector<vector<int>> g;

vector<int> d1, d2;
vector<int> c1;
vector<int> ans;

void update(int u, int val, int from) {
    if (val > d1[u]) {
        d2[u] = d1[u];
        d1[u] = val;
        c1[u] = from;
    } else if (val > d2[u]) {
        d2[u] = val;
    }
}

void dfs1(int u, int fa) {
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        int val = max(0LL, d1[v] + w[v]);
        update(u, val, v);
    }
}

void dfs2(int u, int fa) {
    for (int v : g[u]) {
        if (v == fa) continue;
        int other = (c1[u] == v ? d2[u] : d1[u]);
        int val = max(0LL, other + w[u]);
        update(v, val, u);
        dfs2(v, u);
    }
}
void solve() {
    cin >> n;
    c.assign(n + 1, 0);
    w.assign(n + 1, 0);
    g.assign(n + 1, vector<int>());
    d1.assign(n + 1, 0);
    d2.assign(n + 1, 0);
    c1.assign(n + 1, 0);
    ans.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        int res = w[i] + d1[i] + d2[i];
        ans[c[i]] = max(ans[c[i]], res);
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}