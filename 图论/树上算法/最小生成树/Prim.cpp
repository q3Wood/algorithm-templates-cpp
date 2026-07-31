#include <bits/stdc++.h>
using namespace std;
const long long INF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
    int to, weight;
};
struct Node {
    int id, dist;
    bool operator<(const Node& other) const {
        return dist > other.dist;
    }
};
int n, m;
vector<vector<Edge>> adj;
int prim(int start = 1) {
    int total_weight = 0;
    int node_cnt = 0;
    vector<bool> vis(n + 1, false);
    vector<int> dist(n + 1, INF);
    priority_queue<Node> pq;
    dist[start] = 0;
    pq.push({start, 0});
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        int u = node.id;
        if (vis[u]) continue;
        vis[u] = true;
        total_weight += node.dist;
        node_cnt++;
        if (node_cnt == n) break;
        for (const Edge& edge : adj[u]) {
            int v = edge.to, w = edge.weight;
            if (!vis[v] && w < dist[v]) {
                dist[v] = w;
                pq.push({v, w});
            }
        }
    }
    if (node_cnt < n) return -1; 
    return total_weight;
}
