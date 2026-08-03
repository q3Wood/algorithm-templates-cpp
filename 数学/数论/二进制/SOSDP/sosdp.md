**SOS DP** 全称是 **Sum Over Subsets Dynamic Programming**（**子集和动态规划**）。它是算法竞赛和状态压缩 DP 中一种非常高频且高效的优化技巧。

---

### 💡 SOS DP 是用来解决什么问题的？

假设给你一个长度为 $2^N$ 的数组 $A$（下标用 $N$ 位的二进制状态 `mask` 表示）。
现在要求对于**每一个**二进制掩码 `mask`，算出它的**所有子集的权值和**：

$$F[\text{mask}] = \sum_{\text{sub} \subseteq \text{mask}} A[\text{sub}]$$

*(注：$\text{sub} \subseteq \text{mask}$ 表示 $\text{sub}$ 的每一个为 1 的二进制位，在 $\text{mask}$ 中也必定为 1。)*

#### 两种解法的复杂度对比：

1. **暴力枚举子集**（利用 `sub = (sub - 1) & mask`）
   * 复杂度：$O(3^N)$
   * 当 $N = 20$ 时，$3^{20} \approx 3.5 \times 10^9$，**必定超时 (TLE)**。

2. **使用 SOS DP**
   * 复杂度：$O(N \cdot 2^N)$
   * 当 $N = 20$ 时，$20 \times 2^{20} \approx 2 \times 10^7$，可以在 **0.02 秒内**瞬间算完！

---

### 🧠 核心思想与状态转移

SOS DP 的核心思想是：**按位（Bit by Bit）逐渐放开限制，递推求解。**

定义状态 $dp[i][\text{mask}]$ 表示：
> 考虑二进制的前 $i$ 位（即从第 $0$ 到第 $i-1$ 位），可以是 $\text{mask}$ 的子集；而第 $i$ 位及更高的位，必须与 $\text{mask}$ **完全相同**的所有 $\text{sub}$ 的 $A[\text{sub}]$ 之和。

#### 转移逻辑（看第 $i$ 位是 0 还是 1）：

对于状态 $\text{mask}$ 的第 $i$ 位：
1. **如果第 $i$ 位是 `0`**：
   那么子集 $\text{sub}$ 的第 $i$ 位**只能是 `0`**。
   $$dp[i][\text{mask}] = dp[i - 1][\text{mask}]$$

2. **如果第 $i$ 位是 `1`**：
   那么子集 $\text{sub}$ 的第 $i$ 位既可以是 `0`，也可以是 `1`。
   - 第 $i$ 位填 `1` 的贡献：$dp[i - 1][\text{mask}]$
   - 第 $i$ 位填 `0` 的贡献：$dp[i - 1][\text{mask} \oplus (1 \ll i)]$
   $$dp[i][\text{mask}] = dp[i - 1][\text{mask}] + dp[i - 1][\text{mask} \oplus (1 \ll i)]$$

#### 空间优化：
注意到第一维 $i$ 只和 $i-1$ 有关，因此可以滚动数组优化，把第一维直接省去！

---

### 💻 模板代码实现

#### 1. 求子集和（Submask Sum）
计算 $F[\text{mask}] = \sum_{\text{sub} \subseteq \text{mask}} A[\text{sub}]$

```cpp
#include <vector>

using namespace std;

// N 是二进制位数，A 是原数组（大小为 1 << N）
vector<long long> sos_dp_submask(int N, vector<long long>& A) {
    vector<long long> F = A; // 初始状态 dp[0][mask] = A[mask]

    for (int i = 0; i < N; ++i) { // 遍历二进制的每一位
        for (int mask = 0; mask < (1 << N); ++mask) {
            if (mask & (1 << i)) { // 如果第 i 位是 1
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }
    return F;
}
```

#### 2. 求超集和（Superset Sum）
计算 $F[\text{mask}] = \sum_{\text{mask} \subseteq \text{super}} A[\text{super}]$ （即计算包含当前状态的所有更大状态的和）

```cpp
vector<long long> sos_dp_superset(int N, vector<long long>& A) {
    vector<long long> F = A;

    for (int i = 0; i < N; ++i) {
        for (int mask = (1 << N) - 1; mask >= 0; --mask) {
            if (!(mask & (1 << i))) { // 如果第 i 位是 0
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }
    return F;
}
```

---

### 🎯 常见应用场景

1. **求按位与（AND）为 0 的数对数量**：
   - 条件 $a_i \text{ AND } a_j = 0$ 等价于 $a_j \subseteq \text{compliment}(a_i)$（$a_j$ 是 $a_i$ 的补码的子集）。
   - 可以先用频次数组建出 $A$，再用 SOS DP 求出每个掩码的子集数，从而 $O(1)$ 回答满足条件的对数。

2. **快速 Zeta 变换（Fast Zeta Transform / FMT）**：
   - SOS DP 的本质其实就是高维 Poset（偏序集）上的快速 Zeta 变换，常用于处理二进制卷积（如 OR 卷积、AND 卷积）。

3. **容斥原理与子集卷积**：
   - 配合容斥原理或者子集卷积（Subset Convolution），解决多集合覆盖、独立集计数等高级图论与组合计数问题。

### 🌟 总结一览

| 概念 | 含义 | 复杂度 |
| :--- | :--- | :--- |
| **求解目标** | 算出所有子集/超集的元素权值和 | - |
| **暴力做法** | 枚举每个 mask 的子集 | $O(3^N)$ |
| **SOS DP** | 按位递推更新子集贡献 | **$O(N \cdot 2^N)$** |