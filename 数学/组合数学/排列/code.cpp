#include <bits/stdc++.h>

using namespace std;

long long C(int n, int m) {
    if (m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1;
    if (m > n - m) m = n - m; // 利用 C(n, m) = C(n, n-m)
    long long res = 1;
    for (int i = 1; i <= m; ++i) {
        // 关键点 1：边乘边除，防止 res 增长过快导致溢出
        // 关键点 2：(n - m + i) 的连续乘积保证每次都能被 i 整除，绝不丢精度
        res = res * (n + 1 - i) / i;
        // 关键点 3：若 res 超过 k，直接截断，避免大数计算。k为题目限制的上限
        //if (res >= k) return k;
    }
    return res;
}

long long permuteCount(const vector<int>& freq, int k) {
    int n = accumulate(freq.begin(), freq.end(), 0);
    long long res = 1;
    for (int i = 0; i < freq.size(); ++i) {
        if (freq[i] == 0) continue;
        // 计算当前字符的组合数 C(n, freq[i])
        res *= C(n, freq[i]);
        n -= freq[i];
    }
    return res;
}