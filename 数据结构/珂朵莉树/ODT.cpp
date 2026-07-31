#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

struct Node {
    int l, r;
    mutable ll v;
    bool operator<(const Node& other) const {
        return l < other.l;
    }
};

set<Node> odt;

// 分裂操作
auto split(int pos) {
    auto it = odt.lower_bound({pos, 0, 0});
    if (it != odt.end() && it->l == pos) return it;
    --it;
    int l = it->l, r = it->r;
    ll v = it->v;
    odt.erase(it);
    odt.insert({l, pos - 1, v});
    return odt.insert({pos, r, v}).first;
}

// 推平操作 (区间赋值)
void assign(int l, int r, ll val) {
    auto itr = split(r + 1);
    auto itl = split(l);
    odt.erase(itl, itr);
    odt.insert({l, r, val});
}

// 其他操作示例：区间加
void add(int l, int r, ll val) {
    auto itr = split(r + 1);
    auto itl = split(l);
    for (auto it = itl; it != itr; ++it) {
        it->v += val;
    }
}

// 初始化 (非常重要！)
void init(int n) {
    odt.clear();
    // 初始时放入一个覆盖全范围的节点，值根据题目要求定 (比如 0)
    odt.insert({1, n, 0}); 
}

int main() {
    int n = 10;
    init(n);
    
    // 示例操作
    assign(1, 5, 1); // [1, 5] 变成 1
    add(3, 7, 2);    // [3, 7] 加 2
    
    // 此时结构：
    // [1, 2] = 1
    // [3, 5] = 1+2 = 3
    // [6, 7] = 0+2 = 2
    // [8, 10] = 0
    
    return 0;
}