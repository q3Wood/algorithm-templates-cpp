#include <vector>
using namespace std;

const int MX = 1e7 + 5;
bool is_prime[MX];     // is_prime[i] 为 true 表示是质数
vector<int> primes;    // 按顺序存放搜集到的所有质数
// 需要在极短时间内求出 1 - N 内的所有质数
void euler_sieve() {
    // 初始化：假设大家都是质数 (除 0 和 1 外)
    fill(is_prime, is_prime + MX, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i < MX; i++) {
        if (is_prime[i]) {
            primes.push_back(i); // 如果是质数，拉入质数群
        }
        
        // 核心内层循环：用 i 和当前已知的质数去拼凑合数
        for (int p : primes) {
            if (i * p >= MX) break; // 越界直接退出
            
            is_prime[i * p] = false; // 筛掉合数
            
            // 💡 欧拉筛的灵魂代码（全场最核心的一句）：
            if (i % p == 0) {
                break; 
            }
            // 为什么这里要 break？
            // 如果 i % p == 0，说明 i 里面已经包含了质因子 p。
            // 既然 p 已经是 i 的因子，那么对于后面更大的质数 p'，
            // 合数 (i * p') 的最小质因子一定还是 p，而不是 p'！
            // 所以 (i * p') 应该留给未来的某个时刻，被 p 给筛掉，现在不需要越俎代庖。
        }
    }
}