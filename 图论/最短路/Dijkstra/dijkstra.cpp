#include <bits/stdc++.h>
using namespace std;
using ll = long long; 

const ll INF = 1e18; 

struct Node {
    int u;
    long long w;
    bool operator<(const Node& other) const {
        return w > other.w;
    }
};
void Dijkstra(int n, int u, vector<vector<Node>>& g, vector<long long>& dist) {
    priority_queue<Node> p;
    dist[u] = 0;
    p.push({u, 0});
    while (!p.empty()) {
        Node o = p.top();
        p.pop();
        int v = o.u;
        if (o.w > dist[v]) continue;
        for (auto& e : g[v]) {
            int to = e.u;
            long long w = e.w;
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                p.push({to, dist[to]});
            }
        }
    }
}