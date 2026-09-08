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
int n; // 全局变量，表示区间的右边界, n 可以根据题目要求设置为最大值，通常为题目中允许的最大下标。注意spilt函数中需要检查 pos 是否大于 n，以防止越界。
// 分裂操作
// auto split(int pos) {
//     auto it = odt.lower_bound({pos, 0, 0});
//     if (it != odt.end() && it->l == pos) return it;
//     --it;
//     int l = it->l, r = it->r;
//     ll v = it->v;
//     odt.erase(it);
//     odt.insert({l, pos - 1, v});
//     return odt.insert({pos, r, v}).first;
// }
auto split(int pos) {
    if (pos > n) return odt.end(); // 核心防线：超出右边界直接返回 end()
    
    auto it = --odt.upper_bound({pos, 0, 0}); // 用 upper_bound 找 <= pos 的区间更稳健
    if (it->l == pos) return it;
    
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
    n = 10;
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