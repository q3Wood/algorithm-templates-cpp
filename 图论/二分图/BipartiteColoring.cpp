// 判读是否为二分图 2026.7.6
#include <bits/stdc++.h>
using namespace std;
int n, m; // n为左侧点数，m为右侧点数
const int MAXN = 505;
vector<int> adj[MAXN]; // 邻接表表示图
int color[MAXN]; // color[i]表示第i个点的颜色，0表示未染色，1表示红色，2表示蓝色
bool possible = true; 

void dfs(int u, int c) {
    color[u] = c; 
    for (int v : adj[u]) {
        if (color[v] == c) {
            possible = false; 
            return;
        }
        if (color[v] == 0) {
            dfs(v, 3 - c); 
            if (!possible) return;
        }
    }
}

void addEdge(int u, int v) { // 添加一条无向边，索引从0开始
    adj[u].push_back(v);
    adj[v].push_back(u);
}

bool check() {
    memset(color, 0, sizeof(color));
    possible = true;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            dfs(i, 1); 
            if (!possible) return false;
        }
    }
    return true;
}