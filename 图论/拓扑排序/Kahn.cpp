#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 拓扑排序 Kahn 算法模板
// 返回值: 如果存在拓扑排序，返回排序后的节点数组；如果存在环，返回空数组
vector<int> kahnTopologicalSort(int n, const vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    vector<int> in_degree(n, 0);
    
    // 1. 构建邻接表并统计入度
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // 2. 初始化队列，推入所有入度为 0 的节点
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> topo_order;
    
    // 3. 核心剥离循环
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        
        // 遍历所有邻居，解除依赖
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // 4. 环路检测：判断是否所有节点都被遍历到
    if (topo_order.size() != n) {
        return {}; // 存在环，无法进行完整拓扑排序
    }
    
    return topo_order;
}