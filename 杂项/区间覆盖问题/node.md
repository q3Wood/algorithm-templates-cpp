# 算法专题笔记：区间覆盖问题（造桥/铺地毯模型）

### 一、核心思维模型

面对“**用若干个可用区间，以最少数量连续覆盖目标区间**”的问题，统一抽象为**“造桥渡河”**模型：

```text
               当前破口 uncover = max(tar_l, cur_end)
                             ↓
已造好的桥: [============= cur_end]
候选木板1:         [----------------]
候选木板2:               [------------------------- next_end]  <-- 贪心选它！
目标区间:                      [tar_l ==================== tar_r]
```

1. **`cur_end`（已铺好的最远右端点）**：当前选中的所有区间，最远已经连续覆盖到了哪里。
2. **`uncover`（当前最左破口）**：数轴上**最靠左、迫切需要被立刻盖住的第一个点**。
3. **贪心选择策略**：所有左端点能够得着 `uncover`（即 $left \le uncover$）的可用区间中，**只挑右端点最大的那一个**（步子迈得越远越好）。

---

### 二、终极万能模板（灵神代码骨架）

这套代码同时兼容**单个目标区间**（如 $[0, \text{time}]$）和**多个离散目标区间**：

```cpp
class Solution {
public:
    int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals) {
        // 1. 两个数组均按左端点升序排序
        ranges::sort(availableIntervals, {}, [](auto& a) { return a[0]; });
        ranges::sort(targetIntervals, {}, [](auto& a) { return a[0]; });

        int cur_end = 0; // 已建造的桥的最远右端点
        int i = 0;       // availableIntervals 的扫描指针（只进不退）
        int ans = 0;     // 选取的区间总数

        // 2. 遍历每一个目标区间
        for (auto& target : targetIntervals) {
            int tar_l = target[0], tar_r = target[1];

            // 只要当前的桥还没完全盖住当前目标的右端点，就必须继续建桥
            while (cur_end < tar_r) {
                // 核心：确定当前必须覆盖的第一个破口
                int uncover = max(tar_l, cur_end);

                // 贪心：在所有能接上 uncover 的区间中，寻找能伸到最远的点
                int next_end = cur_end;
                while (i < availableIntervals.size() && availableIntervals[i][0] <= uncover) {
                    next_end = max(next_end, availableIntervals[i][1]);
                    i++;
                }

                // 核心判错：连破口都够不着，或者一步都推不动 -> 出现断层，无解！
                if (next_end < uncover || next_end == cur_end) {
                    return -1;
                }

                // 成功搭上一座新桥，更新最远覆盖范围
                cur_end = next_end;
                ans++;
            }
        }
        return ans;
    }
};
```

---

### 三、模板中的 4 大“套路玄机”

#### 玄机 1：为什么不用提前写“合并目标区间（LC 56）”？
* **代码**：`while (cur_end < tar_r)` 与 `uncover = max(tar_l, cur_end)`
* **原理**：
  * 若区间已被前面完全覆盖（如先有 `[1, 5]`，后有 `[2, 3]`），`cur_end >= 5 >= 3`，`while` 循环直接不进，**自动忽略子区间**；
  * 若两区间重叠（如 `[1, 3]` 和 `[2, 5]`），处理第二个区间时，`uncover = max(2, 3) = 3`，**自动从接缝处无缝续接**。

#### 玄机 2：指针 `i` 为什么敢一辈子不回退？
* **原理**：
  * 因为 `targetIntervals` 和 `cur_end` 都是单调递增的，所以 `uncover` 全程**单调不减**；
  * `availableIntervals` 按左端点排序，若某个区间的左端点 $\le$ 过去的 `uncover`，那它必然也 $\le$ 未来的 `uncover`；
  * 这些区间的最大右端点在过去的轮次已经被 `next_end` 吸收利用过了，无需重复看。指针 `i` 一路走到黑，时间复杂度严格 **$O(N \log N)$**。

#### 玄机 3：断层判定的精髓
* **代码**：`if (next_end < uncover || next_end == cur_end)`
  1. `next_end < uncover`：搜完所有合法的木板，最长的一块居然连 `uncover` 这点都没碰到（甚至可用木板耗尽）；
  2. `next_end == cur_end`：虽然拿到了木板，但它们的全长都在已经铺好的范围内，无法向右推进半步。
  * 两者均意味着**数轴上出现了不可逾越的鸿沟**，直接宣判 `-1`。

#### 玄机 4：实数覆盖 vs 离散整数覆盖
* **实数覆盖（本题）**：水流、光照、连续线段。
  * 条件必须写 `available[i][0] <= uncover`（区间必须重叠或端点接触，不能留有缝隙）。
* **离散整数覆盖（如跳跃游戏）**：
  * 下一个位置只要能接上 `uncover + 1` 即可。

---

### 四、经典题目“家族谱”（举一反三）

这套模板可以原封不动地降维解决以下经典题：

| 题目链接 | 题目特点 | 在模板中如何对应？ |
| :--- | :--- | :--- |
| **LC 45. 跳跃游戏 II** | 离散数组，求到达终点的最少跳数 | `targetIntervals` 只有一个区间 `[0, n-1]`，每个位置 $i$ 相当于一个可用区间 $[i, i + nums[i]]$ |
| **LC 1024. 视频拼接** | 给定片段，拼接出完整的 $[0, \text{time}]$ | `targetIntervals` 只有一个区间 `[0, time]`，直接套用模板 |
| **LC 1326. 灌溉花园** | 给定水龙头半径，覆盖 $[0, n]$ | 每个水龙头转化为区间 $[i - r, i + r]$，目标依然是单区间 $[0, n]$ |
| **LC 4086. 覆盖目标区间** | 目标是多个可能分散、重叠的区间 | **本题（全形态终极版）** |

> **复习记忆口诀**：  
> **双排序、莫回退；`max` 破口、贪最右；推不动、立判负。**