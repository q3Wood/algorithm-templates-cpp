#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

// --- 极其干净的全局静态数据区 ---
vector<int> adj[MAXN];       // 树的邻接表（只有这个用 vector，因为各节点度数不同）
int depth[MAXN];             // 节点的深度
int first_pos[MAXN];         // 节点在欧拉序中第一次出现的索引
int euler_seq[2 * MAXN];     // 存放拍扁后的回溯欧拉序
int timer;                   // 欧拉序计时器

int st[2 * MAXN][20];        // 纯连续二维全局数组，速度的保障
int lg[2 * MAXN];            // 预处理的 log 数组

// 扁平的 DFS 函数
void dfs_euler(int u, int p, int d) {
    depth[u] = d;
    first_pos[u] = ++timer;
    euler_seq[timer] = u;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_euler(v, u, d + 1);
            euler_seq[++timer] = u; // 回溯打卡
        }
    }
}

// 扁平的初始化函数
void init_lca(int n) {
    timer = 0;
    dfs_euler(1, 0, 0); // 假设以 1 为根

    // 预处理 log 数组
    lg[1] = 0;
    for (int i = 2; i <= timer; i++) lg[i] = lg[i / 2] + 1;

    // 填充 ST 表的第 0 层
    for (int i = 1; i <= timer; i++) st[i][0] = euler_seq[i];

    // 递推填充整张表
    for (int j = 1; (1 << j) <= timer; j++) {
        for (int i = 1; i + (1 << j) - 1 <= timer; i++) {
            int a = st[i][j - 1];
            int b = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (depth[a] < depth[b]) ? a : b;
        }
    }
}

// 没有任何指针跳转、极速 O(1) 的 LCA 核心
inline int get_lca(int u, int v) {
    int l = first_pos[u], r = first_pos[v];
    if (l > r) swap(l, r);
    int k = lg[r - l + 1];
    int a = st[l][k];
    int b = st[r - (1 << k) + 1][k];
    return (depth[a] < depth[b]) ? a : b;
}

// 极其清爽的距离计算
inline int get_distance(int u, int v) {
    if (u == 0 || v == 0) return -1e9;
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}