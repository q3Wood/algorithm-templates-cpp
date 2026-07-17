#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005; // 原始节点数的上限根据题目调整为 5e5
const int MAXM = 500005; // 边数的上限
const int LOG = 21;      // 倍增最大步数 (5e5 节点，重构树近 1e6，LOG 开 21 保险)

struct Edge {
    int u, v, w;
    // 重载小于号：如果是求“经过边权 <= x”，则从小到大排序 (w < other.w)
    // 如果是求“经过边权 >= x”（例如接水问题），则从大到小排序 (w > other.w)
    bool operator<(const Edge& other) const {
        return w < other.w; 
    }
} edges[MAXM];

int n, m;
int total_nodes; // 重构树的总结点数 (原节点数 n + 虚拟节点数)

// 新增：记录原图的点权
int a[MAXN]; 
// 新增：记录重构树中子树包含的“原图节点（城市）”数量
int sz[MAXN * 2]; 

// 虚拟节点的权值（也就是原图的边权）
int val[MAXN * 2]; 

// 并查集数组
int fa[MAXN * 2];

// 倍增祖先数组，fa_tree[i][j] 表示节点 i 向上跳 2^j 步到达的祖先
int fa_tree[MAXN * 2][LOG]; 

// 树的结构，用于后续可能需要的 DFS (求 dfs 序、子树大小等)
vector<int> tree_adj[MAXN * 2];

// 并查集初始化
void init_dsu(int size) {
    for (int i = 1; i <= size; i++) {
        fa[i] = i;
    }
}

// 并查集查找 (路径压缩)
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void build_kruskal_tree() {
    // 1. 按边权排序
    sort(edges + 1, edges + 1 + m);
    
    // 2. 初始化并查集，注意大小要开到 2*n，因为会产生 n-1 个虚拟节点
    init_dsu(n * 2);
    
    // 前 n 个节点是原图的叶子节点，权值对于限制边权的问题通常不重要
    for (int i = 1; i <= n; i++) {
        val[i] = 0; 
        sz[i] = 1; // 新增：每个原图节点算作 1 个独立城市
    }
    
    total_nodes = n; // 当前重构树有 n 个原节点
    
    // 3. 开始 Kruskal 算法
    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w; // 在主函数读入时，w 已经被赋值为 max(a[u], a[v])
        
        int root_u = find(u);
        int root_v = find(v);
        
        // 如果不在同一个集合，需要合并
        if (root_u != root_v) {
            total_nodes++; // 新建一个虚拟节点
            val[total_nodes] = w; // 虚拟节点的权值就是当前边的权值
            sz[total_nodes] = sz[root_u] + sz[root_v]; // 新增：合并连通块，城市数量相加
            
            // 将两个集合的根节点连到新的虚拟节点下
            fa[root_u] = total_nodes;
            fa[root_v] = total_nodes;
            
            // 建立真实的树形结构 (虚拟节点连向原来的根)
            tree_adj[total_nodes].push_back(root_u);
            tree_adj[total_nodes].push_back(root_v);
            
            // 维护倍增数组的第 0 层 (父节点)
            fa_tree[root_u][0] = total_nodes;
            fa_tree[root_v][0] = total_nodes;
            
            // 注意：因为是新建节点作为父亲，此时 total_nodes 的父亲还是自己
            fa_tree[total_nodes][0] = 0; 
        }
    }
}

// 预处理倍增数组，用于 O(log N) 向上跳跃
void build_lca() {
    // total_nodes 通常是 2n - 1
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= total_nodes; i++) {
            if (fa_tree[i][j - 1] != 0) {
                fa_tree[i][j] = fa_tree[fa_tree[i][j - 1]][j - 1];
            } else {
                fa_tree[i][j] = 0;
            }
        }
    }
}

// 核心查询：从 start_node 出发，只走边权 <= limit 的边，
// 返回能到达的“最高统治者” (某个虚拟节点)
int get_highest_reachable_node(int start_node, int limit) {
    int current = start_node;
    
    // 贪心向上跳：如果上面第 2^j 步的祖先存在，且权值 <= limit，就跳上去
    for (int j = LOG - 1; j >= 0; j--) {
        int next_anc = fa_tree[current][j];
        if (next_anc != 0 && val[next_anc] <= limit) {
            current = next_anc;
        }
    }
    
    // 返回这个最高祖先的编号
    // 在这棵子树里的所有叶子节点，就是原图中你能到达的所有点！
    return current;
}

int main() {
    // 题目数据量达到 5e5，必须优化输入输出流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    // 1. 读入城市阈值
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 2. 读入双向道路，并完成“点权转边权”
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i].u = u;
        edges[i].v = v;
        // 核心转化：要走这条路，财富值必须同时满足两端的阈值
        edges[i].w = max(a[u], a[v]); 
    }

    // 3. 建树并预处理 LCA 的倍增数组
    build_kruskal_tree();
    build_lca();

    // 4. 处理在线询问
    int q;
    cin >> q;
    while (q--) {
        int u, x;
        cin >> u >> x;
        
        // 找到在财富值 x 的限制下，能跳到的最高连通块祖先
        int highest_root = get_highest_reachable_node(u, x);
        
        // 该祖先子树内的叶子（城市）总数，就是答案
        cout << sz[highest_root] << "\n";
    }

    return 0;
}

// 后续可以添加主席树或线段树等数据结构，支持动态修改城市阈值 a[i]，并在 O(log^2 N) 或 O(log N) 内完成查询。