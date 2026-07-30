#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;//1e9 + 7; // 或者是 998244353
const int MAXN = 2e5 + 5; // 根据题目 n 的范围调整

long long fact[MAXN];     // 阶乘数组: fact[i] = i! % MOD
long long invFact[MAXN];  // 阶乘逆元数组: invFact[i] = (i!)^(-1) % MOD

// 1. 快速幂模板：求 a^b % MOD
long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long getInv(long long a) {
    return qpow(a, MOD - 2);
}

void init() {
    fact[0] = 1;
    invFact[0] = 1;
    
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    
    invFact[MAXN - 1] = getInv(fact[MAXN - 1]);
    
    // 解释：1/(i-1)! = (1/i!) * i
    for (int i = MAXN - 2; i >= 1; --i) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    // intt[i] = (mod - mod / i) * intt[mod % i] % mod; intt[i] 是 i 的逆元
}

long long C(int n, int m) {
    if (m < 0 || m > n || n < 0) return 0;
    
    long long res = fact[n];
    res = res * invFact[m] % MOD;
    res = res * invFact[n - m] % MOD;
    
    return res;
}

// 专门对付 n 极大、m 较小的组合数
long long nCr(long long n, long long m) {
    if (m < 0 || n < m) return 0;
    if (m == 0) return 1;
    
    long long num = 1;
    // 分子部分暴力连乘 m 次：n * (n-1) * ... * (n-m+1)
    for (int i = 0; i < m; ++i) {
        num = num * ((n - i) % MOD) % MOD; 
    }
    // 分母部分依然可以使用你的 invFact，因为 m 最大才 10^6
    return num * invFact[m] % MOD;
}

long long A(int n, int m) {
    if (m < 0 || m > n || n < 0) return 0;
    return fact[n] * invFact[n - m] % MOD;
}
