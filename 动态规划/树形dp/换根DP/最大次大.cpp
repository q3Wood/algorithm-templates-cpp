#include <bits/stdc++.h>
using namespace std;

// 最值型换根 DP 模板
const long long INF = 1e18;

vector<long long> d1, d2;
vector<int> c1;
vector<long long> w;      // 点权（或边权）
vector<vector<int>> g;

// 辅助更新函数：维护最大值、次大值和来源
void update(int u, long long val, int from) {
    if (val > d1[u]) {
        d2[u] = d1[u];
        d1[u] = val;
        c1[u] = from;
    } else if (val > d2[u]) {
        d2[u] = val;
    }
}

// DFS 1：自底向上，收集子树信息
void dfs1(int u, int fa) {
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        // 子节点 v 往上贡献的值（如果不选负贡献，和 0 取 max）
        long long val = max(0LL, d1[v] + w[v]); 
        update(u, val, v);
    }
}

// DFS 2：自顶向下，把父节点方向的信息“换”给子节点
void dfs2(int u, int fa) {
    for (int v : g[u]) {
        if (v == fa) continue;
        // 关键点：除 v 以外，u 的最大增益是多少？
        long long other = (c1[u] == v ? d2[u] : d1[u]);
        long long val_up = max(0LL, other + w[u]);
        
        // 将父节点方向的信息合并进子节点 v
        update(v, val_up, u);
        
        // 继续向下递归
        dfs2(v, u);
    }
}