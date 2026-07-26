1. 求多个数的最小公倍数，把所有数的质因数按照各自的最高次幂乘起来最得到了最小公倍数
2. 求多个数的最大公约数，把所有数的质因数按照各自的最低次幂乘起来最得到了最大公约数
3. 求两个数的最小公倍数和最大公约数的关系：
   - 设两个数为 $a$ 和 $b$，则有：
   $$\text{lcm}(a, b) \times \text{gcd}(a, b) = a \times b$$
   - 由此可以得到：
   $$\text{lcm}(a, b) = \frac{a \times b}{\text{gcd}(a, b)}$$

> 求各个数的质因数分解可以使用试除法，或者使用欧几里得算法求最大公约数，再利用最大公约数求最小公倍数。
```cpp
vector<pair<long long, int>> prime_factorize(long long n) {
    vector<pair<long long, int>> factors;
    
    // 只需遍历到 sqrt(n)
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) { // i 一定是质数 (因为所有的合数因子早就被前面更小的质数除干净了)
            int count = 0;
            // 榨干这个质因子
            while (n % i == 0) {
                count++;
                n /= i;
            }
            factors.push_back({i, count});
        }
    }
    
    // 💡 灵魂收尾：
    // 榨干了所有 <= sqrt(n) 的因子后，如果 n 仍然 > 1，
    // 说明剩下的这个 n 就是那个唯一大于 sqrt(N) 的质因子！
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}
```