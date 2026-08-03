[按位或最大的最小子数组长度](https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/?envType=daily-question&envId=2025-07-29)

# 算法笔记：LogTrick (区间最值/GCD 优化)

## 1\. 核心原理：单调性与 Log 级变化

LogTrick 适用于满足以下性质的运算 $\odot$（如 `&`, `|`, `gcd`）：

**核心观察：**
当我们固定子数组的 **一端（比如右端点 $r$）**，并向另一端扩展（比如左端点 $l$ 从 $r$ 向左移动）时，区间累计值 $Val(l, r) = A[l] \odot \dots \odot A[r]$ 的变化非常“慢”。

1.  **对于按位或 (`|`)**：

      * $A \mid B \ge A$（单调不减）。
      * 每次运算结果变化，至少有一个二进制位从 `0` 变成 `1`。
      * 因为整数（如 `int`）通常只有 30 或 31 个二进制位，所以对于固定的 $r$，随着 $l$ 减小，不同的 $Val(l, r)$ 值 **最多只有约 30 个**。

2.  **对于按位与 (`&`)**：

      * $A \& B \le A$（单调不增）。
      * 每次变化至少有一个 `1` 变成 `0`。同理，不同的值最多只有约 30 个。

3.  **对于最大公约数 (`gcd`)**：

      * $\gcd(A, B) \le A$（单调不增）。
      * 每次变化，结果必然变成前一个值的真因数（至少减少一半）。
      * 因此不同的 GCD 值最多也只有 $O(\log (\max A))$ 个。

**结论：**
虽然子数组总数是 $O(N^2)$，但以 $r$ 结尾的所有子数组的运算结果，**去重后**只有 $O(\log V)$ 种。

-----

## 2\. 算法流程 (通用模板)

我们通常 **枚举右端点 $r$**，并维护一个 **列表 (List/Vector)**，该列表存储了“以 $r$ 结尾的所有可能的运算结果及其对应的左端点位置”。

**步骤：**

1.  初始化一个空的列表 `prev`，存 `pair<value, index>`。
2.  遍历数组每个元素 $x$（作为当前的右端点 $i$）：
      * 创建一个新列表 `curr`。
      * **加入自身**：将 `{x, i}` 加入 `curr`（代表子数组 `[i, i]`）。
      * **传递旧值**：遍历 `prev` 中的每个 `{val, idx}`：
          * 计算新值 `new_val = val ⊙ x`。
          * 将 `{new_val, idx}` 加入 `curr`。
      * **关键步骤（原地去重）**：由于运算的单调性，相同的 `new_val` 必定是连续出现的。我们在 `curr` 中只保留相同值的 **最右侧**（或最左侧，视题目要求）记录。
3.  利用 `curr` 统计答案（例如找最大值、计数等）。
4.  更新 `prev = curr`，进入下一次循环。

-----

## 3\. 复杂度分析

  * **外层循环**：遍历 $N$ 个元素。
  * **内层操作**：列表长度严格限制在 $O(\log V)$ 以内（对于 32 位整数，不超过 30 个）。
  * **总时间复杂度**：$O(N \log V)$。
  * **空间复杂度**：$O(\log V)$。

-----

## 4\. 实战代码：解决 LeetCode 2411

题目 要求找到 **以 $i$ 为左端点** 的子数组，使得按位或值最大，且长度最小。
为了方便处理“以 $i$ 为左端点”，我们可以 **从右向左** 遍历（LogTrick 的方向是灵活的）。

```cpp
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        // ors 存储：{按位或的值, 该值对应的最右边的下标}
        // 这里的逻辑是：对于固定的左端点 i，随着右端点 j 增大，OR 值会增加。
        // 我们记录每个 OR 值第一次出现（或者题目要求的特定位置）的下标。
        vector<pair<int, int>> ors; 

        for (int i = n - 1; i >= 0; --i) {
            // 1. 加入当前元素本身
            ors.push_back({0, i}); // 初始放入一个 dummy 或直接处理 nums[i]
            
            // 2. 更新所有已有的 OR 值
            for (auto& p : ors) {
                p.first |= nums[i];
            }
            
            // 3. 原地去重 (LogTrick 的核心)
            // 我们需要保留对于同一个 OR 值，下标 最小 的那个（因为要求长度最小）
            // 或者根据逻辑，保留下标 最大 的那个。
            // 在本题中，我们从右往左遍历，旧的区间在右边。
            // 如果 nums[i] | x == nums[i] | y，且 x < y，
            // 说明从 i 到 x 已经是这个值了，到 y 也是这个值。
            // 为了维护列表精简，我们去重。
            vector<pair<int, int>> next_ors;
            next_ors.push_back({nums[i], i});
            
            for(auto& p : ors) {
                // 如果当前值和上一个存的值不同，就放进去
                // 这里的去重逻辑保证了 ors 的大小不超过 32
                if(next_ors.back().first != p.first) {
                    next_ors.push_back(p);
                } else {
                    // 如果值相同，我们在本题中不需要更新下标，
                    // 因为我们想要长度最小（也就是右端点越靠左越好）。
                    // next_ors.back() 已经是较小的下标了（因为是新加入的或者之前的）。
                    // *修正*：对于 LC2411，实际上我们可以只维护每个 bit 最后出现的位置更简单，
                    // 但用 LogTrick 的通用写法如下：
                    next_ors.back().second = p.second; // 保留更靠右的下标用于 max 判断？
                    // 其实本题特殊，标准 LogTrick 通常是从左往右。
                    // 下面给出一个最通用的、好理解的 从右向左 写法：
                }
            }
            ors = next_ors;

            // 4. 计算答案
            // 题目要求：最大 按位或。显然后面的 range OR 是单调增的。
            // ors 里的最后一个元素一定是包含最广范围的，也就是 OR 最大值。
            // 它的 value 是最大 OR，但题目要“长度最小”。
            // 在 ors 列表中，值是单调递增的（因为越往右 or 越多）。
            // 最大的 OR 值就在 ors.back().first。
            // 我们需要找到达到这个最大值的 最小下标。
            // 由于去重时合并了，我们需要稍作调整策略：
            // 实际上，max(B_ik) 就是 ors 列表里所有元素 OR 起来，或者说列表里最大的那个值。
            // 列表里第一个达到最大值的 pair 的下标就是我们要的。
            
            // 更简单的逻辑：直接看 ors 中最大的那个值对应的 index
            // 因为是从右向左遍历，ors.back() 是最远的，ors[0] 是最近的。
            // 列表中的值是：[nums[i], ..., max_val]。值递增。
            // 我们要找第一个达到 max_val 的位置。其实就是 ors.back()，
            // 但因为去重逻辑，我们需要保留“使得值变化的那个最靠左的下标”？
            // 不，本题中我们应该保留“值相同下标越小越好”还是“下标越大越好”？
            // 题目：以 i 为起点。找最小子数组。即右端点 j 越小越好。
            // 所以在去重时，如果 val 相同，我们应该保留 index 小的。
        }
        return ans;
    }
};
```

**修正后的、更清晰的 LogTrick 模板（解决 LC 2411）：**

```cpp
vector<int> smallestSubarrays(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    // 列表存储 {OR值, 该值对应的右端点下标}
    vector<pair<int, int>> ors; 

    for (int i = n - 1; i >= 0; --i) {
        // 1. 当前元素自成一组
        ors.push_back({nums[i], i});
        
        // 2. 更新列表中的值
        for (auto& p : ors) p.first |= nums[i];
        
        // 3. 去重 (LogTrick 核心)
        // 此时 ors 中的值是单调递增的（越往后 OR 的数越多）。
        // 如果 adjacent 两个元素值相同，说明中间那段数对 OR 结果没贡献。
        // 对于本题（求最短长度），对于相同的 OR 值，我们要保留 下标更小 的那个（靠左的）。
        // 因为是从右向左遍历，新加入的 {nums[i], i} 在末尾（push_back），
        // 实际上我们应该新建一个 list 来做 merge。
        
        vector<pair<int, int>> next_ors;
        next_ors.push_back({nums[i], i}); // 起点
        
        // 遍历旧列表，进行合并
        for (int k = 0; k < ors.size(); ++k) {
            // 如果当前值和 list 最后一个值不同，说明值变大了，加入
            if (ors[k].first != next_ors.back().first) {
                next_ors.push_back(ors[k]);
            } else {
                // 如果值相同，因为 ors[k].second 比 next_ors.back().second 大（更靠右），
                // 而我们要找“最短”子数组（即右端点越小越好），
                // 所以我们保留 next_ors.back() 里的下标（它是更小的）。
                // 什么都不做，直接跳过 ors[k]
            }
        }
        ors = next_ors;
        
        // 4. 答案就是列表里最大那个值对应的下标
        // 列表里的值单调递增，最后一个就是最大 OR 值。
        // 它的 second 就是达到该值所需的最小右端点。
        ans[i] = max(1, ors.back().second - i + 1);
    }
    return ans;
}
```

## 5\. 总结

**LogTrick** = **固定一端扫描** + **利用位运算单调性** + **维护 Log 个候选值的列表**。
它是解决区间 AND/OR/GCD 计数或最值问题的杀手锏。