/**
 * 旅行商问题
 * 定义f[mask][i]表示在访问了mask表示的集合请求后，最后一个请求为第i个请求的最小时间
 * 状态转移方程：
 * f[mask][i] = max(t_i, min(f[mask ^ (1 << i)][j] + |x_i - x_j|))，其中j为mask中除i外的请求，遍历所有j求最小值，j & (mask ^ (1 << i)) != 0
 * 初始状态：f[1 << i][i] = max(|x_i - start|, t_i), 初始化集合中只有一个请求的情况
 * 最终答案为min(f[(1 << m) - 1][i])，其中i为所有请求的索引，表示访问了所有请求后最后一个请求为第i个请求的最小时间
 * 例题：https://leetcode.cn/problems/elevator-requests-iii/description/
 */
#include <bits/stdc++.h>
#include <ranges>
using namespace std;
class Solution {
public:
    long long elevatorRequests(int n, int start, vector<vector<int>>& requests) {
        int m = requests.size();
        vector f(1 << m, vector<long long>(m));
        for (int i = 0; i < m; i++) {
            auto& req = requests[i];
            f[1 << i][i] = max(abs(req[1] - start), req[0]);
        }

        for (int mask = 1; mask < (1 << m); mask++) {
            if ((mask & (mask - 1)) == 0) { // mask 只有一个元素
                continue;
            }
            for (int i = 0; i < m; i++) {
                if ((mask >> i & 1) == 0) {
                    continue;
                }
                auto& req = requests[i];
                int t = req[0], x = req[1];
                long long res = LLONG_MAX;
                int msk = mask ^ (1 << i);
                for (int j = 0; j < m; j++) {
                    if (msk >> j & 1) {
                        res = min(res, f[msk][j] + abs(x - requests[j][1]));
                    }
                }
                f[mask][i] = max(res, 1LL * t);
            }
        }
        long long ans = LLONG_MAX;
        for (int i = 0; i < m; i++) {
            ans = min(ans, f[(1 << m) - 1][i]);
        }
        // return ranges::min(f.back());
        return ans;
    }
};