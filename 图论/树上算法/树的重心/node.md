### 一、树的重心核心定义与性质
1. **定义**：找到一个节点 $u$，若将其删去，产生的所有子树中**最大子树节点数最小**。
2. **性质 1**：以重心为根时，其**任何一棵子树的大小都不超过 $\lfloor n / 2 \rfloor$**。
3. **性质 2**：树上**所有节点到该节点的距离和最小**。
4. **性质 3**：一棵树的重心**只有 1 个或 2 个**（如果有 2 个，它们之间必定直接相邻）。

---

### 二、标准模板（整棵树连通）

这是最常见的情况，只需要**一次 DFS** 即可找出所有重心。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
vector<vector<int>> adj;
vector<int> sz;             // sz[u] 表示以 u 为根的子树节点数
vector<int> centroids;      // 存储求出的重心（可能有 1 个或 2 个）
int min_max_part = INF;     // 记录最小的最大子树大小

void get_centroids(int u, int p) {
    sz[u] = 1;
    int max_part = 0; // 记录删去 u 后，产生的最大子树大小

    for (int v : adj[u]) {
        if (v == p) continue;
        get_centroids(v, u);
        sz[u] += sz[v];
        max_part = max(max_part, sz[v]); // 下方子树
    }
    // 上方那部分子树的大小为 n - sz[u]
    max_part = max(max_part, n - sz[u]);

    // 更新最小的最大连通块
    if (max_part < min_max_part) {
        min_max_part = max_part;
        centroids.clear();
        centroids.push_back(u);
    } else if (max_part == min_max_part) {
        centroids.push_back(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.resize(n + 1);
    sz.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 从 1 号点出发求重心
    get_centroids(1, 0);

    // 输出结果（升序）
    sort(centroids.begin(), centroids.end());
    for (int u : centroids) {
        cout << u << " ";
    }
    cout << "\n";

    return 0;
}
```

---

### 三、进阶模板（点分治 / 动态求子树重心 / 森林）

在**点分治（CDQ 分治 / 点分树）**或图可能不连通时，我们通常需要在已知大小为 `total_size` 的连通块内找重心。这种写法是竞赛季最常用的标准板子：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int n, m;
vector<vector<int>> adj;
vector<int> sz;
vector<bool> vis;

// 计算当前子树/连通块大小
void get_sz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p || vis[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

// 寻找该连通块内的重心
void get_centroid(int u, int p, int total_sz, vector<int>& centroids) {
    int max_part = total_sz - sz[u]; // 上方部分
    for (int v : adj[u]) {
        if (v == p || vis[v]) continue;
        max_part = max(max_part, sz[v]); // 下方各子树
        get_centroid(v, u, total_sz, centroids);
    }
    // 任何一部分都不超过总大小的一半，即为重心
    if (max_part <= total_sz / 2) {
        centroids.push_back(u);
    }
}

// 对一个包含 root 的连通块求重心
vector<int> find_centroids_in_component(int root) {
    get_sz(root, 0);
    int total_sz = sz[root];
    vector<int> res;
    get_centroid(root, 0, total_sz, res);
    return res;
}
```

### 复杂度
- **时间复杂度**：$O(n)$，只需遍历一次树的节点和边。
- **空间复杂度**：$O(n)$，只存图和 `sz` 数组。