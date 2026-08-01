#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 5005;

struct Edge {
    int to, w;
};
vector<Edge> adj[MAXN];

int dist1[MAXN]; 
int dist2[MAXN]; 

void dijkstra(int start, int n) {
    for(int i = 1; i <= n; i++) {
        dist1[i] = dist2[i] = INF;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist1[start] = 0;
    pq.push({0, start});
    
    while(!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist2[u]) continue;
        
        for(auto& e : adj[u]) {
            int v = e.to;
            int new_dist = d + e.w;
            if(new_dist < dist1[v]) {
                dist2[v] = dist1[v];      
                pq.push({dist2[v], v});  
                
                dist1[v] = new_dist;      
                pq.push({dist1[v], v});
            }
            else if(new_dist > dist1[v] && new_dist < dist2[v]) {
                dist2[v] = new_dist;
                pq.push({dist2[v], v});
            }
        }
    }
}