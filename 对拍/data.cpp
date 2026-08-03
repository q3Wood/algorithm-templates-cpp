// 文件名：data.cpp
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long rnd(long long L, long long R) {
    return L + rng() % (R - L + 1);
}

int main() {
    // 生成两个 1 到 10 之间的随机整数
    long long a = rnd(1, 10);
    long long b = rnd(1, 10);
    
    // 把生成的随机数按题目输入格式打印出来
    cout << a << " " << b << "\n";
    return 0;
}