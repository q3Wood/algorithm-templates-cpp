/**
 * 例题：https://www.luogu.com.cn/record/284560256
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100005;

// 原始数据
long long a[MAXN];

// 分块核心维护结构
int block_size;     // 每一块的大小，通常等于 sqrt(n)
int block_count;    // 块的总数量
int belong[MAXN];   // belong[i] 表示原数组第 i 个元素属于第几块
int L[MAXN], R[MAXN]; // L[i] 和 R[i] 分别表示【第 i 块】的左边界和右边界下标

// 块的统计信息
long long sum[MAXN];  // sum[i] 表示【第 i 块】的元素总和
long long lazy[MAXN]; // lazy[i] 表示【第 i 块】整体被加了多少（懒标记）

// 1. 初始化建块 (极其重要，通常在读入数据后执行)
void build(int n) {
    block_size = sqrt(n);
    // 向上取整算出总块数
    block_count = n / block_size + (n % block_size != 0 ? 1 : 0); 

    for (int i = 1; i <= block_count; i++) {
        L[i] = (i - 1) * block_size + 1;
        R[i] = i * block_size;
    }
    R[block_count] = n; // ⚠️避坑：最后一块可能不满，右边界必须强行截断为 n

    for (int i = 1; i <= n; i++) {
        belong[i] = (i - 1) / block_size + 1;
        sum[belong[i]] += a[i]; // 预处理每个块的和
    }
}

// 2. 区间加上 val
void update(int l, int r, long long val) {
    int p = belong[l], q = belong[r]; // 算出左右端点分别在哪个块
    
    // 情况 A：如果在同一个块内，没有完整的块，纯暴力！
    if (p == q) {
        for (int i = l; i <= r; i++) {
            a[i] += val;
            sum[p] += val;
        }
    } 
    // 情况 B：跨越了多个块
    else {
        // 1. 暴力处理左边散块 (从 l 到 p 块的右边界)
        for (int i = l; i <= R[p]; i++) { a[i] += val; sum[p] += val; }
        
        // 2. 优雅处理中间的完整块 (打懒标记)
        for (int i = p + 1; i <= q - 1; i++) { lazy[i] += val; }
        
        // 3. 暴力处理右边散块 (从 q 块的左边界到 r)
        for (int i = L[q]; i <= r; i++) { a[i] += val; sum[q] += val; }
    }
}

// 3. 区间求和
long long query(int l, int r) {
    int p = belong[l], q = belong[r];
    long long ans = 0;

    // 情况 A：在同一个块内
    if (p == q) {
        for (int i = l; i <= r; i++) {
            // ⚠️避坑：单个元素的真实值 = 自己的值 + 它所属块的懒标记
            ans += a[i] + lazy[p]; 
        }
    } 
    // 情况 B：跨越了多个块
    else {
        // 1. 左边散块
        for (int i = l; i <= R[p]; i++) { ans += a[i] + lazy[p]; }
        
        // 2. 中间完整块 (块总和 + 块的懒标记 * 块的元素个数)
        for (int i = p + 1; i <= q - 1; i++) { 
            ans += sum[i] + lazy[i] * (R[i] - L[i] + 1); 
        }
        
        // 3. 右边散块
        for (int i = L[q]; i <= r; i++) { ans += a[i] + lazy[q]; }
    }
    return ans;
}