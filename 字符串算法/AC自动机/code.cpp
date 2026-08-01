#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// 将 AC 自动机封装进结构体，防止全局变量污染，方便在同一道题里建多个自动机
struct ACAutomaton {
    // MAX_NODES: 所有模式串（黑名单词）的长度总和的最大值 + 1
    // 注意：如果是 10 个长度为 10 的串，开 105 就够了；如果是普通文本匹配题，通常开 100005
    static const int MAX_NODES = 100005; 
    
    int tr[MAX_NODES][26]; // 字典图（状态转移矩阵）
    int fail[MAX_NODES];   // 失配指针（最长公共前后缀）
    
    // 【根据题目灵活修改的属性】：
    // 如果是用来做 DP/矩阵的“避险题”，用 bool danger 记录是不是踩了雷
    // 如果是用来做 文本匹配的“计词题”，用 int cnt 记录这个节点结束了多少个单词
    bool danger[MAX_NODES]; 
    int tot; // 节点总数计数器

    // 1. 初始化清空 (如果有多组测试数据，一定要调用！)
    void init() {
        tot = 0;
        for (int i = 0; i < 26; ++i) tr[0][i] = 0;
        fail[0] = 0;
        danger[0] = false;
    }

    // 2. 开辟新节点时的初始化
    int newNode() {
        ++tot;
        for (int i = 0; i < 26; ++i) tr[tot][i] = 0;
        fail[tot] = 0;
        danger[tot] = false;
        return tot;
    }

    // 3. 插入模式串 (建基础 Trie 树)
    void insert(const string& s) {
        int u = 0; // 从根节点 0 出发
        for (char c : s) {
            int v = c - 'a'; // 假设全是小写字母
            if (!tr[u][v]) {
                tr[u][v] = newNode();
            }
            u = tr[u][v];
        }
        // 走到了字符串结尾，打上危险/计数标记
        danger[u] = true; 
    }

    // 4. 构建 fail 指针与字典图 (核心灵魂)
    void build() {
        queue<int> q;
        // 先把根节点的所有实体第一层儿子入队
        for (int i = 0; i < 26; ++i) {
            if (tr[0][i]) {
                fail[tr[0][i]] = 0; // 第一层儿子的 fail 必然是根
                q.push(tr[0][i]);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // 【高能预警：毒性传染 / 计数累加】
            // 如果 u 的后缀是一个危险词，那么 u 自身也必是危险词！
            danger[u] |= danger[fail[u]];

            for (int i = 0; i < 26; ++i) {
                if (tr[u][i]) {
                    // 有实体儿子：儿子的 fail 指向老爸 fail 的对应儿子
                    fail[tr[u][i]] = tr[fail[u]][i];
                    q.push(tr[u][i]);
                } else {
                    // 无实体儿子（死胡同）：启动“字典图优化”，直接用老爸的 fail 的儿子填平死胡同
                    // 这行代码把“树”变成了“完全有向图”，让转移永远是 O(1) 的！
                    tr[u][i] = tr[fail[u]][i]; 
                }
            }
        }
    }

    // =========================================================
    // 以下是应用层函数，根据题目具体需求选择使用或重写
    // =========================================================

    // 应用场景 A：拿一篇长文章文本，匹配里面出现了多少个模式串
    int query_count(const string& text) {
        int u = 0;
        int total_matches = 0;
        for (char c : text) {
            u = tr[u][c - 'a']; // O(1) 字典图极速转移
            
            // 顺着 fail 指针爬，把所有沿途的后缀全部收割
            // 爬过的节点可以打上标记防止重复计算（这里省略了防重标记，视题目而定）
            int temp = u;
            while (temp > 0) {
                if (danger[temp]) {
                    total_matches++;
                    // 如果题目只要求“是否包含”，这里可以直接 return true;
                }
                temp = fail[temp];
            }
        }
        return total_matches;
    }
    
    // 应用场景 B：导出状态转移矩阵 (用于结合 DP 或矩阵快速幂)
    // 直接遍历 tr[i][c] 即可，无需单独写函数，在外层通过 for(i: 0->tot) for(c: 0->25) 提取。
};