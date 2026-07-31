#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 100005;
struct Edge { int to, w; };
vector<Edge> adj[N];
int dist[N];
int max_dist = -1, endpoint = -1;

// 这里的 fa 为了防止走回头路
void dfs(int u, int fa, int d) {
    if (d > max_dist) {
        max_dist = d;
        endpoint = u;
    }
    for (auto &e : adj[u]) {
        if (e.to != fa) {
            dfs(e.to, u, d + e.w);
        }
    }
}

int main() {
    int n; 
    cin >> n;
    // 建图... (假设输入 u v w)
    for(int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // 第一次 DFS：找端点 P
    max_dist = -1;
    dfs(1, -1, 0);
    int P = endpoint;

    // 第二次 DFS：从 P 出发找端点 Q
    max_dist = -1;
    dfs(P, -1, 0);
    int Q = endpoint;

    cout << max_dist << endl; // 直径长度
    return 0;
}