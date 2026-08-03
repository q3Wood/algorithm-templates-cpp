#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

class LinearBasis {
public:
    static const int MAXL = 60; // 根据值域范围调整，long long 一般 60
    ll basis[MAXL + 1];
    bool zero; // 记录原集合是否能异或出 0 (即是否存在线性相关)

    LinearBasis() {
        fill(basis, basis + MAXL + 1, 0);
        zero = false;
    }

    // 插入一个数
    void insert(ll x) {
        for (int i = MAXL; i >= 0; --i) {
            if (!(x >> i & 1)) continue; // 如果第 i 位是 0，跳过
            
            if (!basis[i]) { // 如果该位还没有基底，直接占坑
                basis[i] = x;
                return;
            }
            x ^= basis[i]; // 有基底了，消元
        }
        // 如果 x 变成了 0，说明 x 可以被表示，存在线性相关
        zero = true; // 说明原集合中存在子集异或为 0
    }

    // 查询能异或出的最大值
    ll query_max() {
        ll ans = 0;
        for (int i = MAXL; i >= 0; --i) {
            // 贪心：如果异或后能变大，就异或
            if ((ans ^ basis[i]) > ans) {
                ans ^= basis[i];
            }
        }
        return ans;
    }
    
    // 查询能异或出的最小值 (不含 0)
    ll query_min() {
        for (int i = 0; i <= MAXL; ++i) {
            if (basis[i]) return basis[i];
        }
        return 0;
    }
};