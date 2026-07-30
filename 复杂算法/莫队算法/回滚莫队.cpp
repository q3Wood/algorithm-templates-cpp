#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector> 

using namespace std;
const int MAXN = 500005; 

int n, q, block_size;
int a[MAXN];       
int belong[MAXN];   

int cnt[MAXN];       
int brute_cnt[MAXN]; // 用于暴力计算的计数数组
int ans_arr[MAXN];  // 存储每个查询的答案
int current_max = 0; 

struct Query {
    int l, r, id;
    
    inline bool operator<(const Query& o) const {
        return belong[l] == belong[o.l] ? r < o.r : belong[l] < belong[o.l];
    }
} queries[MAXN];


inline int brute_force(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; ++i) {
        brute_cnt[a[i]]++; 
        res = res > brute_cnt[a[i]] ? res : brute_cnt[a[i]]; 
    }
    for (int i = l; i <= r; ++i) brute_cnt[a[i]]--;
    return res;
}

inline void add_right(int val) {
    cnt[val]++;
    current_max = current_max > cnt[val] ? current_max : cnt[val];
}

inline void add_left(int val) {
    cnt[val]++;
    current_max = current_max > cnt[val] ? current_max : cnt[val];
}

void solve() {
    if (!(cin >> n >> q) || n == 0) return; 
    
    block_size = max(1, (int)(n / sqrt(max(1, q)))); 
    
    vector<int> b; 
    b.reserve(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b.push_back(a[i]);
        belong[i] = (i - 1) / block_size + 1; 
    }
    
    // 离散化
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
    
    for (int i = 1; i <= q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }
    
    sort(queries + 1, queries + q + 1);
    
    int last_block = 0; 
    int R = 0, block_right_bound = 0;
    
    for (int i = 1; i <= q; ++i) {
        int qL = queries[i].l;
        int qR = queries[i].r;
        int qId = queries[i].id;
        int cur_block = belong[qL];
        
        if (belong[qL] == belong[qR]) {
            ans_arr[qId] = brute_force(qL, qR);
            continue; 
        }
        
        if (last_block != cur_block) {
            while(R > block_right_bound) {
                cnt[a[R]]--;
                R--;
            }
            // 重新定位基准点
            block_right_bound = cur_block * block_size;
            if (block_right_bound > n) block_right_bound = n;
            
            R = block_right_bound; // R 放在块的最右端
            current_max = 0;       
            
            last_block = cur_block;
        }

        while (R < qR) {
            R++;
            add_right(a[R]);
        }
        
        int tmp_max = current_max; 
        int L = block_right_bound + 1; // 左指针基准位置
        
        while (L > qL) {
            L--;
            add_left(a[L]); 
        }
    
        ans_arr[qId] = current_max;
        
        while (L <= block_right_bound) {
            cnt[a[L]]--;
            L++;
        }
        current_max = tmp_max; 
    }
    
    for (int i = 1; i <= q; ++i) {
        cout << ans_arr[i] << "\n"; 
    }
}

int main() {
    // 优化 cin 和 cout 的速度，防止在 OJ 上 TLE
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}