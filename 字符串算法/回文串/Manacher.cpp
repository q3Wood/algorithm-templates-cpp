#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

vector<int> halfLen;
void Manacher(string dfsStr) {
    string t = "^";
    for (char c : dfsStr) {
        t += '#';
        t += c;
    }
    t += "#$";

    halfLen.resize((t.size() - 2));
    halfLen[1] = 1;

    int boxM = 0, boxR = 0;
    for (int i = 2; i < halfLen.size(); i++) { 
        int hl = 1;
        if (i < boxR) {
            hl = min(halfLen[boxM * 2 - i], boxR - i);
        }
        // 暴力扩展
        // 算法的复杂度取决于这部分执行的次数
        // 由于扩展之后 boxR 必然会更新（右移），且扩展的的次数就是 boxR 右移的次数
        // 因此算法的复杂度 = O(len(t)) = O(n)
        while (t[i - hl] == t[i + hl]) {
            hl++;
            boxM = i;
            boxR = i + hl;
        }
        halfLen[i] = hl;
    }
}
/**
 * 当 dfsStr 的长度为 n 时，t 的长度为 2n + 3
 * 其中 t[0] = ^, t[2n + 2] = $, t[1] = #, t[2n + 1] = #
 * 设 hl = halfLen[i], 则在t中以 i 为中心的回文串的长度为 hl*2-1
 * 对应的 dfsStr 中的回文串长度为 hl-1
 * 由于 t 中 # 的数量总是比字母的数量多 1，因此 hl-1 >= 0
 */


// t于dfsStr下标的对应关系为，原串为i时，t中对应的下标为i*2+2
// 如果在t中指向一个真实字符，下标为i时，dfsStr中对应的下标为(i-2)/2


// 判断左闭右开区间 [l,r) 是否为回文串  0<=l<r<=n
// 根据下标转换关系得到 dfsStr 的 [l,r) 子串在 t 中对应的回文中心下标为 l+r+1
// 需要满足 halfLen[l + r + 1] - 1 >= r - l，即 halfLen[l + r + 1] > r - l

// [l ,r]  l*2+2 r*2+2   对应h数组  h[l+r+2] - 1 >= r - l + 1  ==>   h[l+r+1] > r - l + 1 
bool isPalindrome(int l, int r) {
    return halfLen[l + r + 2] > r - l + 1;
}

// 返回最长回文子串的长度
int longestPalindrome() {
    int maxLen = 0;
    for (int i = 1; i < halfLen.size(); i++) {
        maxLen = max(maxLen, halfLen[i] - 1);
    }
    return maxLen;
}

// 返回所有回文子串的数量
int countAllPalindromes() {
    int count = 0;
    for (int i = 1; i < halfLen.size(); i++) {
        count += halfLen[i] / 2;
    }
    return count;
}


int main()
{
    cout << "Hello World!\n";
}