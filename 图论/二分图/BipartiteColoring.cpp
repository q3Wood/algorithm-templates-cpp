// 判读是否为二分图 2026.7.6
// 【例题】：https://leetcode.cn/problems/maximum-partition-factor/submissions/
#include <bits/stdc++.h>
using namespace std;
int n, m; // n为点数，m为边数
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v; // u, v从0开始编号，如果题目中是从1开始编号，在addEdge时需要减1
        addEdge(u, v); 
    }

    if (check()) {
        cout << "The graph is bipartite." << endl;
    } else {
        cout << "The graph is not bipartite." << endl;
    }

    return 0;
}