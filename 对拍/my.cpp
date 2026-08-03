// 文件名：my.cpp
#include <iostream>

using namespace std;

int main() {
    long long a, b;
    if (cin >> a >> b) {
        // 故意埋下的雷：在几百组数据里，只有碰到 7+7 才会算错
        if (a == 7 && b == 7) {
            cout << 15 << "\n"; 
        } else {
            cout << a + b << "\n";
        }
    }
    return 0;
}