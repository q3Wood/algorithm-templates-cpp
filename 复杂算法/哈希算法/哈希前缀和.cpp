#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

/**
 * 哈希前缀和并没有固定的模板，核心思想是使用随机数生成器为每个值生成一个随机的哈希值，然后通过前缀和的方式计算区间的哈希值。
 * 这样可以有效地防御负数攻击和哈希碰撞。
 * 以下是用哈希前缀和来判断区间是否为双排列
 */

const int MAXN = 1e5 + 5; // 假设数组最大长度为 10^5
const int MAXM = 1e6 + 5; // 假设数组元素最大值为 10^6

int pre[MAXN]; // 前缀和数组
int hash_val[MAXM]; // 存储每个值的随机哈希值

void init_hash() {
    for (int i = 0; i < MAXM; ++i) {
        hash_val[i] = rng(); // 为每个值生成一个随机哈希值
    }
}
void hash_prefix_sum(const vector<int>& arr) {
    int n = arr.size();
    pre[0] = 0;
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + hash_val[arr[i - 1]];
    }
    for (int i = 1; i < MAXM; i++) {
        hash_val[i] += hash_val[i - 1] + hash_val[i]; // 计算前缀和, 这是为了应对双排列所以每个值加两次。
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init_hash();
    hash_prefix_sum({1, 2, 3, 4, 5}); // 示例数组
    
}


