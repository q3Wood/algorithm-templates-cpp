#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 经典问题：给定一个数组，多次查询区间 [L, R] 内有多少个不同的数字。
// 假设 N, Q <= 100000, 数组元素的值 <= 1000000

const int MAXA = 1000005; // 假设数字最大值为 10^6
int cnt[MAXA];            // cnt[i] 记录数字 i 在当前区间出现的次数
int current_ans = 0;      // 记录当前区间的答案（不同数字的个数）
int block_size;           // 分块的大小，通常取 sqrt(N)

// 存储查询的结构体
struct Query {
    int l, r;  // 查询区间的左右端点
    int id;    // 查询的原始顺序编号，用于按原顺序输出答案

    // 重载小于号，实现莫队的奇偶排序规则
    bool operator<(const Query& b) const {
        int block_a = l / block_size;
        int block_b = b.l / block_size;
        
        // 如果左端点不在同一个块内，按左端点所在块升序排列
        if (block_a != block_b) {
            return block_a < block_b;
        }
        
        // 如果在同一个块内，进行奇偶优化
        // 奇数块的右端点升序，偶数块的右端点降序
        if (block_a % 2 == 1) {
            return r < b.r;
        } else {
            return r > b.r;
        }
    }
};

// 将元素加入当前区间
void add(int x) {
    // 如果加入之前次数为0，说明是个新数字，答案+1
    if (cnt[x] == 0) {
        current_ans++;
    }
    cnt[x]++;
}

// 将元素移出当前区间
void remove(int x) {
    cnt[x]--;
    // 如果移出之后次数变为0，说明这个数字没了，答案-1
    if (cnt[x] == 0) {
        current_ans--;
    }
}

int main() {
    // 优化 C++ 的输入输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    // 提示：若在线测试平台，请不要带提示语，这里仅作演示
    cout << "请输入数组长度 N 和查询次数 Q: ";
    if (!(cin >> n >> q)) return 0; // 读取失败则退出

    vector<int> a(n + 1);
    cout << "请输入数组元素: ";
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<Query> queries(q);
    cout << "请输入 " << q << " 个查询(L R): " << "\n";
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    // 1. 初始化块的大小
    block_size = sqrt(n);

    // 2. 对所有查询进行莫队专属排序（自动调用重载的 < 运算符）
    sort(queries.begin(), queries.end());

    // 存储最终答案的数组
    vector<int> ans(q);

    // 3. 初始左右指针（注意 L > R，表示当前是一个空区间）
    int L = 1;
    int R = 0;

    // 4. 处理所有查询
    for (int i = 0; i < q; i++) {
        int qL = queries[i].l;
        int qR = queries[i].r;

        // 核心莫队转移逻辑：指针移动的顺序无所谓，但要小心数组越界
        // 记忆口诀：先加后减。先扩大区间(加)，再缩小区间(减)。
        
        // 当需要向右扩张右边界时
        while (R < qR) {
            R++;
            add(a[R]);
        }
        // 当需要向左扩张左边界时
        while (L > qL) {
            L--;
            add(a[L]);
        }
        // 当需要向左收缩右边界时
        while (R > qR) {
            remove(a[R]);
            R--;
        }
        // 当需要向右收缩左边界时
        while (L < qL) {
            remove(a[L]);
            L++;
        }

        // 记录当前查询的答案到原来的编号位置
        ans[queries[i].id] = current_ans;
    }

    // 5. 按原输入顺序输出结果
    cout << "--- 输出结果 ---\n";
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}