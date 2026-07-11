#include <vector>
#include <string>
#include <chrono>
#include <random>

using namespace std;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// 2. 封装整数生成器：生成 [L, R] 范围内的随机整数
long long rnd(long long L, long long R) {
    std::uniform_int_distribution<long long> dist(L, R);
    return dist(rng);
}
struct AntiHackDoubleHash {
    using ll = long long;
    
    const ll MOD1 = 1e9 + 7;
    const ll MOD2 = 1e9 + 9; 
    
    ll BASE1, BASE2;

    vector<ll> h1, h2, p1, p2;

    AntiHackDoubleHash(const vector<int>& arr) {
        BASE1 = rnd(13331, 1e9);
        BASE2 = rnd(13331, 1e9);
        while (BASE1 == BASE2) BASE2 = rnd(13331, 1e9);

        int n = arr.size();
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        
        for (int i = 0; i < n; ++i) {
            // 防御负数攻击，拉回正数域
            ll val1 = (arr[i] % MOD1 + MOD1) % MOD1;
            ll val2 = (arr[i] % MOD2 + MOD2) % MOD2;
            
            // 乘法结果最大 10^18，原生的 long long 运算极快
            h1[i + 1] = (h1[i] * BASE1 + val1) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + val2) % MOD2;
            
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    // 针对字符串的重载构造函数
    AntiHackDoubleHash(const string& str) {
        BASE1 = rnd(13331, 1e9);
        BASE2 = rnd(13331, 1e9);
        while (BASE1 == BASE2) BASE2 = rnd(13331, 1e9);

        int n = str.length();
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        
        for (int i = 0; i < n; ++i) {
            ll val1 = str[i];
            ll val2 = str[i];
            
            h1[i + 1] = (h1[i] * BASE1 + val1) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + val2) % MOD2;
            
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    // O(1) 查询闭区间 [l, r] 的 64 位融合哈希值
    ll query(int l, int r) {
        int len = r - l + 1;
        ll res1 = (h1[r + 1] - h1[l] * p1[len] % MOD1 + MOD1) % MOD1;
        ll res2 = (h2[r + 1] - h2[l] * p2[len] % MOD2 + MOD2) % MOD2;
        // 左移 32 位融合，依然是一个干净利落的 64 位 long long
        return (res1 << 32) | res2;
    }
};