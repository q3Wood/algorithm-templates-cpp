#include <vector>
using namespace std;
template <typename T> class UnionFind {
private:
    vector<int> fa;
    vector<T> dis;  // dis[i] 表示 i 到其父节点的边权值

public:
    int cc;
    UnionFind(int n) : fa(n), dis(n) {
        // ranges::iota(fa, 0); // iota(fa.begin(), fa.end(), 0);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            dis[i] = 0;
        }
        cc = n;
    }

    int find(int x) {
        if (fa[x] != x) {
            int root = find(fa[x]);
            dis[x] ^= dis[fa[x]];
            fa[x] = root;
        }
        return fa[x];
    }

    bool merge(int from, int to, T value) {
        int x = find(from), y = find(to);
        if (x == y) {
            return (dis[from] ^ dis[to]) == value;
        }
        dis[x] = value ^ dis[to] ^ dis[from];
        fa[x] = y;
        cc--;
        return true;
    }

    bool is_same(int x, int y) { return find(x) == find(y); }
};