#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    long long dx, dy, c;
    // 重载小于号，用于后续对向量分组和 C 值排序
    bool operator<(const Segment& other) const {
        if (dx != other.dx) return dx < other.dx;
        if (dy != other.dy) return dy < other.dy;
        return c < other.c;
    }
};

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<long long, long long>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    vector<Segment> segs;
    // 预分配内存，C(n, 2) 对点
    segs.reserve(n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = points[j].first - points[i].first;
            long long dy = points[j].second - points[i].second;
            long long start_x, start_y;

            // 规范化向量方向, 指向右上方，避免同一线段出现两种方向的向量
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
                start_x = points[j].first;
                start_y = points[j].second;
            } else {
                start_x = points[i].first;
                start_y = points[i].second;
            }

            long long c = dy * start_x - dx * start_y;
            segs.push_back({dx, dy, c});
        }
    }

    // 排序后，相同 (dx, dy) 的线段会聚集在一起，且按 c 值从小到大排列
    sort(segs.begin(), segs.end());

    long long max_area = 0;
    int m = segs.size();
    
    // 遍历排序后的数组，寻找同组 (dx, dy) 的最大面积
    for (int i = 0; i < m; ) {
        int j = i;
        // 找到相同 (dx, dy) 的区间 [i, j-1]
        while (j < m && segs[j].dx == segs[i].dx && segs[j].dy == segs[i].dy) {
            j++;
        }
        
        // 因为按 c 排过序，同组中面积最大必为 尾部 c 减去 头部 c
        long long current_area = segs[j - 1].c - segs[i].c;
        if (current_area > max_area) {
            max_area = current_area;
        }
        
        i = j; // 跳到下一组向量
    }

    if (max_area == 0) {
        cout << "-1\n";
    } else {
        // 核心避坑：不转 double，直接拼接 ".0" 输出
        cout << max_area << ".0\n";
    }

    return 0;
}