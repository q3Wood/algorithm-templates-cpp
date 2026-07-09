#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> sz; 

public:
    DSU(int n) {
        parent.resize(n + 1); // 下标从 1 开始
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); 
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (sz[rootX] < sz[rootY]) {
                parent[rootX] = rootY;
                sz[rootY] += sz[rootX];
            } else {
                parent[rootY] = rootX;
                sz[rootX] += sz[rootY];
            }
        }
    }
    
    int getSize(int x) {
        return sz[find(x)];
    }
};

