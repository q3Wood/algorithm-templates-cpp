#include <iostream>
#include <iomanip>

using namespace std;

// 1. 点与向量的通用结构体
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // 向量加法：点 + 向量 = 新的点
    Point operator+(const Point& b) const {
        return Point(x + b.x, y + b.y);
    }

    // 向量减法：点 - 点 = 向量
    Point operator-(const Point& b) const {
        return Point(x - b.x, y - b.y);
    }

    // 数乘：向量 * 标量
    Point operator*(double k) const {
        return Point(x * k, y * k);
    }
};

using Vector = Point; // 在几何中，向量和点的表示是一样的

// 2. 向量点积 (Dot Product)
double dot(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y;
}

// 3. 向量模长的平方 |v|^2
double norm_sq(const Vector& a) {
    return dot(a, a);
}

// 4. 求点 P 在直线 UV 上的投影（垂足）
Point projection(const Point& P, const Point& U, const Point& V) {
    Vector v = V - U;      // 直线方向向量 UV
    Vector u = P - U;      // 向量 UP
    double k = dot(u, v) / norm_sq(v); // 投影比例系数
    return U + v * k;      // 垂足坐标
}

void solve() {
    Point P, U, V;
    cin >> P.x >> P.y >> U.x >> U.y >> V.x >> V.y;

    Point Q = projection(P, U, V);

    cout << fixed << setprecision(7) << Q.x << " " << Q.y << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}