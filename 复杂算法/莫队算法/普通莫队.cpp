// 静态区间众数出现次数
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_A = 1000005;
const int MAX_N = 10005; 

int cnt[MAX_A]; // cnt[x] 表示数值 x 出现的次数
int ccnt[MAX_N]; // ccnt[f] 表示出现次数为 f 的数值有多少个
int current_max = 0;
int block_size;

struct Query {
    int l, r, id;
};

bool compare(const Query& a, const Query& b) {
    if (a.l / block_size != b.l / block_size)
        return a.l < b.l;
    return ((a.l / block_size) & 1) ? a.r < b.r : a.r > b.r;
}

// 增加一个元素
inline void add(int x) {
    ccnt[cnt[x]]--;     
    cnt[x]++;            
    ccnt[cnt[x]]++;      
    if (cnt[x] > current_max) {
        current_max = cnt[x]; 
    }
}

// 删除一个元素
inline void del(int x) {
    ccnt[cnt[x]]--;      
    if (cnt[x] == current_max && ccnt[current_max] == 0) {
        current_max--;
    }
    cnt[x]--;            
    ccnt[cnt[x]]++;      
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    block_size = max(1, (int)(n / sqrt(q)));
    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), compare);

    vector<int> ans(q);
    int L = 1, R = 0;
    
    for (int i = 0; i < q; ++i) {
        int ql = queries[i].l;
        int qr = queries[i].r;
        // 先扩大，再缩小
        while (L > ql) add(a[--L]);
        while (R < qr) add(a[++R]);
        while (L < ql) del(a[L++]);
        while (R > qr) del(a[R--]);

        ans[queries[i].id] = current_max;
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}