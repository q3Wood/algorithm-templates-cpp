#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 建议不要声明全局 vector，容易在多组测试数据时忘记清空引发诡异 Bug
// 改为通过参数传入引用

/* 
 * 核心原版 Next 数组 (必须掌握！)
 * 物理意义：nxt[i] 表示 t[0...i-1] 这个前缀子串中，最长公共前后缀的长度。
 * 适用场景：求最短循环节、求前后缀重合长度、KMP 基础匹配。
 */
void get_next(const string& t, vector<int>& nxt) {
    int n = t.size();
    // ⚠️ 极其关键的修改 1：数组大小开到 n + 1
    nxt.assign(n + 1, 0); 
    
    nxt[0] = -1;
    int j = 0;
    int k = -1;
    
    // ⚠️ 极其关键的修改 2：循环条件改为 j < n，必须算出 nxt[n]
    while (j < n) {
        if (k == -1 || t[j] == t[k]) {
            k++;
            j++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }
    }
}

/*
 * 优化版 NextVal 数组 
 * 物理意义：被破坏，纯粹为了跳过连续相同的字符。
 * 适用场景：仅限单纯的子串匹配 (例如 LeetCode 28)，防止模式串形如 "AAAAAB" 时退化。
 */
void get_nextVal(const string& t, vector<int>& nxt) {
    int n = t.size();
    nxt.assign(n + 1, 0);
    
    nxt[0] = -1;
    int j = 0;
    int k = -1;
    
    while (j < n) {
        if (k == -1 || t[j] == t[k]) {
            j++; 
            k++;
            // 优化核心逻辑，走到结尾时也要判断，防止越界
            if (j < n && t[k] != t[j]) {
                nxt[j] = k;
            } else {
                nxt[j] = nxt[k];
            }
        } else {
            k = nxt[k];
        }
    }
}

// 标准 KMP 匹配
int KMP(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    if (m == 0) return 0;
    
    vector<int> nxt;
    get_next(t, nxt); // 使用原版或优化版均可用于匹配
    
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || s[i] == t[j]) {
            i++; 
            j++;
        } else {
            j = nxt[j];
        }
    }
    
    if (j == m) return i - m;
    return -1;
}

int main() {
    string s = "ababcabcacbab", t = "aaaab";
    cout << "首次匹配位置: " << KMP(s, t) << "\n";
    
    // 演示：求最短循环节 (必须用原版 get_next)
    string period_str = "abababab";
    vector<int> nxt;
    get_next(period_str, nxt);
    
    int len = period_str.size();
    // 公式：L - next[L]。检查是否能整除
    if (nxt[len] > 0 && len % (len - nxt[len]) == 0) {
        cout << period_str << " 的最短循环节长度为: " << len - nxt[len] << "\n";
    }
    
    return 0;
}