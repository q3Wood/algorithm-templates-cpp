#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Edge {
    int to, w;
};
vector<Edge> adj[N];
int ans = 0; // 全局最大直径
int d1[N], d2[N]; // d1: 最长链, d2: 次长链

void dfs_dp(int u, int fa) {
    d1[u] = d2[u] = 0;
    for (auto &e : adj[u]) {
        if (e.to == fa) continue;
        dfs_dp(e.to, u);
        
        int val = d1[e.to] + e.w;
        if (val > d1[u]) {
            d2[u] = d1[u];
            d1[u] = val;
        } else if (val > d2[u]) {
            d2[u] = val;
        }
    }
    ans = max(ans, d1[u] + d2[u]);
}