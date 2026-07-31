#include <bits/stdc++.h>
using namespace std;

// tarjan 模板
const int MAXN = 200005;

vector<int> adj[MAXN];
vector<pair<int, int>> queries[MAXN]; 
int ans[MAXN];                        
int fa[MAXN];                         
bool vis[MAXN];                       

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void tarjan(int u) {
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v]) {
            tarjan(v);
            fa[v] = u; 
        }
    }

   
    for (auto& q : queries[u]) {
        int v = q.first;
        int id = q.second;
        if (vis[v]) {
            ans[id] = find(v); 
        }
    }
}