#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

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
    cin >> n >> m;
    if (n == 1) {
        cout << "0 0" << endl;
        return 0;
    }

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long d, r;
        cin >> u >> v >> d >> r;
        adj[u].push_back({v, d, r});
    }

    vector<long long> dist_d(n + 1, INF);
    vector<long long> dist_r(n + 1, INF);
    priority_queue<tuple<long long, long long, int>, vector<tuple<long long, long long, int>>, greater<>> pq;
    dist_d[1] = 0;
    dist_r[1] = 0;
    pq.push({0, 0, 1});

    while (!pq.empty()) {
        auto [cur_d, cur_r, u] = pq.top();
        pq.pop();

        if (cur_d > dist_d[u] || (cur_d == dist_d[u] && cur_r > dist_r[u])) {
            continue;
        }

        for (const auto& e : adj[u]) {
            int v = e.to;
            long long new_d = cur_d + e.d;
            long long new_r = cur_r + e.r;
            if (new_d < dist_d[v] || (new_d == dist_d[v] && new_r < dist_r[v])) {
                dist_d[v] = new_d;
                dist_r[v] = new_r;
                pq.push({new_d, new_r, v});
            }
        }
    }

    if (dist_d[n] == INF) {
        cout << "-1 -1" << endl;
    } else {
        cout << dist_d[n] << " " << dist_r[n] << endl;
    }
    return 0;
}
