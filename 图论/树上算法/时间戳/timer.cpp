#include <vector>
#include <iostream>

using namespace std;
const int MAXN = 100005;

int timer = 0; // 全局计时器
int in[MAXN], out[MAXN]; // 节点在欧拉序中第一次出现的索引

vector<int> adj[MAXN]; // 树的邻接表
void dfs(int u, int p) {
    in[u] = ++timer; 
    for (int v : adj[u]) {
        if (v != p) { 
            dfs(v, u);
        }
    }
    out[u] = timer; 
}

// u的子树结点的范围是 [in[u], out[u]]，包含u本身


