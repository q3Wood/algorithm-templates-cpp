#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 使用 128 位大整数避免进位溢出
typedef __int128_t int128;

const int128 K = (int128)1000000000000000LL; // K = 10^15 > 2 * 10^14
const int128 INF128 = ((int128)1 << 126) - 1;

struct Edge {
    int to;
    int128 weight;
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
        // 合并权值
        int128 w = (int128)d * K + r;
        adj[u].push_back({v, w});
    }

    vector<int128> dist(n + 1, INF128);
    // 小顶堆存 (综合权值, 节点编号)
    priority_queue<pair<int128, int>, vector<pair<int128, int>>, greater<pair<int128, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (w > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }

    if (dist[n] == INF128) {
        cout << "-1 -1\n";
    } else {
        // 解码出总距离和总风险
        long long ans_d = (long long)(dist[n] / K);
        long long ans_r = (long long)(dist[n] % K);
        cout << ans_d << " " << ans_r << "\n";
    }

    return 0;
}