/**
 * 例题：https://www.luogu.com.cn/problem/P4168
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 40005; // 估算题目 N 的大小
const int MAXB = 205;   // 估算 sqrt(N) 的大小，即块的数量

int a[MAXN];        // 离散化后的数组
int origin_val[MAXN]; // origin_val[i] 记录离散化后的数字 i 对应的原始真实值
int belong[MAXN];   // 每个元素属于哪一块
int L[MAXB], R[MAXB]; // 每一块的左右边界

// pos[x] 记录离散化后的数字 x 出现的所有下标 (用于快速计算某个区间内 x 出现的次数)
vector<int> pos[MAXN]; 
// mode[i][j] 记录第 i 块到第 j 块的众数 (离散化后的值)
int mode[MAXB][MAXB];  
int cnt[MAXN]; // 预处理时统计频次的桶

// 快速计算离散化数字 x 在下标区间 [l, r] 中出现的次数
int count_occurrences(int l, int r, int x) {
    auto it_r = upper_bound(pos[x].begin(), pos[x].end(), r);
    auto it_l = lower_bound(pos[x].begin(), pos[x].end(), l);
    return it_r - it_l;
}

// 求解区间 [l, r] 的众数 (返回原始真实值)
int query(int l, int r) {
    int p = belong[l], q = belong[r];
    int best_val = 0, max_cnt = 0;

    // 情况 A：在同一个块或相邻块，纯暴力统计所有元素
    if (q - p <= 1) {
        for (int i = l; i <= r; i++) {
            int current_cnt = count_occurrences(l, r, a[i]);
            // 众数规则：出现次数最多，次数相同时取数值最小的
            if (current_cnt > max_cnt || (current_cnt == max_cnt && origin_val[a[i]] < origin_val[best_val])) {
                max_cnt = current_cnt;
                best_val = a[i];
            }
        }
        return origin_val[best_val];
    }

    // 情况 B：中间有完整的块
    best_val = mode[p + 1][q - 1]; // 候选人 1：中间完整块的预处理众数
    max_cnt = count_occurrences(l, r, best_val); // 计算这个候选人在整个大区间里的总票数

    // 候选人 2：左边散块的元素
    for (int i = l; i <= R[p]; i++) {
        int current_cnt = count_occurrences(l, r, a[i]);
        if (current_cnt > max_cnt || (current_cnt == max_cnt && origin_val[a[i]] < origin_val[best_val])) {
            max_cnt = current_cnt;
            best_val = a[i];
        }
    }
    
    // 候选人 3：右边散块的元素
    for (int i = L[q]; i <= r; i++) {
        int current_cnt = count_occurrences(l, r, a[i]);
        if (current_cnt > max_cnt || (current_cnt == max_cnt && origin_val[a[i]] < origin_val[best_val])) {
            max_cnt = current_cnt;
            best_val = a[i];
        }
    }

    return origin_val[best_val];
}

// --- 初始化部分 (极简示意) ---
void build(int n) {
    int block_size = sqrt(n);
    int block_count = n / block_size + (n % block_size != 0 ? 1 : 0);
    
    // 划分块
    for (int i = 1; i <= block_count; i++) {
        L[i] = (i - 1) * block_size + 1;
        R[i] = min(i * block_size, n);
    }
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / block_size + 1;

    // 预处理 mode[i][j] (核心难点)
    for (int i = 1; i <= block_count; i++) {
        // 每次计算新的一行，桶要清零
        for(int k = 1; k <= n; k++) cnt[k] = 0; 
        
        int current_best = 0, current_max = 0;
        for (int j = i; j <= block_count; j++) {
            // 将第 j 块的元素加入统计
            for (int k = L[j]; k <= R[j]; k++) {
                cnt[a[k]]++;
                if (cnt[a[k]] > current_max || (cnt[a[k]] == current_max && origin_val[a[k]] < origin_val[current_best])) {
                    current_max = cnt[a[k]];
                    current_best = a[k];
                }
            }
            mode[i][j] = current_best;
        }
    }
}