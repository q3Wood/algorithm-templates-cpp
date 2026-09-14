#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 4e18;

struct Edge {
    int to;
    long long d, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    if (n == 1) {
        cout << "0 0\n";
        return 0;
    }

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long d, r;
        cin >> u >> v >> d >> r;
        adj[u].push_back({v, d, r});
    }

    // ========== 阶段 1：只求距离的最短路 ==========
    vector<long long> dist_d(n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq1;

    dist_d[1] = 0;
    pq1.push({0, 1});

    while (!pq1.empty()) {
        auto [d, u] = pq1.top();
        pq1.pop();

        if (d > dist_d[u]) continue;

        for (const auto& edge : adj[u]) {
            if (dist_d[u] + edge.d < dist_d[edge.to]) {
                dist_d[edge.to] = dist_d[u] + edge.d;
                pq1.push({dist_d[edge.to], edge.to});
            }
        }
    }

    // 无法到达终点
    if (dist_d[n] == INF) {
        cout << "-1 -1\n";
        return 0;
    }

    // ========== 阶段 2：在最短路子图上求最小风险 ==========
    vector<long long> dist_r(n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq2;

    dist_r[1] = 0;
    pq2.push({0, 1});

    while (!pq2.empty()) {
        auto [r, u] = pq2.top();
        pq2.pop();

        if (r > dist_r[u]) continue;

        for (const auto& edge : adj[u]) {
            // 仅当这条边处于第一关键字的最短路上时才允许通行
            if (dist_d[u] + edge.d == dist_d[edge.to]) {
                if (dist_r[u] + edge.r < dist_r[edge.to]) {
                    dist_r[edge.to] = dist_r[u] + edge.r;
                    pq2.push({dist_r[edge.to], edge.to});
                }
            }
        }
    }

    cout << dist_d[n] << " " << dist_r[n] << "\n";

    return 0;
}