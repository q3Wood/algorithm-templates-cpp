// 例题：[烙饼](https://www.nowcoder.com/practice/23c864e63f1a4645b6651b6c6983f529?channelPut=tracker2)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 记录一条烙制日志
struct Record {
    int id1;     // 饼的编号
    int id2;     // 机器编号
    long long l; // 开始时间
    long long r; // 结束时间
};

int main() {
    // 优化 I/O 速度
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n);
    long long sum_a = 0;
    long long max_a = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum_a += a[i];
        max_a = max(max_a, a[i]);
    }

    // 计算最小完成时间 T
    long long T = max(max_a, (sum_a + m - 1) / m);

    vector<Record> ans;
    int cur_m = 1;        // 当前使用的机器编号 (1-based)
    long long cur_t = 0;  // 当前机器已使用的时间

    for (int i = 0; i < n; i++) {
        long long rem = a[i]; // 当前饼还需烙制的时间
        int id = i + 1;       // 饼的编号 (1-based)

        while (rem > 0) {
            long long space = T - cur_t; // 当前机器剩余可用时间
            if (rem <= space) {
                // 当前机器的剩余时间足够烙完这张饼（或剩下的部分）
                ans.push_back({id, cur_m, cur_t, cur_t + rem});
                cur_t += rem;
                rem = 0;
                if (cur_t == T) {
                    cur_m++;
                    cur_t = 0;
                }
            } else {
                // 当前机器不够用，将当前机器填满，剩下的切到下一台机器
                ans.push_back({id, cur_m, cur_t, T});
                rem -= space;
                cur_m++;
                cur_t = 0;
            }
        }
    }

    // 输出结果
    cout << ans.size() << "\n";
    for (const auto& r : ans) {
        cout << r.id1 << " " << r.id2 << " " << r.l << " " << r.r << "\n";
    }

    return 0;
}