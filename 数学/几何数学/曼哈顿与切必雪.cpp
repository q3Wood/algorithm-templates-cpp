/**
 * 曼哈顿距离与切比雪夫距离
 * 设有两个点 $A(x_1, y_1)$ 和 $B(x_2, y_2)$，则它们之间的曼哈顿距离和切比雪夫距离分别定义如下：
 * - 曼哈顿距离（Manhattan Distance）：$d_M = |x_1 - x_2| + |y_1 - y_2|$
 * - 切比雪夫距离（Chebyshev Distance）：$d_C = \max(|x_1 - x_2|, |y_1 - y_2|)$
 * 如果求曼哈顿距离的复杂度过高，可将每个点的坐标进行变换，变换后的坐标为：
 * - $x' = x + y$
 * - $y' = x - y$
 * 此时，曼哈顿距离可以转化为切比雪夫距离：
 * $d_M = |x_1 - x_2| + |y_1 - y_2| = \max(|x'_1 - x'_2|, |y'_1 - y'_2|) = d_C$
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    int manhattan_distance = abs(x1 - x2) + abs(y1 - y2);
    int chebyshev_distance = max(abs(x1 - x2), abs(y1 - y2));

    cout << manhattan_distance << " " << chebyshev_distance << endl;

    int x1_prime = x1 + y1;
    int y1_prime = x1 - y1;
    int x2_prime = x2 + y2;
    int y2_prime = x2 - y2;
    int man_distance = max(abs(x1_prime - x2_prime), abs(y1_prime - y2_prime));
    cout << man_distance << endl;

    if (manhattan_distance == man_distance) {
        cout << "The transformed Manhattan distance equals the original Manhattan distance." << endl;
    } else {
        cout << "The transformed Manhattan distance does not equal the original Manhattan distance." << endl;
    }
}
