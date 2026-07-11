// ### 根号分治核心思想：小步长预处理，大步长暴力跳
// 这套骨架适用于：**给定步长 $p$，求所有间隔为 $p$ 的元素之和（或最大值等操作）。**
// 例题：https://www.luogu.com.cn/problem/P3396

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 150005; // 假设最大数组长度为 150000
const int THRESHOLD = 387; // 阈值，通常取 sqrt(MAXN)，150000 的平方根约为 387

int a[MAXN];

// ans[p][x] 记录步长为 p，且除以 p 的余数为 x 的所有元素的和
// 空间代价：THRESHOLD * THRESHOLD ≈ 387 * 387 ≈ 150,000，非常小
int ans[THRESHOLD + 5][THRESHOLD + 5]; 

int n, m;

// 1. 初始化预处理 (仅处理小步长 p <= THRESHOLD 的情况)
void build() {
    // 遍历每一个原始数组的元素
    for (int i = 1; i <= n; i++) {
        // 将元素 a[i] 贡献给所有可能的小步长 p
        for (int p = 1; p <= THRESHOLD; p++) {
            // 下标 i 对步长 p 取模的结果
            int x = i % p; 
            ans[p][x] += a[i];
        }
    }
}

// 2. 单点修改：只修改小步长预处理数组
void update(int idx, int val) {
    int diff = val - a[idx]; // 计算增量
    a[idx] = val;            // 更新原数组
    
    // 只需更新那些 p <= THRESHOLD 的答案
    for (int p = 1; p <= THRESHOLD; p++) {
        int x = idx % p;
        ans[p][x] += diff;
    }
}

// 3. 根号分治双轨查询
int query(int p, int x) {
    // 策略 A：如果步长较小，直接 O(1) 返回预处理好的答案
    if (p <= THRESHOLD) {
        return ans[p][x];
    } 
    // 策略 B：如果步长极大，暴力跳跃查询
    else {
        int res = 0;
        // 起点是 x。如果 x=0，为了避免跳到下标 0 (数组从 1 开始)，需要特殊处理
        // 也可以不处理，确保遍历条件满足 i <= n 即可
        for (int i = x; i <= n; i += p) {
            if (i > 0) { // 避开无用的 0 索引
                res += a[i];
            }
        }
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 预处理
    build();

    while (m--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'A') {
            // 查询：步长为 x，余数为 y
            cout << query(x, y) << "\n";
        } else if (op == 'C') {
            // 修改：将第 x 个元素修改为 y
            update(x, y);
        }
    }

    return 0;
}