#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 传入原字符串，返回该字符串“最小表示”的起始下标 (0-based)
int get_min_representation(string s) {
    int n = s.length();
    // 经典套路：复制一倍，处理环形问题
    s += s; 
    
    int i = 0, j = 1, k = 0;
    
    // 只要两个指针都没有越过第一圈，且匹配长度不到 n
    while (i < n && j < n && k < n) {
        if (s[i + k] == s[j + k]) {
            k++;
        } else {
            // 谁大，谁就失去资格，并且向后飞跃 k+1 步
            if (s[i + k] > s[j + k]) {
                i = i + k + 1;
            } else {
                j = j + k + 1;
            }
            
            // 特判：如果跳跃后两人撞车了，强行错开
            if (i == j) j++;
            
            // 匹配长度清零，重新开始下一轮比拼
            k = 0; 
        }
    }
    
    // 剩下的那个没出局的、更靠前的指针，就是真正的起点
    return min(i, j);
}

// 获取最小表示的完整字符串 (配合上面的函数使用)
string get_min_string(string s) {
    int start_idx = get_min_representation(s);
    return s.substr(start_idx) + s.substr(0, start_idx);
}

int main() {
    string str = "caba";
    cout << "原字符串: " << str << "\n";
    cout << "最小表示: " << get_min_string(str) << "\n";
    return 0;
}