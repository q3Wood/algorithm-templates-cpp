// 求二分图的最大匹配数模板，使用匈牙利算法 2026.7.6
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
int n, m; // n为左侧点数，m为右侧点数
vector<int> adj[MAXN]; // adj[i]表示左侧第i个点能匹配到的右侧点的列表
int match[MAXN]; // match[i]表示右侧第i个点匹配的左侧点编号，-1表示未匹配
int vis[MAXN]; // vis[i]表示右侧第i个点是否在当前增广路径中被访问过
int dfn = 0;

bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v] != dfn) {
            vis[v] = dfn;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void addEdge(int u, int v) { // 添加一条单向边，索引从0开始
    adj[u].push_back(v);
}

int maxMatching() { // 求最大匹配数
    memset(match, -1, sizeof(match));
    int res = 0;
    for (int u = 0; u < n; ++u) {
        dfn++;
        if (dfs(u)) res++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int edges; // 边的数量
    cin >> edges;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v); // 添加边，假设输入的u和v是从0开始的索引
    }

    int result = maxMatching();
    cout << "Maximum matching size: " << result << endl;

    return 0;
}
