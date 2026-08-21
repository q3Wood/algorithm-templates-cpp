1. 求多个数的最小公倍数，把所有数的质因数按照各自的最高次幂乘起来最得到了最小公倍数
2. 求多个数的最大公约数，把所有数的质因数按照各自的最低次幂乘起来最得到了最大公约数
3. 求两个数的最小公倍数和最大公约数的关系：
   - 设两个数为 $a$ 和 $b$，则有：
   $$\text{lcm}(a, b) \times \text{gcd}(a, b) = a \times b$$
   - 由此可以得到：
   $$\text{lcm}(a, b) = \frac{a \times b}{\text{gcd}(a, b)}$$

> 求各个数的质因数分解可以使用试除法，或者使用欧几里得算法求最大公约数，再利用最大公约数求最小公倍数。

4. 求多个数的所有公约数的个数和所有公约数的和：
   - 设多个数为 $a_1, a_2, \dots, a_n$，则有：
   $$\text{gcd}(a_1, a_2, \dots, a_n) = d$$
   - 设 $d$ 的质因数分解为：
   $$d = p_1^{e_1} \times p_2^{e_2} \times \dots \times p_k^{e_k}$$
   - 则 $d$ 的所有公约数的个数为：
   $$\text{num\_divisors}(d) = (e_1 + 1) \times (e_2 + 1) \times \dots \times (e_k + 1)$$
   - 则 $d$ 的所有公约数的和为：
   $$\text{sum\_divisors}(d) = \frac{p_1^{e_1 + 1} - 1}{p_1 - 1} \times \frac{p_2^{e_2 + 1} - 1}{p_2 - 1} \times \dots \times \frac{p_k^{e_k + 1} - 1}{p_k - 1}$$

5. 求“公倍数”通常会限定一个范围（比如在 $1 \sim N$ 范围内）：
    - 设 $m = \text{lcm}(a_1, a_2, \dots, a_n)$（最小公倍数）。
    - 在 $1 \sim N$ 范围内的所有公倍数为：$m, 2m, 3m, \dots, km$（其中 $k = \lfloor \frac{N}{m} \rfloor$）。
     - 则在 $1 \sim N$ 范围内的**公倍数个数**为：
   $$\text{num\_multiples} = \lfloor \frac{N}{m} \rfloor = k$$
    - **公倍数的和**（等差数列求和）为：
   $$\text{sum\_multiples} = m + 2m + \dots + km = m \times \frac{k(k + 1)}{2}$$

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




