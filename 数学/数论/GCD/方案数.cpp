/**
 * 例题：[https://www.matiji.net/exam/brushquestion/20/4777/C98C14523F069FECB0DEED64F00CEAB0?from=1]
 * 求从数组中选出若干个元素，使得它们的最大公约数恰好为x, 求选法的个数。
 * 直接求“GCD 恰好等于 $x$”的方案数非常困难，因为条件非常严苛。但是求“GCD 是 $x$ 的倍数”的方案数却极其简单：
 * 只要选出来的数全是 $x$ 的倍数即可
 * 外层循环枚举 $i$，内层循环枚举 $i$ 的倍数。执行次数为：$\frac{N}{1} + \frac{N}{2} + \frac{N}{3} + \dots + \frac{N}{N}$
 * 根据高数知识，这是调和级数，其总和逼近 $N \ln N$。时间复杂度：$O(N \log N)$（对于 $N=10^6$，运算量只有 $1.4 \times 10^7$ 左右，非常快）。
 */

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_VAL = 1000005; // 数组中出现的最大数值（值域上限）

int cnt[MAX_VAL];        // cnt[i] 统计原数组中数字 i 出现的次数
long long f[MAX_VAL];    // f[i] 记录 GCD 恰好等于 i 的方案数

long long fast_pow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    
    int max_num = 0; // 记录整个数组的最大值，作为倒推的起点
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
        max_num = max(max_num, x);
    }

    // 从最大值倒推回 1
    for (int i = max_num; i >= 1; --i) {
        int multiple_count = 0;
        
        // 1. 统计原数组中有多少个数是 i 的倍数 (调和级数累加)
        for (int j = i; j <= max_num; j += i) {
            multiple_count += cnt[j];
        }

        // 2. 计算 g[i] (即全都是 i 的倍数的组合方案数)
        // -------------------------------------------------------------
        // 【核心变化点】：根据题目要求选子集、选2个数、还是选序列，这里公式不同
        // 场景 A (选非空子集): g[i] = 2^{multiple_count} - 1
        long long gi = (fast_pow(2, multiple_count) - 1 + MOD) % MOD;
        
        // 场景 B (任意选 k 个数构成序列): g[i] = multiple_count^k
        // long long gi = fast_pow(multiple_count, k);
        
        // 场景 C (只选两个不同的数): g[i] = C(multiple_count, 2)
        // long long gi = 1LL * multiple_count * (multiple_count - 1) / 2 % MOD;
        // -------------------------------------------------------------
        
        f[i] = gi;

        // 3. 容斥减法：减去 GCD 严格等于 i 的倍数的那些非法方案
        for (int j = i * 2; j <= max_num; j += i) {
            // 注意减法取模的规范写法，防止出现负数
            f[i] = (f[i] - f[j] + MOD) % MOD; 
        }
    }

    // cout << f[1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
