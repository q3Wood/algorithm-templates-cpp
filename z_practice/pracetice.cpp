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
    string s;
    int cnt;
    bool operator<(const Node& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m ; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } 
    vector<int> sz(n + 1, 1), dp(n + 1);

    auto dfs1 = [&](auto&& dfs1, int u, int f) -> void {
        for (int v : adj[u]) {
            if (v == f) continue;
            dfs1(dfs1, v, u);
            sz[u] += sz[v];
            dp[u] += dp[v] + sz[v];
        }
    };

    auto dfs2 = [&](auto&& dfs2, int u, int f) -> void {
        for (int v : adj[u]) {
            if (v == f) continue;
            dp[v] = dp[u] - dp[v] - sz[v] + dp[v] + n - sz[v];
            dfs2(dfs2, v, u);
        }
    };
    dfs1(dfs1, 1, 0);
    dfs2(dfs2, 1, 0);
    vector<int> a;
    int mi = INF;
    for (int i = 1; i <= n; i++) {
        if (dp[i] < mi) {
            a.clear();
            a.push_back(i);
            mi = dp[i];
        } else if (dp[i] == mi) {
            a.push_back(i);
        }
    }
    for (int x : a) {
        cout << x << ' ';
    }

    
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
