#include <bits/stdc++.h>
using namespace std;

// 判断两个矩形是否相交, rec1 和 rec2 分别是两个矩形的左下角和右上角坐标[x1, y1,
// x2, y2]
bool check(vector<int>& rec1, vector<int>& rec2) {
    return min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) &&
           min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]);
}