// int bit_width(unsigned n) {
//     if (n == 0) return 0;
//     return std::__lg(n) + 1;
// }
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#define int long long
using namespace std;

class TreeAncestor {
    vector<int> depth;
    vector<vector<int>> pa;
    int max_log;

    int bit_width(unsigned n) {
        if (n == 0) return 0;
        return 32 - __builtin_clz(n);
        // return n == 0 ? 0 : 31 - __builtin_clz(n) + 1;
    }

public:
    TreeAncestor(const vector<vector<int>>& adj, int root = 0) {
        int n = adj.size();
        max_log = bit_width((unsigned)n);
        depth.resize(n);
        pa.assign(n, vector<int>(max_log, -1));

        auto dfs = [&](auto&& dfs, int x, int fa) -> void {
            pa[x][0] = fa;
            for (int y : adj[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dfs(dfs, y, x);
                }
            }
        };
        dfs(dfs, root, -1);

        for (int i = 0; i < max_log - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (pa[x][i] != -1) {
                    pa[x][i + 1] = pa[pa[x][i]][i];
                } else {
                    pa[x][i + 1] = -1;
                }
            }
        }
    }

    int getKthAncestor(int node, int k) {
        for (int i = 0; i < max_log; i++) {
            if ((k >> i) & 1) {
                node = pa[node][i];
                if (node == -1) break;
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) swap(x, y);

        y = getKthAncestor(y, depth[y] - depth[x]);
        if (y == x) return x;

        for (int i = max_log - 1; i >= 0; i--) {
            if (pa[x][i] != pa[y][i]) {
                x = pa[x][i];
                y = pa[y][i];
            }
        }
        return pa[x][0];
    }

    int get_distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }

    int get_depth(int x) { return depth[x]; }
    int get_parent(int x) { return pa[x][0]; }
};