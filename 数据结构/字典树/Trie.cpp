#include <bits/stdc++.h>
using namespace std;
// 经典字符串 Trie
const int MAX_NODE = 100005; // 估算总字符数
int ch[MAX_NODE][26];        // 节点数组，26表示小写字母
int cnt[MAX_NODE];           // 记录以该节点结尾的单词数量
int idx = 0;                 // 节点编号分配器

// 多组测试数据时，必须清空 ch 数组和 idx！( memset(ch, 0, sizeof(ch));  memset(cnt, 0, sizeof(cnt)); idx = 0; )

void insert(string& s) {
    int p = 0; // 从根节点(0)开始
    for (char c : s) {
        int u = c - 'a';
        if (!ch[p][u]) ch[p][u] = ++idx; // 如果没有这个分叉，就新建一个节点
        p = ch[p][u]; // 顺着树往下走
    }
    cnt[p]++; // 走到字符串末尾，做个标记
}

int query(string& s) {
    int p = 0;
    for (char c : s) {
        int u = c - 'a';
        if (!ch[p][u]) return 0; // 只要断了，说明不存在这个前缀
        p = ch[p][u];
    }
    return cnt[p]; // 返回匹配的数量
}

// 查找字符串 s 的最短唯一前缀, 如果没有唯一前缀，则返回整个字符串
string findPrefix(string& word) {
    int p = 0;
    int len = 0; 
    for (char c : word) {
        int u = c - 'a';
        len++; 
        if (!ch[p][u]) return word; 
        p = ch[p][u];
        if (cnt[p] != 0) return word.substr(0, len); 
    }
    return word; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}