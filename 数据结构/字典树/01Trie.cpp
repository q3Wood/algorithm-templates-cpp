#include <bits/stdc++.h>
using namespace std;

// 01-Trie 异或最大值模板
const int MAX_NODE = 100005 * 32; // 每个数字最多32位
int ch[MAX_NODE][2];              // 只有0和1两个分叉
int idx = 0;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int u = (x >> i) & 1; 
        if (!ch[p][u]) ch[p][u] = ++idx;
        p = ch[p][u];
    }
}

// 查询数组中谁和 x 异或结果最大，返回那个最大的异或值
int query_max_xor(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int u = (x >> i) & 1;
        int opposite = u ^ 1; 
        
        if (ch[p][opposite]) {
            res |= (1 << i);
            p = ch[p][opposite];
        } else {
            p = ch[p][u];
        }
    }
    return res;
}