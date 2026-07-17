#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 定义二维点/向量结构体
struct Point {
    long long x, y;
    
    Point(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
    
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 重命名，使得语义更清晰 (点和向量在二维坐标系下本质相同)
typedef Point Vector;

// 核心运算 1：求距离的平方 (极力避免开根号和浮点数误差)
long long dist2(const Point& A, const Point& B) {
    long long dx = A.x - B.x;
    long long dy = A.y - B.y;
    return dx * dx + dy * dy;
}

// 核心运算 2：向量点乘 (Dot Product) 点乘表示：|a||b|cos(θ)，表示投影
// 用途：判断垂直(结果为0)、夹角钝/锐
long long dotProduct(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

// 核心运算 3：向量叉乘 (Cross Product) 叉乘表示：|a||b|sin(θ), 表示面积
// 用途：判断共线(结果为0)、计算面积、判断转向
long long crossProduct(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}


// ==========================================
// 2. 三角形家族判定 (给定 3 个点)
// ==========================================

// 判断三点是否能构成三角形 (即判断三点是否不共线)
bool isTriangle(const Point& A, const Point& B, const Point& C) {
    Vector AB = B - A;
    Vector AC = C - A;
    // 叉乘不为 0 则不共线，能构成三角形
    return crossProduct(AB, AC) != 0;
}

// 判断是否为直角三角形 (使用点乘)
bool isRightTriangle(const Point& A, const Point& B, const Point& C) {
    if (!isTriangle(A, B, C)) return false;
    
    Vector AB = B - A;
    Vector BC = C - B;
    Vector CA = A - C;
    
    // 任意两条边垂直(点乘为0)即为直角三角形
    return dotProduct(AB, BC) == 0 || 
           dotProduct(BC, CA) == 0 || 
           dotProduct(CA, AB) == 0;
}

// ==========================================
// 3. 四边形家族判定 (给定 4 个点)
// 假设点已经按顺时针或逆时针顺序给出：A, B, C, D
// ==========================================

// 判断是否为平行四边形 (对角线互相平分)
// 巧解：不需要除以2，直接比较坐标和
bool isParallelogram(const Point& A, const Point& B, const Point& C, const Point& D) {
    return (A.x + C.x == B.x + D.x) && (A.y + C.y == B.y + D.y);
}

// 判断是否为菱形 (平行四边形 + 对角线互相垂直)
bool isRhombus(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (!isParallelogram(A, B, C, D)) return false;
    
    Vector AC = C - A;
    Vector BD = D - B;
    // 对角线互相垂直
    return dotProduct(AC, BD) == 0;
    
    // 备用写法：或者判断相邻两边距离平方相等
    // return dist2(A, B) == dist2(B, C);
}

// 判断是否为矩形 (平行四边形 + 对角线长度相等)
bool isRectangle(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (!isParallelogram(A, B, C, D)) return false;
    
    // 对角线长度平方相等
    return dist2(A, C) == dist2(B, D);
    
    // 备用写法：或者判断存在一个直角
    // Vector AB = B - A;
    // Vector BC = C - B;
    // return dotProduct(AB, BC) == 0;
}

// 判断是否为正方形 (既是矩形又是菱形)
bool isSquareOrdered(const Point& A, const Point& B, const Point& C, const Point& D) {
    return isRectangle(A, B, C, D) && isRhombus(A, B, C, D);
}

// ==========================================
// 4. 特别放送：无序 4 点判定正方形
// (六条边排序法，无视点的输入顺序)
// ==========================================
bool isSquareUnordered(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vector<long long> d(6);
    d[0] = dist2(p1, p2);
    d[1] = dist2(p1, p3);
    d[2] = dist2(p1, p4);
    d[3] = dist2(p2, p3);
    d[4] = dist2(p2, p4);
    d[5] = dist2(p3, p4);
    
    sort(d.begin(), d.end());
    
    // 正方形特点：前 4 条边长度平方相等 (且大于0)，后 2 条对角线长度平方相等
    if (d[0] == 0) return false; // 存在重合点
    
    return d[0] == d[1] && d[1] == d[2] && d[2] == d[3] && 
           d[4] == d[5] && 
           d[3] < d[4]; // 边长必须小于对角线
}


// ==========================================
// 5. 应对无序点的万能杀招：凸包排序 (极角排序)
// ==========================================
// 用于将无序的多个点，按逆时针顺序排成一个凸多边形
Point base_point; // 全局基准点，用于极角排序

// 比较函数：按照相对于 base_point 的极角大小排序
bool polarCompare(const Point& p1, const Point& p2) {
    Vector v1 = p1 - base_point;
    Vector v2 = p2 - base_point;
    long long cross = crossProduct(v1, v2);
    // 叉乘大于0，说明 v2 在 v1 的逆时针方向，v1 排在前面
    if (cross > 0) return true;
    if (cross < 0) return false;
    // 如果极角相同（共线），距离基准点近的排在前面
    return dist2(base_point, p1) < dist2(base_point, p2);
}

// 将无序的 4 个点按逆时针重新排列
// 排序后，你就可以放心地使用前面那些 isRectangle, isRhombus 等函数了
void sortPoints(vector<Point>& pts) {
    if (pts.size() != 4) return;
    
    // 1. 找到左下角的点作为基准点 (y最小，若y相同则x最小)
    int min_idx = 0;
    for (int i = 1; i < 4; i++) {
        if (pts[i].y < pts[min_idx].y || 
           (pts[i].y == pts[min_idx].y && pts[i].x < pts[min_idx].x)) {
            min_idx = i;
        }
    }
    
    // 把基准点交换到第 0 个位置
    swap(pts[0], pts[min_idx]);
    base_point = pts[0];
    
    // 2. 对剩下的 3 个点按照极角排序
    sort(pts.begin() + 1, pts.end(), polarCompare);
}


// 简单测试样例
int main() {
    Point A(0, 0), B(2, 0), C(2, 2), D(0, 2);
    
    cout << "A, B, C 是否构成直角三角形? " 
         << (isRightTriangle(A, B, C) ? "Yes" : "No") << endl;
         
    cout << "A, B, C, D (按顺序) 是否构成正方形? " 
         << (isSquareOrdered(A, B, C, D) ? "Yes" : "No") << endl;
         
    // 打乱顺序测试
    cout << "无序点 A, C, B, D 是否构成正方形? " 
         << (isSquareUnordered(A, C, B, D) ? "Yes" : "No") << endl;

    return 0;
}