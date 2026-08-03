# 算法竞赛代码字典 (Team Reference Document)

# 根目录杂项

**My_Template_Dictionary.md**

```md

```

**clear_up.py**

```py
import os

# 设置你要扫描的代码所在的最外层目录，'.' 表示当前脚本所在的目录
ROOT_DIR = '.'  
# 生成的整合文档的文件名
OUTPUT_FILE = 'My_Template_Dictionary.md'

# 过滤掉不需要打印的文件夹和文件
IGNORE_DIRS = {'.vscode', '.git', '.idea', 'build', '大纲'}
# 只抓取这些后缀的文件，新增了 .md
ALLOWED_EXTS = {'.cpp', '.c', '.java', '.py', '.md'}

def generate_markdown():
    # 使用 utf-8 编码打开输出文件，防止中文乱码
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as outfile:
        
        # 写入文档大标题
        outfile.write('# 算法竞赛代码字典 (Team Reference Document)\n\n')
        
        # os.walk 会自动帮你递归遍历所有的文件夹和子文件夹
        for root, dirs, files in os.walk(ROOT_DIR):
            
            # 过滤掉不需要的文件夹（修改 dirs 会影响 os.walk 的遍历）
            dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
            
            # 对文件夹按拼音/字母排序，让打印出来的目录更规整
            dirs.sort()
            files.sort()
            
            # 找出当前目录下所有符合后缀要求的代码文件
            valid_files = [f for f in files if os.path.splitext(f)[1] in ALLOWED_EXTS]
            
            if not valid_files:
                continue # 如果这个文件夹里没代码，就跳过
                
            # 计算当前所在的文件夹深度，用来决定用几级 Markdown 标题
            rel_path = os.path.relpath(root, ROOT_DIR)
            if rel_path == '.':
                depth = 1
                folder_name = "根目录杂项"
            else:
                depth = rel_path.count(os.sep) + 2 # 子文件夹从二级标题开始
                # 修改这里：使用完整的路径替换掉单一文件夹名，让层级更清晰
                folder_name = rel_path.replace(os.sep, ' / ')
            
            # 根据深度生成 Markdown 标题 (比如 ## 数据结构, ### 线段树)
            heading = '#' * min(depth, 6) # 最多到 6 级标题
            outfile.write(f'{heading} {folder_name}\n\n')
            
            for file in valid_files:
                file_path = os.path.join(root, file)
                file_ext = os.path.splitext(file)[1][1:] # 获取扩展名，如 'cpp'
                
                # 写入文件名作为小标题
                outfile.write(f'**{file}**\n\n')
                
                # 开始写入代码块
                outfile.write(f'```{file_ext}\n')
                try:
                    # 读取 C++ 文件内容并写入
                    with open(file_path, 'r', encoding='utf-8') as infile:
                        outfile.write(infile.read())
                except Exception as e:
                    outfile.write(f'// 读取文件出错: {e}\n')
                outfile.write('\n```\n\n')
                
    print(f'✅ 成功！已将所有代码整合到 {OUTPUT_FILE} 中。')

if __name__ == '__main__':
    generate_markdown()
```

**template.cpp**

```cpp
// template Created by q3Wood on 2026/7/7
#include <bits/stdc++.h>
#include <numeric>
#include <sys/types.h>

#define int long long
#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define i128 __int128
#define uint unsigned long long

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;
const int INF = 0x3f3f3f3f3f3f3f3f;
const int knight_moves[8][2] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                                {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int dirs[8][2] = {{0, 1}, {1, 0},  {0, -1}, {-1, 0},
                        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
struct node {
    int x, y;
    bool operator<(const node& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};
void solve() {

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```

### C++常用库函数 / STL

**priotity_queue.md**

```md
**优先队列定义结构体排序顺序**
```cpp
struct Node {
    int id, val;
    bool operator<(const Node& other) const {
        // 优先队列， 按 val 从大到小排序, 从小到大改为 return val > other.val;
        return val < other.val; 
    }
};
priority_queue<Node> pq;
```
```

**set.md**

```md
### set/multiset
```cpp
#include <iostream>
#include <set>

using namespace std;

int main() {
    // 默认从小到大排序 (升序)
    set<int> s;
    multiset<int> ms;

    // 1. 插入元素
    s.insert(5);
    s.insert(3);
    s.insert(5); // set 会忽略这个重复的 5
    
    ms.insert(5);
    ms.insert(3);
    ms.insert(5); // multiset 会保留两个 5

    // 2. 查找元素 (返回迭代器)
    auto it1 = s.find(3); 
    if (it1 != s.end()) {
        cout << "在 set 中找到了 3\n";
    }

    // 3. 统计个数
    cout << s.count(5) << "\n";  // 输出 1
    cout << ms.count(5) << "\n"; // 输出 2

    // 4. 获取最值 (begin 是最小值，rbegin 是最大值)
    cout << "最小值: " << *s.begin() << "\n";
    cout << "最大值: " << *s.rbegin() << "\n";

    return 0;
}
```

#### lower_bound 和 upper_bound
> lower_bound 返回第一个不小于给定值的迭代器，upper_bound 返回第一个大于给定值的迭代器。
```cpp
multiset<int> ms = {10, 20, 30, 30, 40};

auto it = ms.lower_bound(30); // 指向第一个 30
auto it2 = ms.upper_bound(30); // 指向 40
// set也可以使用 lower_bound 和 upper_bound
```

#### erase 删除元素
```cpp
multiset<int> ms = {10, 20, 30, 30, 30, 40};
ms.erase(30); 
// 惨剧发生：集合里的 3 个 30 全部灰飞烟灭！
// 剩下的元素：{10, 20, 40}

multiset<int> ms = {10, 20, 30, 30, 30, 40};
auto it = ms.find(30); // 找到其中一个 30 的迭代器, 用lower_bound也可以
if (it != ms.end()) {
    ms.erase(it); 
}
// 完美执行：只删掉了一个 30
// 剩下的元素：{10, 20, 30, 30, 40}
```

#### set/multiset 的自定义排序规则
```cpp
// 基础类型
set<int, greater<int>> s; // 传入 greater<int> 即可降序

// 结构体
struct Node {
    int id;
    int score;
    // 必须是 const 成员函数，且参数必须是 const 引用
    bool operator<(const Node& other) const {
        return score > other.score; // 按分数降序
    }
};
set<Node> node_set;
```

#### 其它常用库函数
```cpp
set<int> s = {1, 2, 3};
if (s.contains(2)) {
    cout << "2 在集合中\n";
}

multiset<int> ms = {10, 20, 30, 30, 30, 40};

auto range = ms.equal_range(30); // 返回一个 pair，表示所有等于 30 的元素的范围

// 遍历所有的 30
for (auto it = range.first; it != range.second; ++it) {
    cout << *it << " "; 
}

// empty, size, clear, swap 等函数也可以使用

// merge: 将一个 set/multiset 的元素合并到另一个 set/multiset 中
set<int> s1 = {1, 2, 3};
set<int> s2 = {3, 4, 5};
s1.merge(s2); // s1 现在包含 {1, 2, 3, 4, 5}，s2 变为空
```

```

**sort.md**

```md
### 定义全局数据
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 1. 对 vector 排序
    vector<int> v = {4, 1, 3, 5, 2};
    // 2. 对普通数组排序
    int a[] = {4, 1, 3, 5, 2};
    int n = 5;
}
```
### 基础用法
```cpp

sort(v.begin(), v.end()); // 结果: 1, 2, 3, 4, 
sort(a, a + n); // 结果: 1, 2, 3, 4, 5

```

### 自定义排序规则
```cpp
// 降序排列 (使用 lambda)
sort(v.begin(), v.end(), [](int x, int y) {
    return x > y; // 谁大谁排在前面
});

// 结构体排序
struct Node {
    int id;
    int score;
};
vector<Node> nodes = {{1, 90}, {2, 100}, {3, 90}};

// 按照分数降序排，分数相同按 id 升序排
sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
    if (a.score != b.score) {
        return a.score > b.score; 
    }
    return a.id < b.id;
});
```
### 结构体重载 `<` 运算符
```cpp
struct Node {
    int id;
    int score;

    // 重载 < 运算符
    bool operator<(const Node& other) const {
        if (score != other.score) {
            return score > other.score; // 分数降序
        }
        return id < other.id; // 分数相同按 id 升序
    }
};
vector<Node> nodes = {{1, 90}, {2, 100}, {3, 90}};
// 直接使用 sort 排序
sort(nodes.begin(), nodes.end());
```

### 下标排序
```cpp
vector<int> v = {4, 1, 3, 5, 2};
// 创建下标数组
vector<int> idx(v.size());
iota(idx.begin(), idx.end(), 0); // 初始化下标数组为 0, 1, 2, ...
// 按照下标排序
sort(idx.begin(), idx.end(), [&](int i, int j) {
    return v[i] < v[j]; // 按照 v 的值排序下标
});
// 排序后的下标数组 idx 表示 v 中元素的升序排列
// 结果：idx = {1，4，2，0，3} 对应 v 的值为 {1, 2, 3, 4, 5}
```
```

**string.md**

```md
**字符串按空格分割**
```cpp
string str = "id0 id1 id2";
stringstream ss(str);
string token;
vector<string> tokens;
// 1.
while (ss >> token) {
    tokens.push_back(token);
}
// 2.
while (getline(ss, token, ' ')) {
    tokens.push_back(token);
}
```


**给字符串添加多个相同字符**
```cpp
string s = "hell";
int t = 3;

// 方法1：append（在末尾添加，推荐）
s.append(t, 'o');  // "hellooo"

// 方法2：字符串构造 + 拼接
s += string(t, 'o');

// 方法3：insert（在末尾插入）
s.insert(s.end(), (size_t)t, 'o');

// 方法4：resize
s.resize(s.size() + t, 'o');

// 方法5：insert 在指定位置插入（推荐）
s.insert(2, (size_t)t, 'o');  // 在索引 2 插入 t 个 'o' → "heoool"

// 方法6：使用迭代器在指定位置插入
s.insert(s.begin() + 2, (size_t)t, 'o');  // 在第 2 个位置插入 → "heoool"

string s = "";
for (int i = 0; i < b; i++) {
    s += "01";
}
```
```

**vector.md**

```md
### vector内存分配

```cpp
vector<int> vec = {1, 2, 3, 4, 5};
vec.clear();

// assign()方法可以用来重新分配vector的内容，传入一个空的初始化列表即可清空vector。
vec.assign({}); // 另一种清空vector的方法
 // 也可以使用assign()方法将vector重新分配为n个0的元素，从而清空原有内容。
vec.assign(n, 0);

// resize()方法可以用来改变vector的大小，如果传入0，则会清空vector。
vec.resize(n); // 将vector的大小调整为n，如果n为0，则清空vector。

// resize 与 assign 的区别在于，resize 会改变 vector 的大小，而 assign 会改变 vector 的内容，但不会改变其大小。
vector<int> vec2 = {1, 2, 3, 4, 5};
vec2.resize(3); // vec2 现在包含 {1, 2, 3}
vec2.assign({}); // vec2 现在为空


int MAX = 1e5 + 5;
vector<int> vec[MAX]; // 创建一个大小为 MAX 的 vector 数组，每个元素都是一个空的 vector<int>
// 清空
// 假设当前图的点编号是 1 ~ n（如果是 0 ~ n-1，改成 i = 0; i < n）
for (int i = 1; i <= n; i++) {
    adj[i].clear();
}

// 彻底释放内存
for (int i = 1; i <= n; i++) {
    vector<int>().swap(adj[i]); // 用一个空 vector 和当前 vector 交换，瞬间释放内存
}

```

```cpp
vector<string> vec(n + 1, string(n + 1, '0')); // 创建一个 n+1 行 n+1 列的二维 vector，并初始化为 '0'
```

### 删除
```cpp
vec.erase(unique(vec.begin(), vec.end()), vec.end()); // 删除重复元素，前提是 vec 已经排序过
```
```

**二分查找.md**

```md
> 二分查找需保证数组有序
## 主要函数：
- `lower_bound`：返回第一个大于等于目标值的元素位置。
- `upper_bound`：返回第一个大于目标值的元素位置。
- `binary_search`：判断目标值是否存在于数组中。

### binary_search
```cpp
vector<int> v = {1, 2, 3, 4, 5};
bool exists = binary_search(v.begin(), v.end(), 3); // 返回 true
bool notExists = binary_search(v.begin(), v.end(), 6); // 返回 false
```

### lower_bound
```cpp
vector<int> v = {1, 2, 3, 4, 5};
auto it = lower_bound(v.begin(), v.end(), 3); // 返回指向 3 的迭代器
int idx = it - v.begin(); // index = 2
if (idx < v.size() && v[idx] == 3) {
    // 找到了目标值
} else {
    // 没有找到目标值
}

```
### upper_bound
```cpp
vector<int> v = {1, 2, 3, 4, 5};
auto it = upper_bound(v.begin(), v.end(), 3); // 返回指向 4 的迭代器
int idx = it - v.begin(); // index = 3
if (idx < v.size() && v[idx] == 3) {
    // 找到了目标值
} else {
    // 没有找到目标值
}
```

### 使用Lambda表达式自定义比较规则
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int score;
};

int main() {
    // 假设已经按分数从小到大排好序了
    vector<Student> v = {
        {3, 70}, 
        {1, 80}, 
        {4, 80}, 
        {2, 95}
    };

    int target_score = 80;

    // 查找第一个分数 >= 80 的学生
    auto it = lower_bound(v.begin(), v.end(), target_score, [](const Student& s, int val) {
        // 这里的逻辑必须是：判断结构体 s 的元素是否 "严格小于" 目标值 val
        return s.score < val; // 如果是 true，说明 s 的分数小于目标值，lower_bound 会继续往右找
    });

    if (it != v.end()) {
        cout << "找到了！学号: " << it->id << ", 分数: " << it->score << "\n";
        int idx = it - v.begin();
        cout << "下标是: " << idx << "\n";
    } else {
        cout << "没找到 >= 80 分的学生\n";
    }

    return 0;
}
```
### 使用重载<运算符自定义比较规则
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int score;

    // 重载 < 运算符：规定按照 score 从小到大排序
    bool operator<(const Student& other) const {
        return this->score < other.score; 
    }
};

int main() {
    vector<Student> v = {
        {3, 70}, 
        {1, 80}, 
        {4, 80}, 
        {2, 95}
    };

    // 此时我们想找分数 >= 80 的人。
    // 因为比较规则是 Student 和 Student 比，我们需要构造一个分数为 80 的假学生传进去。
    // id 填什么无所谓，因为重载的 < 里面只比较了 score。
    Student dummy = {-1, 80}; 

    auto it = lower_bound(v.begin(), v.end(), dummy);

    if (it != v.end()) {
        cout << "找到了！学号: " << it->id << ", 分数: " << it->score << "\n";
    }

    return 0;
}
```

### 在下标排序的数组中用二分查找
```cpp
vector<int> v = {4, 1, 3, 5, 2};
// 先对下标排序
vector<int> idx(v.size());
iota(idx.begin(), idx.end(), 0); // 初始化下标数组
sort(idx.begin(), idx.end(), [&](int i, int j) {
    return v[i] < v[j]; // 按照 v 的值排序下标
});
// 找到第一个大于等于 3 的下标
int target = 3;
auto it = lower_bound(idx.begin(), idx.end(), target, [&](int i, int val) { // i 是idx中的值，即 v的下标，val是目标值
    return v[i] < val; // 比较的是 v 的值
});
```
```

### C++常用库函数 / 位运算

**bitset.md**

```md
`std::bitset` 是 C++ 标准库提供的一个非常强大的模板类，专门用于处理**固定大小**的二进制位集合。

它的主要优势在于：

1.  **空间极致压缩**：它存储每个布尔值只占用 **1 bit**，而 `bool` 数组通常每个元素占用 1 byte (8 bits)。空间利用率是 `bool` 数组的 8 倍。
2.  **运算速度极快**：它支持直接对整个位集进行位运算（与、或、异或、左移、右移），这些操作会被编译器优化为指令集并行操作。通常可以将时间复杂度降低 **64倍**（取决于机器字长，通常是 $O(N/64)$）。

-----

### 1\. 头文件与定义

```cpp
#include <bitset>
using namespace std;

// 定义：bitset<大小> 变量名;
// 注意：大小 N 必须是编译期确定的常数 (constexpr)
bitset<100> b; 
```

### 2\. 初始化 (构造方式)

`bitset` 有多种初始化方式，**索引 0 代表最低位（最右边）**。

```cpp
#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int main() {
    // 1. 默认构造：全部为 0
    bitset<8> b1; 
    cout << b1 << endl; // 输出: 00000000

    // 2. 使用整数构造 (转为二进制)
    bitset<8> b2(12);   // 12 的二进制是 1100
    cout << b2 << endl; // 输出: 00001100

    // 3. 使用字符串构造 (从左到右读入)
    string s = "1001";
    bitset<8> b3(s);    
    // 注意：字符串的下标 0 (最左边) 对应 bitset 的最高位 (如果填满)
    // 这里 s 只有 4 位，所以填在低 4 位
    cout << b3 << endl; // 输出: 00001001
    
    // C++ 字符串字面量初始化
    bitset<8> b4("1111");
    cout << b4 << endl; // 输出: 00001111

    return 0;
}
```

### 3\. 常用成员函数

假设有 `bitset<8> b("00101100");` (即数值 44)

| 函数名 | 描述 | 示例与结果 |
| :--- | :--- | :--- |
| **访问与修改** | | |
| `b[i]` | 像数组一样访问第 `i` 位 (0是最低位) | `b[2]` 返回 1 |
| `set()` | 将所有位设为 1 | `b.set()` $\to$ `11111111` |
| `set(i, v)` | 将第 `i` 位设为 `v` (0或1) | `b.set(0, 1)` $\to$ `00101101` |
| `reset()` | 将所有位设为 0 | `b.reset()` $\to$ `00000000` |
| `reset(i)` | 将第 `i` 位设为 0 | `b.reset(2)` $\to$ `00101000` |
| `flip()` | 将所有位取反 (0变1, 1变0) | `b.flip()` $\to$ `11010011` |
| `flip(i)` | 将第 `i` 位取反 | `b.flip(2)` $\to$ `00101000` |
| **查询统计** | | |
| `count()` | 返回 **1** 的个数 (popcount) | `b.count()` $\to$ 3 |
| `size()` | 返回总位数 (即模板参数 N) | `b.size()` $\to$ 8 |
| `any()` | 是否**至少有一个** 1 | `b.any()` $\to$ true |
| `none()` | 是否**全为** 0 | `b.none()` $\to$ false |
| `all()` | 是否**全为** 1 (C++11) | `b.all()` $\to$ false |
| `test(i)` | 检查第 `i` 位是否为 1 (越界会抛异常) | `b.test(2)` $\to$ true |
| **类型转换** | | |
| `to_ulong()` | 转为 `unsigned long` | `b.to_ulong()` $\to$ 44 |
| `to_ullong()`| 转为 `unsigned long long` | `b.to_ullong()` |
| `to_string()`| 转为 `string` | `b.to_string()` $\to$ "00101100" |

### 4\. 位运算 (核心优势)

`bitset` 支持所有的位运算符，且效率极高。这在集合运算、状态压缩 DP 中非常有用。

```cpp
bitset<4> a("1010");
bitset<4> b("0110");

cout << (a & b) << endl; // 按位与: 0010 (交集)
cout << (a | b) << endl; // 按位或: 1110 (并集)
cout << (a ^ b) << endl; // 按位异或: 1100 (对称差)
cout << (~a)    << endl; // 按位取反: 0101
cout << (a << 1)<< endl; // 左移: 0100
cout << (a >> 1)<< endl; // 右移: 0101

if (a == b) cout << "Equal"; // 支持比较运算符
if (a != b) cout << "Not Equal";
```

-----

### 5\. 竞赛中的“黑科技” (GCC 扩展与优化)

在算法竞赛中，为了追求极致效率，经常使用以下技巧：

#### A. 01 背包 / 子集和问题的优化

假设有一个数组，问能否凑出和为 `W`。
普通 DP 是 $O(N \cdot W)$。使用 `bitset` 可以优化为 $O(N \cdot W / 64)$。

```cpp
// 题目：给你 n 个数，问能否凑出和 x
// 范围：n <= 100, x <= 100000
bitset<100005> dp;
dp[0] = 1; // 初始化：和为 0 是可以凑出来的

for (int x : nums) {
    // 状态转移方程：dp[v] = dp[v] | dp[v - x]
    // 等价于整体左移 x 位后取或
    dp |= (dp << x); 
}

if (dp[target]) cout << "Yes";
```

#### B. `_Find_first()` 和 `_Find_next()` (GCC 专属)

标准库没有直接提供“寻找下一个为 1 的位置”的 $O(1)$ 函数，但 GCC 编译器提供了扩展函数（在 LeetCode、Codeforces 等常见评测机上可用）。这比自己写循环找快得多。

```cpp
bitset<100> b;
b[10] = 1;
b[20] = 1;
b[50] = 1;

// 找到第一个置位的位置 (index 10)
int first = b._Find_first(); 
cout << first << endl; 

// 找到 first 之后的下一个置位位置
// 遍历所有为 1 的位：
for (int i = b._Find_first(); i < b.size(); i = b._Find_next(i)) {
    cout << i << " "; // 输出 10 20 50
}
```

### 6\. 注意事项

1.  **大小固定**：`bitset<N>` 的 `N` 必须是编译期常数。如果你需要动态大小的位图，请使用 `std::vector<bool>`（虽然它也有坑）或者 `boost::dynamic_bitset`。
2.  **栈溢出**：如果 `N` 非常大（例如 $10^7$），直接在函数内部定义 `bitset<10000000> b;` 可能会爆栈（Stack Overflow）。建议定义在**全局变量**或者使用 `new`。
      * $10^7$ bits $\approx$ 1.25 MB，通常栈只有几 MB，很危险。
      * 全局区通常有几百 MB 到 GB，很安全。
3.  **下标方向**：牢记 `b[0]` 是**最右边**（二进制最低位），`b[N-1]` 是**最左边**（二进制最高位）。这与数组 `arr[0]` 在左边的直觉相反，但符合二进制的数学表示。

### 总结

  * 需要处理集合运算（交、并、补）且元素范围固定时，首选 `bitset`。
  * 需要高密度存储 bool 状态时，首选 `bitset`。
  * 需要 $O(N/64)$ 优化 DP 或图论连通性问题时，首选 `bitset`。
```

**库函数.md**

```md
在 C++ 中，位运算相关的函数经历了一个从“依赖编译器内建函数”到“标准化库函数”的演变过程。

**C++20 是一个分水岭**。在 C++20 之前，我们通常依赖 GCC/Clang 的内建函数（如 `__builtin_popcount`）；在 C++20 之后，标准库终于引入了 `<bit>` 头文件，把这些功能标准化了。

以下是详细的分类总结：

### 1\. 现代标准位运算库 (推荐)

这是 C++20 引入的最正统、跨平台的位运算库。它们是模板函数，支持各种无符号整数类型（`unsigned`、`unsigned long long` 等）。

  * **头文件**: `#include <bit>`
  * **所需版本**: **C++20**

| 函数名 | 功能描述 (英文 / 中文) | 典型应用 |
| :--- | :--- | :--- |
| **`std::popcount`** | Population Count (计算二进制中 1 的个数) | 汉明距离、状态压缩 DP |
| **`std::countl_zero`** | Count Leading Zeros (计算从最高位起连续 0 的个数) | 确定数字的最高有效位、求 Log2 |
| **`std::countr_zero`** | Count Trailing Zeros (计算从最低位起连续 0 的个数) | 确定最低有效位 (Lowbit) |
| **`std::countl_one`** | Count Leading Ones (计算从最高位起连续 1 的个数) | 特殊编码解析 |
| **`std::countr_one`** | Count Trailing Ones (计算从最低位起连续 1 的个数) | 寻找连续可用的资源块 |
| **`std::bit_width`** | Bit Width (表示该数所需的最小二进制位数) | 相当于 $\lfloor \log_2(x) \rfloor + 1$ |
| **`std::bit_floor`** | 向下取整到最近的 2 的幂 ($2^k \le x$) | 内存对齐、线段树建树 |
| **`std::bit_ceil`** | 向上取整到最近的 2 的幂 ($2^k \ge x$) | 扩容策略 (Vector扩容)、FFT 补零 |
| **`std::has_single_bit`** | 判断是否是 2 的幂 (即只有一个 bit 是 1) | 快速检查 (x \> 0 && (x & (x-1)) == 0) |
| **`std::rotl`** / **`std::rotr`** | Rotate Left/Right (循环左移/右移) | 密码学、哈希函数 |

-----

### 2\. 编译器内建函数 (竞赛常用)

在 C++20 之前（或者在不支持 C++20 的 OJ 上），我们主要使用 GCC/Clang 提供的内建函数。它们**不是**标准 C++ 的一部分，但在所有主流 OJ（Linux环境）上都可用。

  * **头文件**: 无需头文件（编译器内置），但在代码中通常包含 `<cstdio>` 或 `<iostream>` 即可。
  * **所需版本**: **C++98 及以上** (只要是 GCC/Clang 编译器)

> **⚠️ 注意：** 这些函数通常分为 `int` 版本、`long` 版本 (`l` 后缀) 和 `long long` 版本 (`ll` 后缀)。**既然你习惯 `#define int long long`，请务必使用 `ll` 后缀的版本！**

| 函数名 (long long 版) | 对应 C++20 函数 | 注意事项 (非常重要！) |
| :--- | :--- | :--- |
| **`__builtin_popcountll(x)`** | `std::popcount(x)` | `x` 为 `long long` 类型。 |
| **`__builtin_clzll(x)`** | `std::countl_zero(x)` | **如果是 0，行为未定义(UB)**。使用前必须特判 `x != 0`。 |
| **`__builtin_ctzll(x)`** | `std::countr_zero(x)` | **如果是 0，行为未定义(UB)**。使用前必须特判 `x != 0`。 |
| **`__builtin_ffsll(x)`** | 无直接对应 (类似 `ctz + 1`) | 返回最低位 1 的索引（从 1 开始计数）。若 x=0 返回 0。 |
| **`__builtin_parityll(x)`** | 无直接对应 (popcount % 2) | 检查 1 的个数是奇数还是偶数 (奇偶校验)。 |

-----

### 3\. `std::bitset` 类库 (处理长位串)

如果你需要处理超过 64 位的位运算（比如 1000 位的 01 串），或者需要像数组一样操作位，`std::bitset` 是最佳选择。

  * **头文件**: `#include <bitset>`
  * **所需版本**: **C++98**

| 成员函数 | 功能 |
| :--- | :--- |
| `bitset<N> b;` | 创建一个 N 位的 bitset |
| `b.count()` | 返回 1 的个数 |
| `b.set()` / `b.reset()` | 全部置 1 / 全部置 0 |
| `b.flip()` | 全部按位取反 |
| `b.to_ullong()` | 转换为 `unsigned long long` |
| `b.to_string()` | 转换为 01 字符串 |
| `b._Find_first()` / `b._Find_next()` | **(非标准但常用)** 寻找第一个/下一个 1 的位置 (手写 bitset 优化常数时很有用) |

-----

### 总结与代码示例

考虑到你平时写算法题，建议遵循以下策略：

1.  **首选 C++20 的 `<bit>`**：如果 OJ 支持 C++20，直接用 `std::popcount`，既安全又好记。
2.  **备选内建函数**：如果环境较老，使用 `__builtin_popcountll`。
3.  **避坑指南**：使用 `__builtin_clz` 或 `ctz` 时，**一定**要保证参数不为 0。

**兼容性写法示例：**

```cpp
#include <iostream>
#include <bit>      // C++20
#include <cstdint>  // for uint64_t

// 如果不想记复杂的宏，可以直接用这个技巧
long long my_popcount(long long x) {
#if __cplusplus >= 202002L
    return std::popcount((unsigned long long)x);
#else
    return __builtin_popcountll(x);
#endif
}

// 获取一个数二进制的长度 (例如 5 -> 101 -> 3)
int get_bit_width(long long x) {
    if (x == 0) return 0;
#if __cplusplus >= 202002L
    return std::bit_width((unsigned long long)x);
#else
    // 64 减去前导零的个数
    return 64 - __builtin_clzll(x); 
#endif
}

int main() {
    long long x = 12; // 二进制 1100
    
    std::cout << "1的个数: " << my_popcount(x) << std::endl; // 输出 2
    std::cout << "位宽: " << get_bit_width(x) << std::endl;   // 输出 4 (1100)
    
    return 0;
}
```
```

## math

**qpow.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1'000'000'007;

using matrix = vector<vector<long long>>;

// 返回矩阵 a 和矩阵 b 相乘的结果
matrix mul(matrix& a, matrix& b) {
    int n = a.size(), m = b[0].size();
    matrix c = matrix(n, vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < a[i].size(); k++) {
            if (a[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < m; j++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

// a^n * f1
matrix pow_mul(matrix a, int n, matrix& f1) {
    matrix res = f1;
    while (n) {
        if (n & 1) {
            res = mul(a, res);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}
```

**random.cpp**

```cpp
#include <random>
#include <chrono>

// 1. 初始化一个全局的 64 位高质量随机数引擎，用高精度时间戳做种子
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// 2. 封装整数生成器：生成 [L, R] 范围内的随机整数
long long randint(long long L, long long R) {
    std::uniform_int_distribution<long long> dist(L, R);
    return dist(rng);
}

// 3. 封装浮点数生成器：生成 [L, R) 范围内的随机小数
double randdouble(double L, double R) {
    std::uniform_real_distribution<double> dist(L, R);
    return dist(rng);
}
```

**拓展欧拉定理.md**

```md
### 1. 核心武器：扩展欧拉定理（欧拉降幂）

在数论中，当我们需要计算 $a^b \pmod m$，且指数 $b$ 极大时，可以使用扩展欧拉定理将指数降下来。公式如下：

$$a^b \pmod m = a^{(b \pmod{\varphi(m)}) + \varphi(m)} \pmod m \quad (\text{当 } b \ge \varphi(m) \text{ 时})$$

其中 $\varphi(m)$ 是欧拉函数，表示小于等于 $m$ 且与 $m$ 互质的正整数的个数。
这个公式的强大之处在于：**它不要求底数 $a$ 和模数 $m$ 互质**。

### 2. 破译“纸老虎”：欧拉函数的快速衰减

题目要求计算 $2^{3^{4^{\dots^{2023}}}} \pmod{2023}$。我们套用上面的降幂公式，会发现模数在逐层递减：

* **第 1 层：** 模数 $m_1 = 2023$。我们需要求指数 $3^{4^{\dots}} \pmod{\varphi(2023)}$。
计算得出 $\varphi(2023) = 1632$。
* **第 2 层：** 模数变成了 $m_2 = 1632$。我们需要求指数 $4^{5^{\dots}} \pmod{\varphi(1632)}$。
计算得出 $\varphi(1632) = 512$。
* **第 3 层：** 模数变成了 $m_3 = 512$。计算 $\varphi(512) = 256$。
* **第 4 层：** $\varphi(256) = 128$。
* **后续层：** $64 \rightarrow 32 \rightarrow 16 \rightarrow 8 \rightarrow 4 \rightarrow 2 \rightarrow 1$。

**关键点来了：**
当对某一层求欧拉函数得到 $1$ 时，任何数对 $1$ 取模结果都是 $0$。这就意味着递归计算在这一层直接“触底”了，直接返回 $0$ 即可。
根据上面的衰减速度，大约在底数为 $12$ 到 $14$ 左右时，模数就已经变成 $1$ 了。**从 $15$ 一直到 $2023$ 的那几千层指数，对最终结果没有任何影响！**

### 3. C++ 满分求解代码

既然是结果填空题，我们只需要把这个递归逻辑写成 C++ 程序跑出结果即可。由于指数塔的增长速度呈爆炸级，从第 2 层开始，真实的指数就必定远远大于 $\varphi(m)$，因此我们可以无脑套用 `+ phi(m)` 的公式。

你可以直接运行以下代码获取最终填空答案：

```cpp
#include <iostream>
using namespace std;

// 1. 求欧拉函数 phi(n)
long long phi(long long n) {
    long long res = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}

// 2. 快速幂模板，计算 (a^b) % m
long long quick_pow(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// 3. 递归求解指数塔
long long solve(int n, long long m) {
    // 递归终点：当模数衰减为 1 时，任何数 mod 1 都是 0
    if (m == 1) return 0;
    
    // 如果真的遍历到了顶层（实际根本到达不了）
    if (n == 2023) return 2023 % m;

    long long p = phi(m);
    
    // 递归计算上一层的指数
    long long exp = solve(n + 1, p);
    
    // 套用扩展欧拉定理：a^b % m = a^{(b % p) + p} % m
    return quick_pow(n, exp + p, m);
}

int main() {
    // 求解 2^(3^...) mod 2023
    cout << solve(2, 2023) << endl;
    return 0;
}

```

运行这段代码，在 1 毫秒内即可输出最终的整数结果，直接将其填入答题框即可得分。
```

**模笔记.md**

```md
- 模M时，每次操作带来的增量是$\Delta$，那么这个状态发生循环所需的最多步数N是：
$$ N = \frac{M}{\gcd(M, \Delta)} $$
```

**组合数.cpp**

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;//1e9 + 7; // 或者是 998244353
const int MAXN = 2e5 + 5; // 根据题目 n 的范围调整

long long fact[MAXN];     // 阶乘数组: fact[i] = i! % MOD
long long invFact[MAXN];  // 阶乘逆元数组: invFact[i] = (i!)^(-1) % MOD

// 1. 快速幂模板：求 a^b % MOD
long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long getInv(long long a) {
    return qpow(a, MOD - 2);
}

void init() {
    fact[0] = 1;
    invFact[0] = 1;
    
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    
    invFact[MAXN - 1] = getInv(fact[MAXN - 1]);
    
    // 解释：1/(i-1)! = (1/i!) * i
    for (int i = MAXN - 2; i >= 1; --i) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    // intt[i] = (mod - mod / i) * intt[mod % i] % mod; intt[i] 是 i 的逆元
}

long long C(int n, int m) {
    if (m < 0 || m > n || n < 0) return 0;
    
    long long res = fact[n];
    res = res * invFact[m] % MOD;
    res = res * invFact[n - m] % MOD;
    
    return res;
}

// 专门对付 n 极大、m 较小的组合数
long long nCr(long long n, long long m) {
    if (m < 0 || n < m) return 0;
    if (m == 0) return 1;
    
    long long num = 1;
    // 分子部分暴力连乘 m 次：n * (n-1) * ... * (n-m+1)
    for (int i = 0; i < m; ++i) {
        num = num * ((n - i) % MOD) % MOD; 
    }
    // 分母部分依然可以使用你的 invFact，因为 m 最大才 10^6
    return num * invFact[m] % MOD;
}

long long A(int n, int m) {
    if (m < 0 || m > n || n < 0) return 0;
    return fact[n] * invFact[n - m] % MOD;
}

```

**组合数学结论.md**

```md
- 有 n 个 无区别小球，放到 m 个 有区别盒子 中，允许某些盒子为空。问有多少种分配方法？
$$C(m+n-1, m-1) = \binom{m+n-1}{m-1}$$
简解：假设增加 m 个小球，将小球分成 m 份，每份至少一个小球。就是$\binom{m+n-1}{m-1}$ ,每份的小球数减去一个，就是原来 n 个小球的分配方法数。


**从n个不同元素中选奇数个元素的组合数**

$$(1+1)^n = \binom{n}{0} + \binom{n}{1} + \binom{n}{2} + \dots + \binom{n}{n} = 2^n$$
$$ (1-1)^n = \binom{n}{0} - \binom{n}{1} + \binom{n}{2} - \dots + (-1)^n\binom{n}{n} = 0$$

所以，选奇数个元素的组合数为：
$$\binom{n}{1} + \binom{n}{3} + \binom{n}{5} + \dots = 2^{n-1}$$
```

**调和级数求因子_倍数.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;
// 假设数组中的最大值为 MAX_V
const int MAX_V = 100000;
vector<int> cnt(MAX_V + 1, 0); // 记录每个值在数组中出现的次数
vector<int> M(MAX_V + 1, 0);   // M[v] 记录数组中有多少个数是 v 的倍数
vector<int> D(MAX_V + 1, 0);   // D[v] 记录数组中有多少个数是 v 的约数

const int MOD = 1e9 + 7;
// 假设 cnt 数组已经初始化完毕...

int main() {
    // O(V log V) 调和级数预处理
    for (int i = 1; i <= MAX_V; ++i) {
        if (cnt[i] == 0)
            continue; // 剪枝：如果数组里根本没这个数，视情况可跳过

        // j 就是 i 的倍数：i, 2i, 3i, ...
        for (int j = i; j <= MAX_V; j += i) {
            // 更新倍数统计：j 是 i 的倍数，所以把 i 的出现次数加给 D[j]
            D[j] += cnt[i];

            // 更新约数统计：i 是 j 的约数，所以把 j 的出现次数加给 M[i]
            M[i] += cnt[j];
        }
    }

   
    return 0;
}
 // const int MAX_V = 100000;
    // vector<long long> dp(MAX_V + 1, 0);
    // // dp[i] 表示以数值 i 结尾/作为状态的某种最优解

    // // 从小到大推（求倍数）
    // for (int i = 1; i <= MAX_V; ++i) {
    //     // 状态转移到所有的倍数
    //     for (int j = 2 * i; j <= MAX_V; j += i) {
    //         dp[j] = max(dp[j], dp[i] + /* 某种权值 */);
    //     }
    // }

    // // 或者从大到小推（求约数容斥，莫比乌斯反演简化版）
    // for (int i = MAX_V; i >= 1; --i) {
    //     for (int j = 2 * i; j <= MAX_V; j += i) {
    //         dp[i] = (dp[i] - dp[j] + MOD) % MOD;
    //     }
    // }
```

### math / prime

**Euler.cpp**

```cpp
#include <vector>
using namespace std;

const int MX = 1e7 + 5;
bool is_prime[MX];     // is_prime[i] 为 true 表示是质数
vector<int> primes;    
void euler_sieve() {
    fill(is_prime, is_prime + MX, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MX; i++) {
        if (is_prime[i]) {
            primes.push_back(i); 
        }
        for (int p : primes) {
            if (i * p >= MX) break; 
            is_prime[i * p] = false; 
            if (i % p == 0) {
                break; 
            }
        }
    }
}
```

**Miller-Rabin.cpp**

```cpp
// 大素数判定
#include <iostream>

using namespace std;

// 定义别名，方便书写
typedef long long ll;
typedef __int128 lll; // 使用 __int128 防止乘法取模时溢出

ll power(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (lll)res * a % m; 
        a = (lll)a * a % m;
        b >>= 1;
    }
    return res;
}

// Miller-Rabin 素性测试核心逻辑
bool miller_rabin(ll n) {
    if (n < 2) return false;      
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    // 将 n-1 分解为 d * 2^s 的形式
    ll d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    // 对于 n <= 10^12，使用前几个素数作为底数测试绝对足够且准确
    int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    for (int a : bases) {
        if (n == a) return true;
        if (n % a == 0) return false;

        ll x = power(a, d, n);
        
        // 如果 x == 1 或者 x == n-1，通过了当前的底数测试
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        // 进行二次探测
        for (int i = 0; i < s - 1; i++) {
            x = (lll)x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        
        // 如果都没有通过，说明必定是合数
        if (composite) return false;
    }
    return true; 
}
void solve() {
    ll x;
    cin >> x;
    if (miller_rabin(x)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    // 解除 cin/cout 与 stdio 的同步，极限提升 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

```

**spf.cpp**

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MX = 1e6 + 5; 
int spf[MX];
bool is_inited = false;

// O(MX * log(log(MX)))，极其接近 O(MX)
void init_spf() {
    if (is_inited) return;
    is_inited = true;
    
    for (int i = 2; i < MX; i++) {
        spf[i] = i; 
    }
    for (int i = 2; i * i < MX; i++) {
        if (spf[i] == i) { 
            for (int j = i * i; j < MX; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

// 时间复杂度：O(log X)
vector<int> get_prime_factors(int x) {
    vector<int> factors;
    while (x > 1) {
        int p = spf[x];     
        factors.push_back(p); 
        
        // 去重
        // while (x % p == 0) x /= p; 
        
        // 如果不需要去重，直接除一次即可：
        x /= p;
    }
    return factors;
}


```

**trial_division.cpp**

```cpp
#include <iostream>
#include <vector>

using namespace std;

// 返回一个 pair 的数组：{质因子, 该质因子出现的次数}
vector<pair<long long, int>> prime_factorize(long long n) {
    vector<pair<long long, int>> factors;
    
    // 只需遍历到 sqrt(n)
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) { 
            int count = 0;
            while (n % i == 0) {
                count++;
                n /= i;
            }
            factors.push_back({i, count});
        }
    }
    
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}

// 求n所有约数的和
long long sum_of_divisors(long long n) {
    auto factors = prime_factorize(n);
    long long sum = 1;
    
    for (const auto& [p, exp] : factors) {
        // 质因子 p 出现 exp 次的贡献是 (p^(exp+1) - 1) / (p - 1)
        long long term = 1;
        for (int i = 0; i <= exp; i++) {
            term *= p;
        }
        sum *= (term - 1) / (p - 1);
    }
    
    return sum;
}
int main() {
   cout << sum_of_divisors(12);
}
```

**因子相关结论.md**

```md
### 1. 约数个数定理
> 若$$n = p_1^{a_1} p_2^{a_2} \cdots p_k^{a_k}$$，则$n$的约数个数为$$(a_1 + 1)(a_2 + 1) \cdots (a_k + 1)$$。
```

### math / 几何

**四边形面积.cpp**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    long long dx, dy, c;
    // 重载小于号，用于后续对向量分组和 C 值排序
    bool operator<(const Segment& other) const {
        if (dx != other.dx) return dx < other.dx;
        if (dy != other.dy) return dy < other.dy;
        return c < other.c;
    }
};

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<long long, long long>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    vector<Segment> segs;
    segs.reserve(n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = points[j].first - points[i].first;
            long long dy = points[j].second - points[i].second;
            long long start_x, start_y;
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
                start_x = points[j].first;
                start_y = points[j].second;
            } else {
                start_x = points[i].first;
                start_y = points[i].second;
            }
            // 面积 |c1 - c2|
            long long c = dy * start_x - dx * start_y;
            segs.push_back({dx, dy, c});
        }
    }

    sort(segs.begin(), segs.end());

    long long max_area = 0;
    int m = segs.size();
    
    for (int i = 0; i < m; ) {
        int j = i;
        while (j < m && segs[j].dx == segs[i].dx && segs[j].dy == segs[i].dy) {
            j++;
        }
    
        long long current_area = segs[j - 1].c - segs[i].c;
        if (current_area > max_area) {
            max_area = current_area;
        }
        
        i = j; 
    }

    if (max_area == 0) {
        cout << "-1\n";
    } else {
        double kk = max_area;
        cout << kk << endl;
    }

    return 0;
}
```

### 动态规划 / 数位DP

**digitDP.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
// 代码示例：返回 [low, high] 中的恰好包含 target 个 0 的数字个数
// 比如 digitDP(0, 10, 1) == 2
// 要点：我们统计的是 0 的个数，需要区分【前导零】和【数字中的零】，前导零不能计入，而数字中的零需要计入
int digitDP(int low, int high, int target) {
    string low_s = to_string(low);
    string high_s = to_string(high);
    int n = high_s.size();
    int diff_lh = n - low_s.size();
    vector memo(n, vector<int>(target + 1, -1));
//Kahn vector<vector<int>> memo(n, vector<int>(target + 1, -1));
    auto dfs = [&](auto&& dfs, int i, int cnt0, bool limit_low, bool limit_high) -> int {
        if (cnt0 > target) {
            return 0; // 不合法
        }
        if (i == n) {
            return cnt0 == target;
        }

        if (!limit_low && !limit_high && memo[i][cnt0] >= 0) {
            return memo[i][cnt0];
        }

        int lo = limit_low && i >= diff_lh ? low_s[i - diff_lh] - '0' : 0;
        int hi = limit_high ? high_s[i] - '0' : 9;

        int res = 0;
        int d = lo;
        // 通过 limit_low 和 i 可以判断能否不填数字，无需 is_num 参数
        // 如果前导零不影响答案，去掉这个 if block
        if (limit_low && i < diff_lh) {
            // 不填数字，上界不受约束
            res = dfs(dfs, i + 1, cnt0, true, false);
            d = 1;
        }
        for (; d <= hi; d++) {
            // 统计 0 的个数
            res += dfs(dfs, i + 1, cnt0 + (d == 0), limit_low && d == lo, limit_high && d == hi);
            // res %= MOD;
        }

        if (!limit_low && !limit_high) {
            memo[i][cnt0] = res;
        }
        return res;
    };

    return dfs(dfs, 0, 0, true, true);
}

```

### 图论 / 二分图

**BipartiteColoring.cpp**

```cpp
// 判读是否为二分图 2026.7.6
// 【例题】：https://leetcode.cn/problems/maximum-partition-factor/submissions/
#include <bits/stdc++.h>
using namespace std;
int n, m; // n为左侧点数，m为右侧点数
const int MAXN = 505;
vector<int> adj[MAXN]; // 邻接表表示图
int color[MAXN]; // color[i]表示第i个点的颜色，0表示未染色，1表示红色，2表示蓝色
bool possible = true; 

void dfs(int u, int c) {
    color[u] = c; 
    for (int v : adj[u]) {
        if (color[v] == c) {
            possible = false; 
            return;
        }
        if (color[v] == 0) {
            dfs(v, 3 - c); 
            if (!possible) return;
        }
    }
}

void addEdge(int u, int v) { // 添加一条无向边，索引从0开始
    adj[u].push_back(v);
    adj[v].push_back(u);
}

bool check() {
    memset(color, 0, sizeof(color));
    possible = true;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            dfs(i, 1); 
            if (!possible) return false;
        }
    }
    return true;
}
```

**BipartiteGraph.cpp**

```cpp
// 求二分图的最大匹配数模板，使用匈牙利算法 2026.7.6
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
int n, m; // n为左侧点数，m为右侧点数
vector<int> adj[MAXN]; // adj[i]表示左侧第i个点能匹配到的右侧点的列表
int match[MAXN]; // match[i]表示右侧第i个点匹配的左侧点编号，-1表示未匹配
int vis[MAXN]; // vis[i]表示右侧第i个点是否在当前增广路径中被访问过
int dfn = 0;

bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v] != dfn) {
            vis[v] = dfn;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void addEdge(int u, int v) { // 添加一条单向边，索引从0开始
    adj[u].push_back(v);
}

int maxMatching() { // 求最大匹配数
    memset(match, -1, sizeof(match));
    int res = 0;
    for (int u = 0; u < n; ++u) {
        dfn++;
        if (dfs(u)) res++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int edges; // 边的数量
    cin >> edges;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v); // 添加边，假设输入的u和v是从0开始的索引
    }

    int result = maxMatching();
    cout << "Maximum matching size: " << result << endl;

    return 0;
}

```

### 图论 / 拓扑排序

**Kahn.cpp**

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 拓扑排序 Kahn 算法模板
// 返回值: 如果存在拓扑排序，返回排序后的节点数组；如果存在环，返回空数组
vector<int> kahnTopologicalSort(int n, const vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    vector<int> in_degree(n, 0);
    
    // 1. 构建邻接表并统计入度
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // 2. 初始化队列，推入所有入度为 0 的节点
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> topo_order;
    
    // 3. 核心剥离循环
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        
        // 遍历所有邻居，解除依赖
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // 4. 环路检测：判断是否所有节点都被遍历到
    if (topo_order.size() != n) {
        return {}; // 存在环，无法进行完整拓扑排序
    }
    
    return topo_order;
}
```

#### 图论 / 最短路 / Dijkstra

**dijkstra.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long; 

const ll INF = 1e18; 

struct Node {
    int u;
    long long w;
    bool operator<(const Node& other) const {
        return w > other.w;
    }
};
void Dijkstra(int n, int u, vector<vector<Node>>& g, vector<long long>& dist) {
    priority_queue<Node> p;
    dist[u] = 0;
    p.push({u, 0});
    while (!p.empty()) {
        Node o = p.top();
        p.pop();
        int v = o.u;
        if (o.w > dist[v]) continue;
        for (auto& e : g[v]) {
            int to = e.u;
            long long w = e.w;
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                p.push({to, dist[to]});
            }
        }
    }
}
```

#### 图论 / 最短路 / Floyd

**floyd.cpp**

```cpp
#include <vector>
#include <iostream>
using namespace std;

const int INF = 1e9;
// 复杂度: O(n^3)
void floydWarshall(vector<vector<long long>>& dist) {
    int n = dist.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}
```

#### 图论 / 最短路 / 次短路

**code.cpp**

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 5005;

struct Edge {
    int to, w;
};
vector<Edge> adj[MAXN];

int dist1[MAXN]; 
int dist2[MAXN]; 

void dijkstra(int start, int n) {
    for(int i = 1; i <= n; i++) {
        dist1[i] = dist2[i] = INF;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist1[start] = 0;
    pq.push({0, start});
    
    while(!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist2[u]) continue;
        
        for(auto& e : adj[u]) {
            int v = e.to;
            int new_dist = d + e.w;
            if(new_dist < dist1[v]) {
                dist2[v] = dist1[v];      
                pq.push({dist2[v], v});  
                
                dist1[v] = new_dist;      
                pq.push({dist1[v], v});
            }
            else if(new_dist > dist1[v] && new_dist < dist2[v]) {
                dist2[v] = new_dist;
                pq.push({dist2[v], v});
            }
        }
    }
}
```

**简介.md**

```md
# 🛣️ 算法笔记：次短路问题 (Second Shortest Path)

> **归档**：`图论 \ 最短路`
> **标签**：`#Dijkstra` `#Graph` `#State_Splitting`
> **前置知识**：`Dijkstra 算法`

## 1\. 问题定义

求从起点 $S$ 到终点 $T$ 的**第二短**的路径长度。

次短路通常分为两种定义：

1.  **严格次短路**：长度必须 **严格大于** 最短路长度 ($Len > MinDist$)。
2.  **非严格次短路**：长度可以 **等于** 最短路长度（例如存在两条长度相同的最短路径，第二条也被视为次短）。

> **注意**：做题前务必看清题目要求。P2865 要求的是**严格次短**。

-----

## 2\. 核心思路：状态拆分 Dijkstra

普通的 Dijkstra 也就是求解“最短路”。为了求“次短路”，我们需要让每个节点多记录一个状态。

  * **`dist1[u]`**：起点到 $u$ 的**最短**路径长度。
  * **`dist2[u]`**：起点到 $u$ 的**次短**路径长度。

### 2.1 状态更新逻辑 (金银牌法则)

假设当前从堆中弹出的节点是 $u$，距离是 $d$。我们要尝试更新邻居 $v$，边权为 $w$。
新的潜在距离为 `new_dist = d + w`。我们将 `new_dist` 与 $v$ 现有的成绩比较：

| 情况 | 条件 | 操作 | 逻辑解释 |
| :--- | :--- | :--- | :--- |
| **1. 破纪录** | `new_dist < dist1[v]` | 1. `dist2[v] = dist1[v]`<br>2. `dist1[v] = new_dist`<br>3. 将两个状态入队 | 发现了更短的路！<br>旧的最短路退位变成次短路。<br>新的最短路登顶。 |
| **2. 新次短** | `new_dist > dist1[v]`<br>`&&`<br>`new_dist < dist2[v]` | 1. `dist2[v] = new_dist`<br>2. 将该状态入队 | 没能打破最短纪录，但比原本的次短路优秀。<br>刷新次短路记录。 |
| **3. 相等** | `new_dist == dist1[v]` | (根据题目要求) | **严格次短**：忽略。<br>**非严格次短**：更新次短路（如果允许相等）。 |
| **4. 无效** | `new_dist >= dist2[v]` | `continue` | 比次短路还长，毫无价值。 |

-----

## 3\. 标准代码模板 (C++)

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 5005;

struct Edge {
    int to, w;
};
vector<Edge> adj[MAXN];

int dist1[MAXN]; // 最短路
int dist2[MAXN]; // 次短路

void dijkstra(int start, int n) {
    // 初始化
    for(int i = 1; i <= n; i++) {
        dist1[i] = dist2[i] = INF;
    }
    
    // 小根堆：{距离, 节点编号}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist1[start] = 0;
    pq.push({0, start});
    
    while(!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        // 【剪枝】如果当前距离比次短路还大，肯定没用
        if (d > dist2[u]) continue;
        
        for(auto& e : adj[u]) {
            int v = e.to;
            int new_dist = d + e.w;
            
            // 情况 1: 更新最短路
            if(new_dist < dist1[v]) {
                dist2[v] = dist1[v];      // 旧的最短路 -> 次短路
                pq.push({dist2[v], v});   // 记得入队！
                
                dist1[v] = new_dist;      // 更新最短路
                pq.push({dist1[v], v});
            }
            // 情况 2: 更新次短路 (注意这里的 > dist1[v] 是为了保证严格次短)
            else if(new_dist > dist1[v] && new_dist < dist2[v]) {
                dist2[v] = new_dist;
                pq.push({dist2[v], v});
            }
        }
    }
}
```

-----

## 4\. 复杂度分析

  * **空间复杂度**：$O(N + M)$。我们需要两个数组存距离，但这不改变数量级。
  * **时间复杂度**：$O(M \log N)$。
      * 在最坏情况下，每条边可能会触发两次入队操作（一次更新最短，一次更新次短）。
      * 堆中的元素数量最多约为 $2 \times M$。
      * 实际上常数会比普通 Dijkstra 稍大，但在竞赛中通常可以视为同一级别。

-----

## 5\. 易错点备忘

1.  **次短路也要入队**：这是最容易忘的！当 `dist2` 更新时，必须把 `{dist2[v], v}` 扔进堆里。因为这一条“次短”的路径，往下走一步，可能会构成后续节点的“最短”或“次短”。
2.  **严格性判断**：
      * 严格次短：`else if (new_dist > dist1[v] && ...)`
      * 非严格次短：`else if (new_dist >= dist1[v] && ...)` 或者简单地 `else if (new_dist < dist2[v])` (包含了等于最短的情况)。
3.  **继承旧值**：更新最短路时，别忘了 `dist2[v] = dist1[v]`。

-----
```

#### 图论 / 树上算法 / LCA

**TreeAncestor.cpp**

```cpp
// int bit_width(unsigned n) {
//     if (n == 0) return 0;
//     return std::__lg(n) + 1;
// }
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#define int long long
using namespace std;

class TreeAncestor {
    vector<int> depth;
    vector<vector<int>> pa;
    int max_log;

    int bit_width(unsigned n) {
        if (n == 0) return 0;
        return 32 - __builtin_clz(n);
        // return n == 0 ? 0 : 31 - __builtin_clz(n) + 1;
    }

public:
    TreeAncestor(const vector<vector<int>>& adj, int root = 0) {
        int n = adj.size();
        max_log = bit_width((unsigned)n);
        depth.resize(n);
        pa.assign(n, vector<int>(max_log, -1));

        auto dfs = [&](auto&& dfs, int x, int fa) -> void {
            pa[x][0] = fa;
            for (int y : adj[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dfs(dfs, y, x);
                }
            }
        };
        dfs(dfs, root, -1);

        for (int i = 0; i < max_log - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (pa[x][i] != -1) {
                    pa[x][i + 1] = pa[pa[x][i]][i];
                } else {
                    pa[x][i + 1] = -1;
                }
            }
        }
    }

    int getKthAncestor(int node, int k) {
        for (int i = 0; i < max_log; i++) {
            if ((k >> i) & 1) {
                node = pa[node][i];
                if (node == -1) break;
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) swap(x, y);

        y = getKthAncestor(y, depth[y] - depth[x]);
        if (y == x) return x;

        for (int i = max_log - 1; i >= 0; i--) {
            if (pa[x][i] != pa[y][i]) {
                x = pa[x][i];
                y = pa[y][i];
            }
        }
        return pa[x][0];
    }

    int get_distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }

    int get_depth(int x) { return depth[x]; }
    int get_parent(int x) { return pa[x][0]; }
};
```

**tarjan.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;

// tarjan 模板
const int MAXN = 200005;

vector<int> adj[MAXN];
vector<pair<int, int>> queries[MAXN]; 
int ans[MAXN];                        
int fa[MAXN];                         
bool vis[MAXN];                       

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void tarjan(int u) {
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v]) {
            tarjan(v);
            fa[v] = u; 
        }
    }

   
    for (auto& q : queries[u]) {
        int v = q.first;
        int id = q.second;
        if (vis[v]) {
            ans[id] = find(v); 
        }
    }
}
```

**欧拉序.cpp**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

// --- 极其干净的全局静态数据区 ---
vector<int> adj[MAXN];       // 树的邻接表（只有这个用 vector，因为各节点度数不同）
int depth[MAXN];             // 节点的深度
int first_pos[MAXN];         // 节点在欧拉序中第一次出现的索引
int euler_seq[2 * MAXN];     // 存放拍扁后的回溯欧拉序
int timer;                   // 欧拉序计时器

int st[2 * MAXN][20];        // 纯连续二维全局数组，速度的保障
int lg[2 * MAXN];            // 预处理的 log 数组

// 扁平的 DFS 函数
void dfs_euler(int u, int p, int d) {
    depth[u] = d;
    first_pos[u] = ++timer;
    euler_seq[timer] = u;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_euler(v, u, d + 1);
            euler_seq[++timer] = u; // 回溯打卡
        }
    }
}

// 扁平的初始化函数
void init_lca(int n) {
    timer = 0;
    dfs_euler(1, 0, 0); // 假设以 1 为根

    // 预处理 log 数组
    lg[1] = 0;
    for (int i = 2; i <= timer; i++) lg[i] = lg[i / 2] + 1;

    // 填充 ST 表的第 0 层
    for (int i = 1; i <= timer; i++) st[i][0] = euler_seq[i];

    // 递推填充整张表
    for (int j = 1; (1 << j) <= timer; j++) {
        for (int i = 1; i + (1 << j) - 1 <= timer; i++) {
            int a = st[i][j - 1];
            int b = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (depth[a] < depth[b]) ? a : b;
        }
    }
}

// 没有任何指针跳转、极速 O(1) 的 LCA 核心
inline int get_lca(int u, int v) {
    int l = first_pos[u], r = first_pos[v];
    if (l > r) swap(l, r);
    int k = lg[r - l + 1];
    int a = st[l][k];
    int b = st[r - (1 << k) + 1][k];
    return (depth[a] < depth[b]) ? a : b;
}

// 极其清爽的距离计算
inline int get_distance(int u, int v) {
    if (u == 0 || v == 0) return -1e9;
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}
```

#### 图论 / 树上算法 / 最小生成树

**Kruskal.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct node {
	int u, v, val;
};
int fa[5005];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	vector<node> e(m);
	for (int i = 0; i < m; i++) {
		cin >> e[i].u >> e[i].v >> e[i].val;
	}
	sort(e.begin(), e.end(), [&](node a, node b) {
		return a.val < b.val;
		});
	int ans = 0, cnt = 0;
	for (int i = 0; i < m; i++) {
		int u = find(e[i].u);
		int v = find(e[i].v);
		if (u == v) continue;
		cnt++;
		ans += e[i].val;
		fa[v] = u;
	}
	if (cnt == n - 1) cout << ans << endl;
	else cout << "orz" << endl;
	return 0;
}
```

**Prim.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long INF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
    int to, weight;
};
struct Node {
    int id, dist;
    bool operator<(const Node& other) const {
        return dist > other.dist;
    }
};
int n, m;
vector<vector<Edge>> adj;
int prim(int start = 1) {
    int total_weight = 0;
    int node_cnt = 0;
    vector<bool> vis(n + 1, false);
    vector<int> dist(n + 1, INF);
    priority_queue<Node> pq;
    dist[start] = 0;
    pq.push({start, 0});
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        int u = node.id;
        if (vis[u]) continue;
        vis[u] = true;
        total_weight += node.dist;
        node_cnt++;
        if (node_cnt == n) break;
        for (const Edge& edge : adj[u]) {
            int v = edge.to, w = edge.weight;
            if (!vis[v] && w < dist[v]) {
                dist[v] = w;
                pq.push({v, w});
            }
        }
    }
    if (node_cnt < n) return -1; 
    return total_weight;
}

```

#### 图论 / 树上算法 / 树的直径

**dfs.cpp**

```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 100005;
struct Edge { int to, w; };
vector<Edge> adj[N];
int dist[N];
int max_dist = -1, endpoint = -1;

// 这里的 fa 为了防止走回头路
void dfs(int u, int fa, int d) {
    if (d > max_dist) {
        max_dist = d;
        endpoint = u;
    }
    for (auto &e : adj[u]) {
        if (e.to != fa) {
            dfs(e.to, u, d + e.w);
        }
    }
}

int main() {
    int n; 
    cin >> n;
    // 建图... (假设输入 u v w)
    for(int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // 第一次 DFS：找端点 P
    max_dist = -1;
    dfs(1, -1, 0);
    int P = endpoint;

    // 第二次 DFS：从 P 出发找端点 Q
    max_dist = -1;
    dfs(P, -1, 0);
    int Q = endpoint;

    cout << max_dist << endl; // 直径长度
    return 0;
}
```

**treeDP.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Edge {
    int to, w;
};
vector<Edge> adj[N];
int ans = 0; // 全局最大直径
int d1[N], d2[N]; // d1: 最长链, d2: 次长链

void dfs_dp(int u, int fa) {
    d1[u] = d2[u] = 0;
    for (auto &e : adj[u]) {
        if (e.to == fa) continue;
        dfs_dp(e.to, u);
        
        int val = d1[e.to] + e.w;
        if (val > d1[u]) {
            d2[u] = d1[u];
            d1[u] = val;
        } else if (val > d2[u]) {
            d2[u] = val;
        }
    }
    ans = max(ans, d1[u] + d2[u]);
}
```

### 图论 / 边点权重限制

**Kruskal重构树.cpp**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005; // 原始节点数的上限根据题目调整为 5e5
const int MAXM = 500005; // 边数的上限
const int LOG = 21;      // 倍增最大步数 (5e5 节点，重构树近 1e6，LOG 开 21 保险)

struct Edge {
    int u, v, w;
    // 重载小于号：如果是求“经过边权 <= x”，则从小到大排序 (w < other.w)
    // 如果是求“经过边权 >= x”（例如接水问题），则从大到小排序 (w > other.w)
    bool operator<(const Edge& other) const {
        return w < other.w; 
    }
} edges[MAXM];

int n, m;
int total_nodes; // 重构树的总结点数 (原节点数 n + 虚拟节点数)

// 新增：记录原图的点权
int a[MAXN]; 
// 新增：记录重构树中子树包含的“原图节点（城市）”数量
int sz[MAXN * 2]; 

// 虚拟节点的权值（也就是原图的边权）
int val[MAXN * 2]; 

// 并查集数组
int fa[MAXN * 2];

// 倍增祖先数组，fa_tree[i][j] 表示节点 i 向上跳 2^j 步到达的祖先
int fa_tree[MAXN * 2][LOG]; 

// 树的结构，用于后续可能需要的 DFS (求 dfs 序、子树大小等)
vector<int> tree_adj[MAXN * 2];

// 并查集初始化
void init_dsu(int size) {
    for (int i = 1; i <= size; i++) {
        fa[i] = i;
    }
}

// 并查集查找 (路径压缩)
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void build_kruskal_tree() {
    // 1. 按边权排序
    sort(edges + 1, edges + 1 + m);
    
    // 2. 初始化并查集，注意大小要开到 2*n，因为会产生 n-1 个虚拟节点
    init_dsu(n * 2);
    
    // 前 n 个节点是原图的叶子节点，权值对于限制边权的问题通常不重要
    for (int i = 1; i <= n; i++) {
        val[i] = 0; 
        sz[i] = 1; // 新增：每个原图节点算作 1 个独立城市
    }
    
    total_nodes = n; // 当前重构树有 n 个原节点
    
    // 3. 开始 Kruskal 算法
    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w; // 在主函数读入时，w 已经被赋值为 max(a[u], a[v])
        
        int root_u = find(u);
        int root_v = find(v);
        
        // 如果不在同一个集合，需要合并
        if (root_u != root_v) {
            total_nodes++; // 新建一个虚拟节点
            val[total_nodes] = w; // 虚拟节点的权值就是当前边的权值
            sz[total_nodes] = sz[root_u] + sz[root_v]; // 新增：合并连通块，城市数量相加
            
            // 将两个集合的根节点连到新的虚拟节点下
            fa[root_u] = total_nodes;
            fa[root_v] = total_nodes;
            
            // 建立真实的树形结构 (虚拟节点连向原来的根)
            tree_adj[total_nodes].push_back(root_u);
            tree_adj[total_nodes].push_back(root_v);
            
            // 维护倍增数组的第 0 层 (父节点)
            fa_tree[root_u][0] = total_nodes;
            fa_tree[root_v][0] = total_nodes;
            
            // 注意：因为是新建节点作为父亲，此时 total_nodes 的父亲还是自己
            fa_tree[total_nodes][0] = 0; 
        }
    }
}

// 预处理倍增数组，用于 O(log N) 向上跳跃
void build_lca() {
    // total_nodes 通常是 2n - 1
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= total_nodes; i++) {
            if (fa_tree[i][j - 1] != 0) {
                fa_tree[i][j] = fa_tree[fa_tree[i][j - 1]][j - 1];
            } else {
                fa_tree[i][j] = 0;
            }
        }
    }
}

// 核心查询：从 start_node 出发，只走边权 <= limit 的边，
// 返回能到达的“最高统治者” (某个虚拟节点)
int get_highest_reachable_node(int start_node, int limit) {
    int current = start_node;
    
    // 贪心向上跳：如果上面第 2^j 步的祖先存在，且权值 <= limit，就跳上去
    for (int j = LOG - 1; j >= 0; j--) {
        int next_anc = fa_tree[current][j];
        if (next_anc != 0 && val[next_anc] <= limit) {
            current = next_anc;
        }
    }
    
    // 返回这个最高祖先的编号
    // 在这棵子树里的所有叶子节点，就是原图中你能到达的所有点！
    return current;
}

int main() {
    // 题目数据量达到 5e5，必须优化输入输出流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    // 1. 读入城市阈值
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 2. 读入双向道路，并完成“点权转边权”
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i].u = u;
        edges[i].v = v;
        // 核心转化：要走这条路，财富值必须同时满足两端的阈值
        edges[i].w = max(a[u], a[v]); 
    }

    // 3. 建树并预处理 LCA 的倍增数组
    build_kruskal_tree();
    build_lca();

    // 4. 处理在线询问
    int q;
    cin >> q;
    while (q--) {
        int u, x;
        cin >> u >> x;
        
        // 找到在财富值 x 的限制下，能跳到的最高连通块祖先
        int highest_root = get_highest_reachable_node(u, x);
        
        // 该祖先子树内的叶子（城市）总数，就是答案
        cout << sz[highest_root] << "\n";
    }

    return 0;
}

// 后续可以添加主席树或线段树等数据结构，支持动态修改城市阈值 a[i]，并在 O(log^2 N) 或 O(log N) 内完成查询。
```

## 复杂算法

**二维偏序.md**

```md
## 二维偏序
> 二维偏序是指在二维空间中定义的一种偏序关系。对于二维平面上的点 $(x_1, y_1)$ 和 $(x_2, y_2)$，我们可以定义如下的偏序关系：
$$(x_1, y_1) \leq (x_2, y_2) \iff x_1 \leq x_2 \text{ 且 } y_1 \leq y_2$$

- 二维偏序并没有固定的代码模板，一般来说，我们可以使用结构体或类来表示二维点，并重载比较运算符来实现二维偏序关系。有时候题目并不会给出明确的二维偏序定义，而是需要我们根据题意自行设计比较规则。

- 例题： https://leetcode.cn/problems/maximize-fixed-points-after-deletions/
```

### 复杂算法 / 分块

**分块求众数.cpp**

```cpp
/**
 * 例题：https://www.luogu.com.cn/problem/P4168
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 40005; // 题目中 n 的最大值
const int MAXB = 205;   // 估算的块数 (sqrt(40000) = 200)

// --- 数据结构 ---
int a[MAXN];          // 存放离散化后的数组
int origin_val[MAXN]; // 记录离散化后的值对应的原始种类编号
vector<int> sorted_a; // 用于离散化去重排序的临时容器

int belong[MAXN];     // belong[i] 表示原数组第 i 个元素属于第几块
int L[MAXB], R[MAXB]; // L[i] 和 R[i] 分别表示【第 i 块】的左右边界

int mode[MAXB][MAXB]; // mode[i][j] 记录第 i 块到第 j 块的众数 (离散化后的值)

// 核心优化：sum_cnt[i][x] 记录前 i 个块中，数字 x 出现的总次数
int sum_cnt[MAXB][MAXN]; 
int c[MAXN];          // query时使用的临时桶，只统计散块的元素
int stk[MAXN];        // 栈，用于极速清空临时桶 c
int top_stk = 0;
int tmp_cnt[MAXN];    // build预处理时使用的临时桶

// --- 初始化与预处理 ---
void build(int n) {
    int block_size = sqrt(n);
    int block_count = n / block_size + (n % block_size != 0 ? 1 : 0);

    // 1. 划分块
    for (int i = 1; i <= block_count; i++) {
        L[i] = (i - 1) * block_size + 1;
        R[i] = min(i * block_size, n);
    }
    for (int i = 1; i <= n; i++) {
        belong[i] = (i - 1) / block_size + 1;
    }

    // 2. 预处理 sum_cnt (前缀和思想，彻底干掉二分查找)
    for (int i = 1; i <= block_count; i++) {
        // 先继承前一个块的统计结果
        for (int j = 1; j <= n; j++) {
            sum_cnt[i][j] = sum_cnt[i - 1][j];
        }
        // 再加上当前块的元素
        for (int j = L[i]; j <= R[i]; j++) {
            sum_cnt[i][a[j]]++;
        }
    }

    // 3. 预处理 mode[i][j] (两层循环遍历所有的块区间)
    for (int i = 1; i <= block_count; i++) {
        int current_best = 0; 
        int current_max = 0;  
        
        for (int j = i; j <= block_count; j++) {
            for (int k = L[j]; k <= R[j]; k++) {
                int val = a[k];
                tmp_cnt[val]++;
                if (tmp_cnt[val] > current_max || (tmp_cnt[val] == current_max && origin_val[val] < origin_val[current_best])) {
                    current_max = tmp_cnt[val];
                    current_best = val;
                }
            }
            mode[i][j] = current_best;
        }
        
        // 极速清空法：只清空用过的桶，不要 memset 整个数组！
        for (int j = i; j <= block_count; j++) {
            for (int k = L[j]; k <= R[j]; k++) {
                tmp_cnt[a[k]] = 0;
            }
        }
    }
}

// --- 在线查询 (干掉了二分查找，纯 O(sqrt(N))) ---
int query(int l, int r) {
    int p = belong[l], q = belong[r];
    int best_val = 0, max_cnt = 0;

    // 情况 A：在同一个块或相邻块，直接暴力统计
    if (q - p <= 1) {
        for (int i = l; i <= r; i++) {
            int x = a[i];
            c[x]++;
            stk[++top_stk] = x; // 记录被修改的元素，用于 O(1) 清空
            if (c[x] > max_cnt || (c[x] == max_cnt && origin_val[x] < origin_val[best_val])) {
                max_cnt = c[x];
                best_val = x;
            }
        }
        // 极速清空
        while (top_stk > 0) c[stk[top_stk--]] = 0;
        return origin_val[best_val];
    }

    // 情况 B：跨越了多个块
    best_val = mode[p + 1][q - 1]; // 候选人 1 默认上岗
    
    // 统计左右散块的元素
    for (int i = l; i <= R[p]; i++) {
        c[a[i]]++;
        stk[++top_stk] = a[i];
    }
    for (int i = L[q]; i <= r; i++) {
        c[a[i]]++;
        stk[++top_stk] = a[i];
    }

    // 计算候选人 1 的真实得票数：散块里的票数 + 完整块里的票数(前缀和相减)
    max_cnt = c[best_val] + sum_cnt[q - 1][best_val] - sum_cnt[p][best_val];

    // 候选人 2：散块中出现过的元素参与竞争
    for (int i = 1; i <= top_stk; i++) {
        int x = stk[i];
        // 真实票数 = 散块票数 c[x] + 中间大整块票数
        int val = c[x] + sum_cnt[q - 1][x] - sum_cnt[p][x];
        if (val > max_cnt || (val == max_cnt && origin_val[x] < origin_val[best_val])) {
            max_cnt = val;
            best_val = x;
        }
    }

    // 极速清空栈
    while (top_stk > 0) c[stk[top_stk--]] = 0;

    return origin_val[best_val];
}

int main() {
    // 优化输入输出流，防 TLE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 1. 读入数据并进行离散化
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sorted_a.push_back(a[i]);
    }
    
    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());

    for (int i = 1; i <= n; i++) {
        // lower_bound 返回的是迭代器，减去 begin() 得到 0-based 的索引，加 1 变成 1-based
        int discrete_val = lower_bound(sorted_a.begin(), sorted_a.end(), a[i]) - sorted_a.begin() + 1;
        origin_val[discrete_val] = a[i]; // 记录映射关系，方便最后输出答案
        a[i] = discrete_val;             // 将原数组替换为离散化后的较小数值
    }

    // 2. 建块与预处理
    build(n);

    // 3. 处理询问
    int last_ans = 0; // x 初始化为 0
    while (m--) {
        int l0, r0;
        cin >> l0 >> r0;
        
        // 题目给定的解密公式
        int l = ((l0 + last_ans - 1) % n) + 1;
        int r = ((r0 + last_ans - 1) % n) + 1;
        if (l > r) swap(l, r);

        last_ans = query(l, r);
        cout << last_ans << "\n";
    }

    return 0;
}
```

**区间求和.cpp**

```cpp
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
```

### 复杂算法 / 根号分治

**步长p求和.cpp**

```cpp
// ### 根号分治核心思想：小步长预处理，大步长暴力跳
// 这套骨架适用于：**给定步长 $p$，求所有间隔为 $p$ 的元素之和（或最大值等操作）。**
// 例题：https://www.luogu.com.cn/problem/P3396

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 150005; // 假设最大数组长度为 150000
const int THRESHOLD = 387; // 阈值，通常取 sqrt(MAXN)，150000 的平方根约为 387

int a[MAXN];

// ans[p][x] 记录步长为 p，且除以 p 的余数为 x 的所有元素的和
// 空间代价：THRESHOLD * THRESHOLD ≈ 387 * 387 ≈ 150,000，非常小
int ans[THRESHOLD + 5][THRESHOLD + 5]; 

int n, m;

// 1. 初始化预处理 (仅处理小步长 p <= THRESHOLD 的情况)
void build() {
    // 遍历每一个原始数组的元素
    for (int i = 1; i <= n; i++) {
        // 将元素 a[i] 贡献给所有可能的小步长 p
        for (int p = 1; p <= THRESHOLD; p++) {
            // 下标 i 对步长 p 取模的结果
            int x = i % p; 
            ans[p][x] += a[i];
        }
    }
}

// 2. 单点修改：只修改小步长预处理数组
void update(int idx, int val) {
    int diff = val - a[idx]; // 计算增量
    a[idx] = val;            // 更新原数组
    
    // 只需更新那些 p <= THRESHOLD 的答案
    for (int p = 1; p <= THRESHOLD; p++) {
        int x = idx % p;
        ans[p][x] += diff;
    }
}

// 3. 根号分治双轨查询
int query(int p, int x) {
    // 策略 A：如果步长较小，直接 O(1) 返回预处理好的答案
    if (p <= THRESHOLD) {
        return ans[p][x];
    } 
    // 策略 B：如果步长极大，暴力跳跃查询
    else {
        int res = 0;
        // 起点是 x。如果 x=0，为了避免跳到下标 0 (数组从 1 开始)，需要特殊处理
        // 也可以不处理，确保遍历条件满足 i <= n 即可
        for (int i = x; i <= n; i += p) {
            if (i > 0) { // 避开无用的 0 索引
                res += a[i];
            }
        }
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 预处理
    build();

    while (m--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'A') {
            // 查询：步长为 x，余数为 y
            cout << query(x, y) << "\n";
        } else if (op == 'C') {
            // 修改：将第 x 个元素修改为 y
            update(x, y);
        }
    }

    return 0;
}
```

### 复杂算法 / 莫队算法

**不同数字.cpp**

```cpp
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
```

**回滚莫队.cpp**

```cpp
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
```

**普通莫队.cpp**

```cpp
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
```

### 字符串算法 / AC自动机

**code.cpp**

```cpp
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
```

### 字符串算法 / KMP

**kmp.cpp**

```cpp
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
```

### 字符串算法 / 回文串

**Manacher.cpp**

```cpp
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
```

**中心拓展.cpp**

```cpp

```

### 字符串算法 / 字符串哈希

**双哈希.cpp**

```cpp
#include <vector>
#include <string>
#include <chrono>
#include <random>

using namespace std;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// 2. 封装整数生成器：生成 [L, R] 范围内的随机整数
long long rnd(long long L, long long R) {
    std::uniform_int_distribution<long long> dist(L, R);
    return dist(rng);
}
struct AntiHackDoubleHash {
    using ll = long long;
    
    const ll MOD1 = 1e9 + 7;
    const ll MOD2 = 1e9 + 9; 
    
    ll BASE1, BASE2;

    vector<ll> h1, h2, p1, p2;

    AntiHackDoubleHash(const vector<int>& arr) {
        BASE1 = rnd(13331, 1e9);
        BASE2 = rnd(13331, 1e9);
        while (BASE1 == BASE2) BASE2 = rnd(13331, 1e9);

        int n = arr.size();
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        
        for (int i = 0; i < n; ++i) {
            // 防御负数攻击，拉回正数域
            ll val1 = (arr[i] % MOD1 + MOD1) % MOD1;
            ll val2 = (arr[i] % MOD2 + MOD2) % MOD2;
            
            // 乘法结果最大 10^18，原生的 long long 运算极快
            h1[i + 1] = (h1[i] * BASE1 + val1) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + val2) % MOD2;
            
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    // 针对字符串的重载构造函数
    AntiHackDoubleHash(const string& str) {
        BASE1 = rnd(13331, 1e9);
        BASE2 = rnd(13331, 1e9);
        while (BASE1 == BASE2) BASE2 = rnd(13331, 1e9);

        int n = str.length();
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        
        for (int i = 0; i < n; ++i) {
            ll val1 = str[i];
            ll val2 = str[i];
            
            h1[i + 1] = (h1[i] * BASE1 + val1) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + val2) % MOD2;
            
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    // O(1) 查询闭区间 [l, r] 的 64 位融合哈希值
    ll query(int l, int r) {
        int len = r - l + 1;
        ll res1 = (h1[r + 1] - h1[l] * p1[len] % MOD1 + MOD1) % MOD1;
        ll res2 = (h2[r + 1] - h2[l] * p2[len] % MOD2 + MOD2) % MOD2;
        // 左移 32 位融合，依然是一个干净利落的 64 位 long long
        return (res1 << 32) | res2;
    }
};
```

### 字符串算法 / 最小表示法

**code.cpp**

```cpp
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
```

## 对拍

**baoli.cpp**

```cpp
// 文件名：baoli.cpp
#include <iostream>

using namespace std;

int main() {
    long long a, b;
    if (cin >> a >> b) {
        // 绝对正确、没有花里胡哨逻辑的底牌
        cout << a + b << "\n"; 
    }
    return 0;
}
```

**check.cpp**

```cpp
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    int test_cases = 1000; 
    
    for (int i = 1; i <= test_cases; i++) {
        system("data.exe > data.in"); 
        system("my.exe < data.in > my.out"); 
        system("baoli.exe < data.in > baoli.out"); 
        
        if (system("fc my.out baoli.out > nul")) { 
            cout << "\nWrong Answer found on test " << i << "!\n";
            cout << "Check data.in for the testcase.\n";
            break; 
        } else {
            cout << "Test " << i << " AC\n";
        }
    }
    
    return 0;
}
```

**data.cpp**

```cpp
// 文件名：data.cpp
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long rnd(long long L, long long R) {
    return L + rng() % (R - L + 1);
}

int main() {
    // 生成两个 1 到 10 之间的随机整数
    long long a = rnd(1, 10);
    long long b = rnd(1, 10);
    
    // 把生成的随机数按题目输入格式打印出来
    cout << a << " " << b << "\n";
    return 0;
}
```

**my.cpp**

```cpp
// 文件名：my.cpp
#include <iostream>

using namespace std;

int main() {
    long long a, b;
    if (cin >> a >> b) {
        // 故意埋下的雷：在几百组数据里，只有碰到 7+7 才会算错
        if (a == 7 && b == 7) {
            cout << 15 << "\n"; 
        } else {
            cout << a + b << "\n";
        }
    }
    return 0;
}
```

### 数学 / 几何数学

**判断图形.cpp**

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 定义二维点/向量结构体
struct Point {
    long long x, y;
    
    Point(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
    
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 重命名，使得语义更清晰 (点和向量在二维坐标系下本质相同)
typedef Point Vector;

// 核心运算 1：求距离的平方 (极力避免开根号和浮点数误差)
long long dist2(const Point& A, const Point& B) {
    long long dx = A.x - B.x;
    long long dy = A.y - B.y;
    return dx * dx + dy * dy;
}

// 核心运算 2：向量点乘 (Dot Product) 点乘表示：|a||b|cos(θ)，表示投影
// 用途：判断垂直(结果为0)、夹角钝/锐
long long dotProduct(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

// 核心运算 3：向量叉乘 (Cross Product) 叉乘表示：|a||b|sin(θ), 表示面积
// 用途：判断共线(结果为0)、计算面积、判断转向
long long crossProduct(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}


// ==========================================
// 2. 三角形家族判定 (给定 3 个点)
// ==========================================

// 判断三点是否能构成三角形 (即判断三点是否不共线)
bool isTriangle(const Point& A, const Point& B, const Point& C) {
    Vector AB = B - A;
    Vector AC = C - A;
    // 叉乘不为 0 则不共线，能构成三角形
    return crossProduct(AB, AC) != 0;
}

// 判断是否为直角三角形 (使用点乘)
bool isRightTriangle(const Point& A, const Point& B, const Point& C) {
    if (!isTriangle(A, B, C)) return false;
    
    Vector AB = B - A;
    Vector BC = C - B;
    Vector CA = A - C;
    
    // 任意两条边垂直(点乘为0)即为直角三角形
    return dotProduct(AB, BC) == 0 || 
           dotProduct(BC, CA) == 0 || 
           dotProduct(CA, AB) == 0;
}

// ==========================================
// 3. 四边形家族判定 (给定 4 个点)
// 假设点已经按顺时针或逆时针顺序给出：A, B, C, D
// ==========================================

// 判断是否为平行四边形 (对角线互相平分)
// 巧解：不需要除以2，直接比较坐标和
bool isParallelogram(const Point& A, const Point& B, const Point& C, const Point& D) {
    return (A.x + C.x == B.x + D.x) && (A.y + C.y == B.y + D.y);
}

// 判断是否为菱形 (平行四边形 + 对角线互相垂直)
bool isRhombus(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (!isParallelogram(A, B, C, D)) return false;
    
    Vector AC = C - A;
    Vector BD = D - B;
    // 对角线互相垂直
    return dotProduct(AC, BD) == 0;
    
    // 备用写法：或者判断相邻两边距离平方相等
    // return dist2(A, B) == dist2(B, C);
}

// 判断是否为矩形 (平行四边形 + 对角线长度相等)
bool isRectangle(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (!isParallelogram(A, B, C, D)) return false;
    
    // 对角线长度平方相等
    return dist2(A, C) == dist2(B, D);
    
    // 备用写法：或者判断存在一个直角
    // Vector AB = B - A;
    // Vector BC = C - B;
    // return dotProduct(AB, BC) == 0;
}

// 判断是否为正方形 (既是矩形又是菱形)
bool isSquareOrdered(const Point& A, const Point& B, const Point& C, const Point& D) {
    return isRectangle(A, B, C, D) && isRhombus(A, B, C, D);
}

// ==========================================
// 4. 特别放送：无序 4 点判定正方形
// (六条边排序法，无视点的输入顺序)
// ==========================================
bool isSquareUnordered(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vector<long long> d(6);
    d[0] = dist2(p1, p2);
    d[1] = dist2(p1, p3);
    d[2] = dist2(p1, p4);
    d[3] = dist2(p2, p3);
    d[4] = dist2(p2, p4);
    d[5] = dist2(p3, p4);
    
    sort(d.begin(), d.end());
    
    // 正方形特点：前 4 条边长度平方相等 (且大于0)，后 2 条对角线长度平方相等
    if (d[0] == 0) return false; // 存在重合点
    
    return d[0] == d[1] && d[1] == d[2] && d[2] == d[3] && 
           d[4] == d[5] && 
           d[3] < d[4]; // 边长必须小于对角线
}


// ==========================================
// 5. 应对无序点的万能杀招：凸包排序 (极角排序)
// ==========================================
// 用于将无序的多个点，按逆时针顺序排成一个凸多边形
Point base_point; // 全局基准点，用于极角排序

// 比较函数：按照相对于 base_point 的极角大小排序
bool polarCompare(const Point& p1, const Point& p2) {
    Vector v1 = p1 - base_point;
    Vector v2 = p2 - base_point;
    long long cross = crossProduct(v1, v2);
    // 叉乘大于0，说明 v2 在 v1 的逆时针方向，v1 排在前面
    if (cross > 0) return true;
    if (cross < 0) return false;
    // 如果极角相同（共线），距离基准点近的排在前面
    return dist2(base_point, p1) < dist2(base_point, p2);
}

// 将无序的 4 个点按逆时针重新排列
// 排序后，你就可以放心地使用前面那些 isRectangle, isRhombus 等函数了
void sortPoints(vector<Point>& pts) {
    if (pts.size() != 4) return;
    
    // 1. 找到左下角的点作为基准点 (y最小，若y相同则x最小)
    int min_idx = 0;
    for (int i = 1; i < 4; i++) {
        if (pts[i].y < pts[min_idx].y || 
           (pts[i].y == pts[min_idx].y && pts[i].x < pts[min_idx].x)) {
            min_idx = i;
        }
    }
    
    // 把基准点交换到第 0 个位置
    swap(pts[0], pts[min_idx]);
    base_point = pts[0];
    
    // 2. 对剩下的 3 个点按照极角排序
    sort(pts.begin() + 1, pts.end(), polarCompare);
}


// 简单测试样例
int main() {
    Point A(0, 0), B(2, 0), C(2, 2), D(0, 2);
    
    cout << "A, B, C 是否构成直角三角形? " 
         << (isRightTriangle(A, B, C) ? "Yes" : "No") << endl;
         
    cout << "A, B, C, D (按顺序) 是否构成正方形? " 
         << (isSquareOrdered(A, B, C, D) ? "Yes" : "No") << endl;
         
    // 打乱顺序测试
    cout << "无序点 A, C, B, D 是否构成正方形? " 
         << (isSquareUnordered(A, C, B, D) ? "Yes" : "No") << endl;

    return 0;
}
```

**曼哈顿与切必雪.cpp**

```cpp
/**
 * 曼哈顿距离与切比雪夫距离
 * 设有两个点 $A(x_1, y_1)$ 和 $B(x_2, y_2)$，则它们之间的曼哈顿距离和切比雪夫距离分别定义如下：
 * - 曼哈顿距离（Manhattan Distance）：$d_M = |x_1 - x_2| + |y_1 - y_2|$
 * - 切比雪夫距离（Chebyshev Distance）：$d_C = \max(|x_1 - x_2|, |y_1 - y_2|)$
 * 如果求曼哈顿距离的复杂度过高，可将每个点的坐标进行变换，变换后的坐标为：
 * - $x' = x + y$
 * - $y' = x - y$
 * 此时，曼哈顿距离可以转化为切比雪夫距离：
 * $d_M = |x_1 - x_2| + |y_1 - y_2| = \max(|x'_1 - x'_2|, |y'_1 - y'_2|) = d_C$
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    int manhattan_distance = abs(x1 - x2) + abs(y1 - y2);
    int chebyshev_distance = max(abs(x1 - x2), abs(y1 - y2));

    cout << manhattan_distance << " " << chebyshev_distance << endl;

    int x1_prime = x1 + y1;
    int y1_prime = x1 - y1;
    int x2_prime = x2 + y2;
    int y2_prime = x2 - y2;
    int man_distance = max(abs(x1_prime - x2_prime), abs(y1_prime - y2_prime));
    cout << man_distance << endl;

    if (manhattan_distance == man_distance) {
        cout << "The transformed Manhattan distance equals the original Manhattan distance." << endl;
    } else {
        cout << "The transformed Manhattan distance does not equal the original Manhattan distance." << endl;
    }
}

```

**直线.md**

```md
在算法竞赛（Competitive Programming）中，**直线（Line）**是计算几何（Computational Geometry）和部分动态规划优化（如斜率优化、李超线段树）中的核心基础概念。

以下是算法竞赛中关于**直线**的知识点完整梳理，从基础表示、常用操作到高级算法：

---

### 一、直线的表示方法

在计算几何中，直线的表示方式直接影响代码的简洁度与数值稳定性。

#### 1. 点向量式（点 + 方向向量）—— **最推荐**
直线由线上一点 $P$ 和方向向量 $\vec{v}$ 唯一确定，表达式为：
$$L(t) = P + t \cdot \vec{v} \quad (t \in \mathbb{R})$$
* **优点**：避免斜率不存在（垂直于 x 轴）的特判；非常方便与点积、叉积结合；容易扩展到线段（$t \in [0, 1]$）和射线（$t \ge 0$）。

#### 2. 两点式（两个点确定一条直线）
用线上不重合的两点 $A, B$ 表示直线。
* **优点**：输入数据大多直接给出两点，无需额外预处理。

#### 3. 一般式：$Ax + By + C = 0$
* **优点**：若所有坐标为整数，且经过约分使 $\gcd(|A|, |B|, |C|) = 1$ 且 $A > 0$（或 $A=0, B>0$），可以进行**精确的哈希（Hash）或去重**，彻底避免浮点误差。

---

### 二、基础向量工具与点线关系

掌握点积（Dot Product）和叉积（Cross Product）是处理直线问题的关键。

设直线由点 $A, B$ 确定（方向向量 $\vec{v} = \vec{AB}$），另外有一点 $P$。

#### 1. 点在直线的哪一侧（Cross Product / 跨立实验基础）
计算叉积 $\text{cross}(\vec{AB}, \vec{AP}) = (B.x - A.x)(P.y - A.y) - (B.y - A.y)(P.x - A.x)$：
* **大于 0**：$P$ 在向量 $\vec{AB}$ 的**左侧**。
* **小于 0**：$P$ 在向量 $\vec{AB}$ 的**右侧**。
* **等于 0**：$P$ 在直线 $AB$ **上**（共线）。

#### 2. 点到直线的距离
利用平行四边形面积公式（叉积的几何意义）：
$$\text{Distance}(P, AB) = \frac{|\vec{AB} \times \vec{AP}|}{|\vec{AB}|}$$

#### 3. 点在直线上的投影点（Projection）
利用点积求出 $P$ 在直线 $AB$ 上的投影点 $Q$：
$$Q = A + \frac{\vec{AP} \cdot \vec{AB}}{|\vec{AB}|^2} \cdot \vec{AB}$$

#### 4. 点关于直线的对称点（Reflection）
直接利用投影点 $Q$：
$$P_{reflection} = 2Q - P$$

---

### 三、直线与直线的关系

设直线 $L_1 = P_1 + t \cdot \vec{v}_1$，直线 $L_2 = P_2 + s \cdot \vec{v}_2$。

#### 1. 平行与垂直判断
* **平行**：$\vec{v}_1 \times \vec{v}_2 = 0$（叉积为 0）。
* **重合**：在平行的基础上，$\vec{v}_1 \times (P_2 - P_1) = 0$。
* **垂直**：$\vec{v}_1 \cdot \vec{v}_2 = 0$（点积为 0）。

#### 2. 求两直线交点（Intersection）
当 $\vec{v}_1 \times \vec{v}_2 \neq 0$ 时，利用叉积面积比求解（比常规解方程更不易出错且极其简洁）：
$$u = \frac{(P_2 - P_1) \times \vec{v}_2}{\vec{v}_1 \times \vec{v}_2}$$
$$\text{交点 } X = P_1 + u \cdot \vec{v}_1$$

---

### 四、线段（Segment）特有性质与操作

线段可看作带范围限制的直线。

#### 1. 线段相交判定
* **快速排斥实验**：以两线段为对角线的矩形如果不相交，则线段一定不相交。
* **跨立实验**：线段 $AB$ 的两端点位于线段 $CD$ 所在的直线两侧，且线段 $CD$ 的两端点位于线段 $AB$ 所在的直线两侧。
  $$\text{cross}(\vec{AB}, \vec{AC}) \times \text{cross}(\vec{AB}, \vec{AD}) \le 0 \quad \text{且} \quad \text{cross}(\vec{CD}, \vec{CA}) \times \text{cross}(\vec{CD}, \vec{CB}) \le 0$$
  *(注意：端点重合或在上属于特例，需结合 eps 特判)*。

#### 2. 点到线段的最短距离
点 $P$ 到线段 $AB$ 的距离不一定是垂线段长度，需要分类讨论投影点 $Q$ 是否落在线段上：
* 若 $\vec{AP} \cdot \vec{AB} < 0$，最近点为端点 $A$。
* 若 $\vec{BP} \cdot \vec{BA} < 0$，最近点为端点 $B$。
* 否则，最近点为投影点 $Q$，距离为点到直线的距离。

---

### 五、高频进阶算法与应用

#### 1. 半平面交（Half-Plane Intersection）—— $O(N \log N)$
* **定义**：多条直线将平面分割，每条直线的一侧定义为“半平面”，求所有半平面的交集（结果通常是一个凸多边形，或为空、无界）。
* **经典算法**：**排序 + 双端队列（Sakai 算法）**。
  1. 将所有半平面的方向向量按极角排序。
  2. 维护一个双端队列（Deque）存储当前构成凸多边形边界的直线。
  3. 依次加入直线，弹出对新直线不合法的队尾/队首直线。
* **应用**：
  * 判定凸多边形是否存在“核”（Kernel）。
  * 求解凸多边形的交。
  * 线性规划问题（二维）。

#### 2. 李超线段树（Li Chao Tree）
* **定义**：用于动态维护一堆直线 $y = kx + b$（或线段），支持高效查询在某个横坐标 $x = x_0$ 处的最大/最小 $y$ 值。
* **复杂度**：插入一条直线 $O(\log N)$，查询 $O(\log N)$。
* **应用**：斜率优化 DP 的通用替代方案（特别是当斜率或横坐标不单调时）。

#### 3. 斜率优化 DP 与 Convex Hull Trick (CHT)
* **思想**：将 DP 转移方程写成 $y = kx + b$ 的形式，其中 $b$ 包含 DP 状态，$k$ 与 $x$ 分别代表决策点与当前点的相关参数。
* **算法**：
  * 当 $x$ 和 $k$ 都单调：用**单调队列**维护凸包（$O(N)$）。
  * 当仅 $x$ 单调：用**单调栈 + 二分**查询（$O(N \log N)$）。
  * 都不单调：用**李超线段树**或 **平衡树（CDQ 分治 / Dynamic CHT）**（$O(N \log N)$）。

#### 4. 旋转卡壳（Rotating Calipers）
* **应用**：利用平行切线（卡壳）沿凸包旋转，求解凸多边形的最远点对（直径）、最小外接矩形、多边形间最小距离等。

#### 5. 点线对偶性（Duality）
* **概念**：二维平面上的点 $(a, b)$ 可以映射为直线 $y = ax - b$；直线 $y = kx + m$ 可以映射为点 $(k, -m)$。
* **应用**：将“点集性质”与“直线集性质”相互转换（例如：求是否有三点共线转换成三线交于一点）。

---

### 六、模板编写与避坑指南

#### 1. 浮点数精度（`eps`）
计算几何中极易因 `double` 精度累积误差产生逻辑错误：
```cpp
const double eps = 1e-9;
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}
int cmp(double x, double y) {
    return sgn(x - y);
}
```

#### 2. 能用整数就不用浮点数
* 判定点是否在直线一侧、线段相交检测、坐标去重等，只要输入为整数，**全程使用 `long long` 的叉积和点积**，完全避免精度问题。

#### 3. 基础代码模板（向量与直线）
```cpp
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
int sgn(double x) { return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1); }

struct Point {
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
    Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }
};
typedef Point Vector;

double dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
double cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }

struct Line {
    Point p;   // 直线上一点
    Vector v;  // 方向向量
    double ang; // 极角（半平面交排序用）
    Line() {}
    Line(Point p, Vector v): p(p), v(v) { ang = atan2(v.y, v.x); }
    
    // 直线交点
    friend Point intersect(Line A, Line B) {
        Vector u = A.p - B.p;
        double t = cross(B.v, u) / cross(A.v, B.v);
        return A.p + A.v * t;
    }
};
```
```

#### 数学 / 几何数学 / 平行四边形求面积

**模板.cpp**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    long long dx, dy, c;
    // 重载小于号，用于后续对向量分组和 C 值排序
    bool operator<(const Segment& other) const {
        if (dx != other.dx) return dx < other.dx;
        if (dy != other.dy) return dy < other.dy;
        return c < other.c;
    }
};

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<long long, long long>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    vector<Segment> segs;
    // 预分配内存，C(n, 2) 对点
    segs.reserve(n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = points[j].first - points[i].first;
            long long dy = points[j].second - points[i].second;
            long long start_x, start_y;

            // 规范化向量方向, 指向右上方，避免同一线段出现两种方向的向量
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
                start_x = points[j].first;
                start_y = points[j].second;
            } else {
                start_x = points[i].first;
                start_y = points[i].second;
            }

            long long c = dy * start_x - dx * start_y;
            segs.push_back({dx, dy, c});
        }
    }

    // 排序后，相同 (dx, dy) 的线段会聚集在一起，且按 c 值从小到大排列
    sort(segs.begin(), segs.end());

    long long max_area = 0;
    int m = segs.size();
    
    // 遍历排序后的数组，寻找同组 (dx, dy) 的最大面积
    for (int i = 0; i < m; ) {
        int j = i;
        // 找到相同 (dx, dy) 的区间 [i, j-1]
        while (j < m && segs[j].dx == segs[i].dx && segs[j].dy == segs[i].dy) {
            j++;
        }
        
        // 因为按 c 排过序，同组中面积最大必为 尾部 c 减去 头部 c
        long long current_area = segs[j - 1].c - segs[i].c;
        if (current_area > max_area) {
            max_area = current_area;
        }
        
        i = j; // 跳到下一组向量
    }

    if (max_area == 0) {
        cout << "-1\n";
    } else {
        // 核心避坑：不转 double，直接拼接 ".0" 输出
        cout << max_area << ".0\n";
    }

    return 0;
}
```

**简介.md**

```md
# 【计算几何】等长平行线段构成平行四边形的面积最值问题

### 1. 核心问题概述
给定平面上 $N$ 个整点，求任意 4 个点能构成的平行四边形的最大面积。数据范围较大（$N \le 1000$，坐标 $\le 10^9$），直接枚举 4 个点 $O(N^4)$ 或枚举对角线 $O(N^3)$ 均会超时。

### 2. 关键核心转换（Tricks）
* **Trick 1：向量化替代斜率与边长**
  将点对 $(i, j)$ 转化为向量 $(dx, dy)$。通过强制约束 $dx > 0$（或 $dx=0, dy>0$）来对无向线段进行**方向规范化**。相同 $(dx, dy)$ 的线段天然满足【平行且等长】。
  
* **Trick 2：解析几何降维（无浮点数面积）**
  定义线段截距常数：$C = dy \cdot x - dx \cdot y$（本质为直线一般式常数项）。
  同组向量的两条线段，其构成的平行四边形面积满足：$\text{Area} = |C_1 - C_2|$。
  *优点*：全整数运算，完美避开 `double` 的精度丢失及开根号运算。

* **Trick 3：极值极效维护**
  因为面积为 $|C_1 - C_2|$，要让同组向量的面积最大，只需维护该组内 $C$ 的最大值（$C_{max}$）和最小值（$C_{min}$）。最大面积即为 $C_{max} - C_{min}$。

### 3. 经典易错点（Pitfalls）
1. **长整型溢出**：坐标高达 $10^9$，在计算 $C = dy \cdot x - dx \cdot y$ 时，中间结果会达到 $2 \times 10^9 \times 10^9 = 2 \times 10^{18}$，必须全程使用 64 位整型（C++ 的 `long long` 或 Java 的 `long`）。
2. **输出精度伪命题**：题目要求保留一位小数。由于整点平行四边形面积必为整数，不要将 `long long` 的最大面积强转为 `double`（大整数转浮点数会丢失低位精度导致 WA），应当直接以字符串形式拼接 `".0"` 输出。

### 4. 模版代码 (C++ 排序高效版)
// 此处贴上双重循环生成线段 + 结构体排序 / Map 分组的代码
```

#### 数学 / 数论 / GCD

**gcd与lcm结论.md**

```md
1. 求多个数的最小公倍数，把所有数的质因数按照各自的最高次幂乘起来最得到了最小公倍数
2. 求多个数的最大公约数，把所有数的质因数按照各自的最低次幂乘起来最得到了最大公约数
3. 求两个数的最小公倍数和最大公约数的关系：
   - 设两个数为 $a$ 和 $b$，则有：
   $$\text{lcm}(a, b) \times \text{gcd}(a, b) = a \times b$$
   - 由此可以得到：
   $$\text{lcm}(a, b) = \frac{a \times b}{\text{gcd}(a, b)}$$

> 求各个数的质因数分解可以使用试除法，或者使用欧几里得算法求最大公约数，再利用最大公约数求最小公倍数。
```cpp
vector<pair<long long, int>> prime_factorize(long long n) {
    vector<pair<long long, int>> factors;
    
    // 只需遍历到 sqrt(n)
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) { // i 一定是质数 (因为所有的合数因子早就被前面更小的质数除干净了)
            int count = 0;
            // 榨干这个质因子
            while (n % i == 0) {
                count++;
                n /= i;
            }
            factors.push_back({i, count});
        }
    }
    
    // 💡 灵魂收尾：
    // 榨干了所有 <= sqrt(n) 的因子后，如果 n 仍然 > 1，
    // 说明剩下的这个 n 就是那个唯一大于 sqrt(N) 的质因子！
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}
```
```

**方案数.cpp**

```cpp
/**
 * 例题：[https://www.matiji.net/exam/brushquestion/20/4777/C98C14523F069FECB0DEED64F00CEAB0?from=1]
 * 求从数组中选出若干个元素，使得它们的最大公约数恰好为x, 求选法的个数。
 * 直接求“GCD 恰好等于 $x$”的方案数非常困难，因为条件非常严苛。但是求“GCD 是 $x$ 的倍数”的方案数却极其简单：
 * 只要选出来的数全是 $x$ 的倍数即可
 * 外层循环枚举 $i$，内层循环枚举 $i$ 的倍数。执行次数为：$\frac{N}{1} + \frac{N}{2} + \frac{N}{3} + \dots + \frac{N}{N}$
 * 根据高数知识，这是调和级数，其总和逼近 $N \ln N$。时间复杂度：$O(N \log N)$（对于 $N=10^6$，运算量只有 $1.4 \times 10^7$ 左右，非常快）。
 */

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_VAL = 1000005; // 数组中出现的最大数值（值域上限）

int cnt[MAX_VAL];        // cnt[i] 统计原数组中数字 i 出现的次数
long long f[MAX_VAL];    // f[i] 记录 GCD 恰好等于 i 的方案数

long long fast_pow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    
    int max_num = 0; // 记录整个数组的最大值，作为倒推的起点
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
        max_num = max(max_num, x);
    }

    // 从最大值倒推回 1
    for (int i = max_num; i >= 1; --i) {
        int multiple_count = 0;
        
        // 1. 统计原数组中有多少个数是 i 的倍数 (调和级数累加)
        for (int j = i; j <= max_num; j += i) {
            multiple_count += cnt[j];
        }

        // 2. 计算 g[i] (即全都是 i 的倍数的组合方案数)
        // -------------------------------------------------------------
        // 【核心变化点】：根据题目要求选子集、选2个数、还是选序列，这里公式不同
        // 场景 A (选非空子集): g[i] = 2^{multiple_count} - 1
        long long gi = (fast_pow(2, multiple_count) - 1 + MOD) % MOD;
        
        // 场景 B (任意选 k 个数构成序列): g[i] = multiple_count^k
        // long long gi = fast_pow(multiple_count, k);
        
        // 场景 C (只选两个不同的数): g[i] = C(multiple_count, 2)
        // long long gi = 1LL * multiple_count * (multiple_count - 1) / 2 % MOD;
        // -------------------------------------------------------------
        
        f[i] = gi;

        // 3. 容斥减法：减去 GCD 严格等于 i 的倍数的那些非法方案
        for (int j = i * 2; j <= max_num; j += i) {
            // 注意减法取模的规范写法，防止出现负数
            f[i] = (f[i] - f[j] + MOD) % MOD; 
        }
    }

    // cout << f[1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

```

##### 数学 / 数论 / 二进制 / LogTrick

**logTrick.md**

```md
[按位或最大的最小子数组长度](https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/?envType=daily-question&envId=2025-07-29)

# 算法笔记：LogTrick (区间最值/GCD 优化)

## 1\. 核心原理：单调性与 Log 级变化

LogTrick 适用于满足以下性质的运算 $\odot$（如 `&`, `|`, `gcd`）：

**核心观察：**
当我们固定子数组的 **一端（比如右端点 $r$）**，并向另一端扩展（比如左端点 $l$ 从 $r$ 向左移动）时，区间累计值 $Val(l, r) = A[l] \odot \dots \odot A[r]$ 的变化非常“慢”。

1.  **对于按位或 (`|`)**：

      * $A \mid B \ge A$（单调不减）。
      * 每次运算结果变化，至少有一个二进制位从 `0` 变成 `1`。
      * 因为整数（如 `int`）通常只有 30 或 31 个二进制位，所以对于固定的 $r$，随着 $l$ 减小，不同的 $Val(l, r)$ 值 **最多只有约 30 个**。

2.  **对于按位与 (`&`)**：

      * $A \& B \le A$（单调不增）。
      * 每次变化至少有一个 `1` 变成 `0`。同理，不同的值最多只有约 30 个。

3.  **对于最大公约数 (`gcd`)**：

      * $\gcd(A, B) \le A$（单调不增）。
      * 每次变化，结果必然变成前一个值的真因数（至少减少一半）。
      * 因此不同的 GCD 值最多也只有 $O(\log (\max A))$ 个。

**结论：**
虽然子数组总数是 $O(N^2)$，但以 $r$ 结尾的所有子数组的运算结果，**去重后**只有 $O(\log V)$ 种。

-----

## 2\. 算法流程 (通用模板)

我们通常 **枚举右端点 $r$**，并维护一个 **列表 (List/Vector)**，该列表存储了“以 $r$ 结尾的所有可能的运算结果及其对应的左端点位置”。

**步骤：**

1.  初始化一个空的列表 `prev`，存 `pair<value, index>`。
2.  遍历数组每个元素 $x$（作为当前的右端点 $i$）：
      * 创建一个新列表 `curr`。
      * **加入自身**：将 `{x, i}` 加入 `curr`（代表子数组 `[i, i]`）。
      * **传递旧值**：遍历 `prev` 中的每个 `{val, idx}`：
          * 计算新值 `new_val = val ⊙ x`。
          * 将 `{new_val, idx}` 加入 `curr`。
      * **关键步骤（原地去重）**：由于运算的单调性，相同的 `new_val` 必定是连续出现的。我们在 `curr` 中只保留相同值的 **最右侧**（或最左侧，视题目要求）记录。
3.  利用 `curr` 统计答案（例如找最大值、计数等）。
4.  更新 `prev = curr`，进入下一次循环。

-----

## 3\. 复杂度分析

  * **外层循环**：遍历 $N$ 个元素。
  * **内层操作**：列表长度严格限制在 $O(\log V)$ 以内（对于 32 位整数，不超过 30 个）。
  * **总时间复杂度**：$O(N \log V)$。
  * **空间复杂度**：$O(\log V)$。

-----

## 4\. 实战代码：解决 LeetCode 2411

题目 要求找到 **以 $i$ 为左端点** 的子数组，使得按位或值最大，且长度最小。
为了方便处理“以 $i$ 为左端点”，我们可以 **从右向左** 遍历（LogTrick 的方向是灵活的）。

```cpp
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        // ors 存储：{按位或的值, 该值对应的最右边的下标}
        // 这里的逻辑是：对于固定的左端点 i，随着右端点 j 增大，OR 值会增加。
        // 我们记录每个 OR 值第一次出现（或者题目要求的特定位置）的下标。
        vector<pair<int, int>> ors; 

        for (int i = n - 1; i >= 0; --i) {
            // 1. 加入当前元素本身
            ors.push_back({0, i}); // 初始放入一个 dummy 或直接处理 nums[i]
            
            // 2. 更新所有已有的 OR 值
            for (auto& p : ors) {
                p.first |= nums[i];
            }
            
            // 3. 原地去重 (LogTrick 的核心)
            // 我们需要保留对于同一个 OR 值，下标 最小 的那个（因为要求长度最小）
            // 或者根据逻辑，保留下标 最大 的那个。
            // 在本题中，我们从右往左遍历，旧的区间在右边。
            // 如果 nums[i] | x == nums[i] | y，且 x < y，
            // 说明从 i 到 x 已经是这个值了，到 y 也是这个值。
            // 为了维护列表精简，我们去重。
            vector<pair<int, int>> next_ors;
            next_ors.push_back({nums[i], i});
            
            for(auto& p : ors) {
                // 如果当前值和上一个存的值不同，就放进去
                // 这里的去重逻辑保证了 ors 的大小不超过 32
                if(next_ors.back().first != p.first) {
                    next_ors.push_back(p);
                } else {
                    // 如果值相同，我们在本题中不需要更新下标，
                    // 因为我们想要长度最小（也就是右端点越靠左越好）。
                    // next_ors.back() 已经是较小的下标了（因为是新加入的或者之前的）。
                    // *修正*：对于 LC2411，实际上我们可以只维护每个 bit 最后出现的位置更简单，
                    // 但用 LogTrick 的通用写法如下：
                    next_ors.back().second = p.second; // 保留更靠右的下标用于 max 判断？
                    // 其实本题特殊，标准 LogTrick 通常是从左往右。
                    // 下面给出一个最通用的、好理解的 从右向左 写法：
                }
            }
            ors = next_ors;

            // 4. 计算答案
            // 题目要求：最大 按位或。显然后面的 range OR 是单调增的。
            // ors 里的最后一个元素一定是包含最广范围的，也就是 OR 最大值。
            // 它的 value 是最大 OR，但题目要“长度最小”。
            // 在 ors 列表中，值是单调递增的（因为越往右 or 越多）。
            // 最大的 OR 值就在 ors.back().first。
            // 我们需要找到达到这个最大值的 最小下标。
            // 由于去重时合并了，我们需要稍作调整策略：
            // 实际上，max(B_ik) 就是 ors 列表里所有元素 OR 起来，或者说列表里最大的那个值。
            // 列表里第一个达到最大值的 pair 的下标就是我们要的。
            
            // 更简单的逻辑：直接看 ors 中最大的那个值对应的 index
            // 因为是从右向左遍历，ors.back() 是最远的，ors[0] 是最近的。
            // 列表中的值是：[nums[i], ..., max_val]。值递增。
            // 我们要找第一个达到 max_val 的位置。其实就是 ors.back()，
            // 但因为去重逻辑，我们需要保留“使得值变化的那个最靠左的下标”？
            // 不，本题中我们应该保留“值相同下标越小越好”还是“下标越大越好”？
            // 题目：以 i 为起点。找最小子数组。即右端点 j 越小越好。
            // 所以在去重时，如果 val 相同，我们应该保留 index 小的。
        }
        return ans;
    }
};
```

**修正后的、更清晰的 LogTrick 模板（解决 LC 2411）：**

```cpp
vector<int> smallestSubarrays(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    // 列表存储 {OR值, 该值对应的右端点下标}
    vector<pair<int, int>> ors; 

    for (int i = n - 1; i >= 0; --i) {
        // 1. 当前元素自成一组
        ors.push_back({nums[i], i});
        
        // 2. 更新列表中的值
        for (auto& p : ors) p.first |= nums[i];
        
        // 3. 去重 (LogTrick 核心)
        // 此时 ors 中的值是单调递增的（越往后 OR 的数越多）。
        // 如果 adjacent 两个元素值相同，说明中间那段数对 OR 结果没贡献。
        // 对于本题（求最短长度），对于相同的 OR 值，我们要保留 下标更小 的那个（靠左的）。
        // 因为是从右向左遍历，新加入的 {nums[i], i} 在末尾（push_back），
        // 实际上我们应该新建一个 list 来做 merge。
        
        vector<pair<int, int>> next_ors;
        next_ors.push_back({nums[i], i}); // 起点
        
        // 遍历旧列表，进行合并
        for (int k = 0; k < ors.size(); ++k) {
            // 如果当前值和 list 最后一个值不同，说明值变大了，加入
            if (ors[k].first != next_ors.back().first) {
                next_ors.push_back(ors[k]);
            } else {
                // 如果值相同，因为 ors[k].second 比 next_ors.back().second 大（更靠右），
                // 而我们要找“最短”子数组（即右端点越小越好），
                // 所以我们保留 next_ors.back() 里的下标（它是更小的）。
                // 什么都不做，直接跳过 ors[k]
            }
        }
        ors = next_ors;
        
        // 4. 答案就是列表里最大那个值对应的下标
        // 列表里的值单调递增，最后一个就是最大 OR 值。
        // 它的 second 就是达到该值所需的最小右端点。
        ans[i] = max(1, ors.back().second - i + 1);
    }
    return ans;
}
```

## 5\. 总结

**LogTrick** = **固定一端扫描** + **利用位运算单调性** + **维护 Log 个候选值的列表**。
它是解决区间 AND/OR/GCD 计数或最值问题的杀手锏。
```

**核心教程.md**

```md
算法竞赛进阶：Log Trick (对数降维技巧) 核心教程

一、 什么是 Log Trick？

Log Trick 并不是某一个具体的数据结构（像线段树、树状数组），而是一种基于特定运算“单调且突变”性质的状态压缩思想。

在面对涉及求所有子区间（$O(N^2)$ 个区间）的某种运算结果时，Log Trick 能把 $O(N^2)$ 的时间复杂度强行压缩到 $O(N \log V)$ （$V$ 为值域），从而让你在 $10^5 \sim 10^6$ 的数据量下轻松跑过。

二、 适用场景：Log Trick 的“三剑客”

Log Trick 仅适用于满足以下两个性质的运算：

单调性：区间越长，结果越小（或越大）。

极速收敛（断崖式突变）：一旦数值发生变化，至少是以倍数（或位级）剧变，导致总变化次数被死死限制在 $\log_2(V)$ 次以内。

在算法竞赛中，Log Trick 几乎只用于这“三剑客”：

最大公约数 ($\gcd$)：单调递减。每次变化必定成为原来数字的约数，至少缩小一半。最多变化 $\approx 30$ 次。

按位与 (&)：单调递减。每次变化必定有二进制位从 1 变成 0。最多变化 $\approx 30$ 次。

按位或 (|)：单调递增。每次变化必定有二进制位从 0 变成 1。最多变化 $\approx 30$ 次。

(注意：异或 ^ 忽大忽小，加法 + 变化平缓，均不适用于 Log Trick！)

三、 核心思想：固定右端点，压缩左端点

假设我们有一个数组 a，我们要考察以 $R$ 为右端点的所有连续子区间 $[L, R]$ （$L$ 从 $R$ 往左倒推到 $1$）。

以 按位与 (&) 为例：
假设数组为：[7, 7, 7, 6, 6, 6, 4]，当前 $R = 7$（最后一个元素 4）。
从右往左看，区间 $[L, R]$ 的按位与结果会是：

$L=7$: 4

$L=6$: 6 & 4 = 4

$L=5$: 6 & 6 & 4 = 4

$L=4$: 6 & 6 & 6 & 4 = 4

$L=3$: 7 & 6 & 6 & 6 & 4 = 4

...
你会发现，虽然 $L$ 有成千上万个，但算出来的结果全都是一段一段相同的！
在 Log Trick 中，对于固定的 $R$，我们不需要记录所有的 $L$，我们只需要记录：“每一个不同的结果值，它最后一次出现的左端点在哪里”。

四、 标程模板：万能的 vector<pair>

下面以“求一个数组中，所有子区间的按位与（或 GCD）的结果种类及对应个数”为例，给出一个万能的 Log Trick 模板。
``` cpp
#include <iostream>
#include <vector>
#include <map>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 用于记录某种结果值在全数组中一共出现了多少次（如果题目不问出现次数，可省略）
    map<int, long long> value_counts; 

    // cur_states 存储以【上一个元素】结尾的所有不同的状态
    // pair.first = 运算结果值 (例如 gcd, bitwise AND)
    // pair.second = 这种结果值对应的【最靠右的起始下标 L】
    vector<pair<int, int>> cur_states;

    for (int r = 1; r <= n; r++) {
        vector<pair<int, int>> next_states;
        
        // 1. a[r] 自身构成一个长度为 1 的区间
        next_states.push_back({a[r], r});

        // 2. 将旧的状态全部与新元素 a[r] 结合
        for (auto& p : cur_states) {
            // 这里替换成题目要求的操作，比如 & (按位与), | (按位或), gcd 等
            int new_val = p.first & a[r]; 
            
            // 3. 【核心去重剪枝】：如果值没变，保留更靠右的下标（贪心）
            // 因为是从后往前遍历，next_states 里的值是单调递减（或递增）的
            // 所以相同的 new_val 必然紧挨着！
            if (next_states.back().first == new_val) {
                // next_states.back().second 已经是最靠右的了，无需修改
                // 因为我们按旧集合顺序遍历，旧集合第一个产生该 new_val 的 p.second 必然最大
                continue; 
            } else {
                next_states.push_back({new_val, p.second});
            }
        }
        
        // 4. 更新当前状态
        cur_states = next_states;

        // 5. 【实战应用】：统计结果
        // 现在 cur_states 里面记录了以 r 结尾的所有“断崖点”。
        // 每两个断崖点之间的距离，就是这个值出现的次数！
        int last_l = r + 1; // 虚拟的最右侧边界
        for (auto& p : cur_states) {
            // 这个值覆盖了区间段长度
            int count = last_l - p.second;
            value_counts[p.first] += count;
            last_l = p.second; // 更新边界
        }
    }

    // 此时 value_counts 里已经完美统计了 O(N^2) 个子区间的所有的结果
    // 且全程只花了 O(N log V) 的时间！
}
``` 

五、 实战做题信号

当你在题目中看到以下特征时，大脑应该立刻亮起 Log Trick 的警报：

题目求连续子段（Subarray / Continuous Segment）。

对子段执行的操作是 GCD、LCM（最小公倍数也可转换）、位运算（与 &，或 |）。

数据范围 $N \approx 10^5 \sim 5 \times 10^5$，暴力 $O(N^2)$ 会被卡，但 $O(N \log N)$ 稳过。

询问某种运算结果等于 $X$ 的子段有多少个，或者让你处理多组离线查询（像你做过的那道题）。

记住这个模板，Log Trick 会从一种“很神妙”的解法，变成你手中的“常规武器”！




```

##### 数学 / 数论 / 二进制 / SOSDP

**sosdp.md**

```md
**SOS DP** 全称是 **Sum Over Subsets Dynamic Programming**（**子集和动态规划**）。它是算法竞赛和状态压缩 DP 中一种非常高频且高效的优化技巧。

---

### 💡 SOS DP 是用来解决什么问题的？

假设给你一个长度为 $2^N$ 的数组 $A$（下标用 $N$ 位的二进制状态 `mask` 表示）。
现在要求对于**每一个**二进制掩码 `mask`，算出它的**所有子集的权值和**：

$$F[\text{mask}] = \sum_{\text{sub} \subseteq \text{mask}} A[\text{sub}]$$

*(注：$\text{sub} \subseteq \text{mask}$ 表示 $\text{sub}$ 的每一个为 1 的二进制位，在 $\text{mask}$ 中也必定为 1。)*

#### 两种解法的复杂度对比：

1. **暴力枚举子集**（利用 `sub = (sub - 1) & mask`）
   * 复杂度：$O(3^N)$
   * 当 $N = 20$ 时，$3^{20} \approx 3.5 \times 10^9$，**必定超时 (TLE)**。

2. **使用 SOS DP**
   * 复杂度：$O(N \cdot 2^N)$
   * 当 $N = 20$ 时，$20 \times 2^{20} \approx 2 \times 10^7$，可以在 **0.02 秒内**瞬间算完！

---

### 🧠 核心思想与状态转移

SOS DP 的核心思想是：**按位（Bit by Bit）逐渐放开限制，递推求解。**

定义状态 $dp[i][\text{mask}]$ 表示：
> 考虑二进制的前 $i$ 位（即从第 $0$ 到第 $i-1$ 位），可以是 $\text{mask}$ 的子集；而第 $i$ 位及更高的位，必须与 $\text{mask}$ **完全相同**的所有 $\text{sub}$ 的 $A[\text{sub}]$ 之和。

#### 转移逻辑（看第 $i$ 位是 0 还是 1）：

对于状态 $\text{mask}$ 的第 $i$ 位：
1. **如果第 $i$ 位是 `0`**：
   那么子集 $\text{sub}$ 的第 $i$ 位**只能是 `0`**。
   $$dp[i][\text{mask}] = dp[i - 1][\text{mask}]$$

2. **如果第 $i$ 位是 `1`**：
   那么子集 $\text{sub}$ 的第 $i$ 位既可以是 `0`，也可以是 `1`。
   - 第 $i$ 位填 `1` 的贡献：$dp[i - 1][\text{mask}]$
   - 第 $i$ 位填 `0` 的贡献：$dp[i - 1][\text{mask} \oplus (1 \ll i)]$
   $$dp[i][\text{mask}] = dp[i - 1][\text{mask}] + dp[i - 1][\text{mask} \oplus (1 \ll i)]$$

#### 空间优化：
注意到第一维 $i$ 只和 $i-1$ 有关，因此可以滚动数组优化，把第一维直接省去！

---

### 💻 模板代码实现

#### 1. 求子集和（Submask Sum）
计算 $F[\text{mask}] = \sum_{\text{sub} \subseteq \text{mask}} A[\text{sub}]$

```cpp
#include <vector>

using namespace std;

// N 是二进制位数，A 是原数组（大小为 1 << N）
vector<long long> sos_dp_submask(int N, vector<long long>& A) {
    vector<long long> F = A; // 初始状态 dp[0][mask] = A[mask]

    for (int i = 0; i < N; ++i) { // 遍历二进制的每一位
        for (int mask = 0; mask < (1 << N); ++mask) {
            if (mask & (1 << i)) { // 如果第 i 位是 1
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }
    return F;
}
```

#### 2. 求超集和（Superset Sum）
计算 $F[\text{mask}] = \sum_{\text{mask} \subseteq \text{super}} A[\text{super}]$ （即计算包含当前状态的所有更大状态的和）

```cpp
vector<long long> sos_dp_superset(int N, vector<long long>& A) {
    vector<long long> F = A;

    for (int i = 0; i < N; ++i) {
        for (int mask = (1 << N) - 1; mask >= 0; --mask) {
            if (!(mask & (1 << i))) { // 如果第 i 位是 0
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }
    return F;
}
```

---

### 🎯 常见应用场景

1. **求按位与（AND）为 0 的数对数量**：
   - 条件 $a_i \text{ AND } a_j = 0$ 等价于 $a_j \subseteq \text{compliment}(a_i)$（$a_j$ 是 $a_i$ 的补码的子集）。
   - 可以先用频次数组建出 $A$，再用 SOS DP 求出每个掩码的子集数，从而 $O(1)$ 回答满足条件的对数。

2. **快速 Zeta 变换（Fast Zeta Transform / FMT）**：
   - SOS DP 的本质其实就是高维 Poset（偏序集）上的快速 Zeta 变换，常用于处理二进制卷积（如 OR 卷积、AND 卷积）。

3. **容斥原理与子集卷积**：
   - 配合容斥原理或者子集卷积（Subset Convolution），解决多集合覆盖、独立集计数等高级图论与组合计数问题。

### 🌟 总结一览

| 概念 | 含义 | 复杂度 |
| :--- | :--- | :--- |
| **求解目标** | 算出所有子集/超集的元素权值和 | - |
| **暴力做法** | 枚举每个 mask 的子集 | $O(3^N)$ |
| **SOS DP** | 按位递推更新子集贡献 | **$O(N \cdot 2^N)$** |
```

##### 数学 / 数论 / 二进制 / 异或

**异或.md**

```md
1. 判断$a_i$与$a_i \oplus b$ 的大小关系，取决于$a_i$在`b`的最高位的处是否为1，如果为1，则$a_i < a_i \oplus b$，否则$a_i > a_i \oplus b$。

2. 当批量计算涉及到异或运算时，可以考虑使用某一位的二进制表示来进行分组，分组后再进行计算。

3. 将异或结果按二进制独立拆开。对于第k位二进制，区间异或时，当且仅当异或和$P_j$于$P_(i-1)$在第k位二进制不同，则该位异或结果为1,此时区间$[i,j]$才会对第k位产生贡献。

4. 异或边权完全图的最短路

$$x \oplus y + y \oplus z \geq x \oplus z$$
即 **直接走就是最短路，任何绕路都不会更短**。

5. 1 到 n 的异或和公式

$$1 \oplus 2 \oplus 3 \oplus ... \oplus n = \begin{cases} n & n \mod 4 = 0 \\ 1 & n \mod 4 = 1 \\ n + 1 & n \mod 4 = 2 \\ 0 & n \mod 4 = 3 \end{cases}$$
```

##### 数学 / 数论 / 二进制 / 逐位排序

**逐位排序.md**

```md
# 📝 算法笔记：位运算与数学 - 二进制位的独立性

> **题目来源**：牛客/算法竞赛 (image_701bae.png)
> **核心标签**：`Bit Manipulation` `Math` `Greedy` `Constructive`
> **一句话总结**：当操作仅针对某一特定二进制位进行交换时，不同位之间互不干扰，可将问题拆解为 $n$ 个独立的子问题分别求解。

## 1. 题目重述

**输入**：
- 一个整数 $n$ ($1 \le n \le 20$)。
- 一个长度为 $2^n$ 的数组 $a$，包含 $0$ 到 $2^n - 1$ 的所有整数（即一个排列）。

**操作**：
- 选择 $i$ 和 $j$，交换 $a_i$ 和 $a_{i+1}$ 的**第 $j$ 位**（二进制位，从低到高）。
- 注意：这**不是**交换数组中的两个数，而是交换两个数在二进制下的某一位。

**目标**：
- 使用最少的操作次数，使数组 $a$ 变为**升序**排列（即 $a_i = i$, 下标从0开始）。

---

## 2. 数学思维：拆解与独立性

这道题之所以被归类为数学/位运算，是因为它利用了二进制的核心性质：**位独立性**。

### 核心洞察 (Key Insight)
题目允许我们交换相邻两个数的**特定第 $j$ 位**。这意味着：
- 对第 0 位的操作，完全不会影响第 1 位、第 2 位...的数据。
- 对第 $k$ 位的操作，也不会被其他位的操作影响。

**结论**：这是一个**线性可加**的问题。
总的最少操作次数 = $\sum_{j=0}^{n-1} (\text{第 } j \text{ 位还原到目标状态所需的最少交换次数})$

---

## 3. 算法推导

### 步骤一：确定“目标状态”
我们要让数组变成 $0, 1, 2, \dots, 2^n - 1$。我们需要知道在**目标状态**下，每一位的二进制排列规律是什么。

观察 $n=3$ 的情况（$0 \sim 7$）：
- 数字：`000, 001, 010, 011, 100, 101, 110, 111`
- **第 0 位 (Low)**：`0, 1, 0, 1, 0, 1, 0, 1` (周期为 $2^1=2$)
- **第 1 位 (Mid)**：`0, 0, 1, 1, 0, 0, 1, 1` (周期为 $2^2=4$)
- **第 2 位 (High)**：`0, 0, 0, 0, 1, 1, 1, 1` (周期为 $2^3=8$)

**规律**：对于第 $j$ 位，目标序列是由 **“$2^j$ 个 0” 和 “$2^j$ 个 1”** 交替重复构成的。

### 步骤二：计算单位的代价 (Greedy)
对于第 $j$ 位：
1. **提取现状**：遍历输入数组 $a$，把每个数的第 $j$ 位抠出来，形成一个 01 序列 $S_{curr}$。
2. **生成目标**：根据上面的规律，生成目标 01 序列 $S_{target}$。
3. **计算距离**：
   - 我们只能交换相邻的位，这本质上是把序列中的 `1` 移动到它该去的位置。
   - 由于所有的 `1` 都是一样的（indistinguishable），为了操作次数最少，我们应该**贪心匹配**：
     - $S_{curr}$ 中**第 1 个**出现的 `1`，应该移动到 $S_{target}$ 中**第 1 个** `1` 的位置。
     - $S_{curr}$ 中**第 k 个**出现的 `1`，应该移动到 $S_{target}$ 中**第 k 个** `1` 的位置。

**代价公式**：
$$Cost_j = \sum_{k} | \text{Pos}(S_{curr}, 1_k) - \text{Pos}(S_{target}, 1_k) |$$

---

## 4. C++ 代码实现模板

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n;
    cin >> n;
    int t = pow(2, n);
    vector<vector<int>> a(n, vector<int>(t));
    for (int i = 0, x; i < t; i++) {
        cin >> x;
        for (int j = 0; j < n; j++) {
            a[j][i] = 1 & (x >> j);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int k = pow(2, i);
        int cn = 0, index = 0;
        for (int j = 0; j < t; j++) {
            if (a[i][j] == 0) {
                ans += abs(j - index);
                cn++;
                index++;
                if (cn == k) {
                    cn = 0;
                    index += k;
                }
            }
        }
    }
    cout << ans << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    while (_--) {
        solve();
    }
    return 0;
}

```

## 5\. 复杂度分析

  - **时间复杂度**：

      - 外层循环遍历 $n$ 个位。
      - 内层循环遍历长度 $L = 2^n$。
      - 总复杂度：$O(n \cdot 2^n)$。
      - 题目给定 $n \le 20$，计算量约为 $20 \times 10^6 = 2 \times 10^7$，在 1 秒时限内非常安全。

  - **空间复杂度**：

      - 需要存储数组和位置列表，约为 $O(2^n)$。

## 6\. 总结与延伸

  - **位运算的本质**：把整数看作二进制向量。如果操作（如异或、按位交换）各维度互不影响，就可以**降维打击**，把一个大整数问题变成 $n$ 个简单的 0/1 序列问题。
  - **相似题目**：
      - **逆序对问题**：如果题目要求交换整个数字来排序，那就是求逆序对。
      - **LeetCode "Hamming Distance" 类题目**：通常都涉及按位独立统计。


```

#### 数学 / 数论 / 取模

**模运算的世界.md**

```md
### [灵茶山艾府](https://leetcode.cn/discuss/post/3584387/fen-xiang-gun-mo-yun-suan-de-shi-jie-dan-7xgu/)
```

**结论.md**

```md
这是一道非常精彩的数论与前缀和优化结合的题目。

题目要求我们快速处理多次查询，求 $f(l, r) = \sum_{i=l}^{r} (\lfloor \frac{n}{i} \rfloor \bmod i) \pmod{10^9+7}$。因为查询次数 $q$ 高达 $3 \times 10^5$，且 $n$ 高达 $10^{12}$，常规的 $O(n)$ 遍历，甚至单次查询 $O(\sqrt{n})$ 的整除分块都会超时（$O(q\sqrt{n}) \approx 3 \times 10^{11}$ 次操作，必然 TLE）。我们需要一种能够预处理后 **$O(1)$ 响应单次查询**的算法。

### 核心解题思路

#### 1. 拆解取模公式

根据取模运算的定义，对于正整数 $a, b$，有 $a \bmod b = a - b \times \lfloor \frac{a}{b} \rfloor$。
令 $a = \lfloor \frac{n}{i} \rfloor, b = i$，带入可得：


$$\lfloor \frac{n}{i} \rfloor \bmod i = \lfloor \frac{n}{i} \rfloor - i \times \lfloor \frac{\lfloor \frac{n}{i} \rfloor}{i} \rfloor$$


由于嵌套向下取整有一个重要性质：$\lfloor \frac{\lfloor x/a \rfloor}{b} \rfloor = \lfloor \frac{x}{ab} \rfloor$，所以上面的式子可以化简为：


$$T(i) = \lfloor \frac{n}{i} \rfloor - i \times \lfloor \frac{n}{i^2} \rfloor$$

#### 2. 划定分界点 $K = \lfloor \sqrt{n} \rfloor$

仔细观察后面的项 $\lfloor \frac{n}{i^2} \rfloor$。

* 当 $i \le \lfloor \sqrt{n} \rfloor$ 时，这部分需要老老实实计算。因为 $n \le 10^{12}$，所以 $K = \lfloor \sqrt{n} \rfloor \le 10^6$。这个范围足够小，我们可以通过 $O(\sqrt{n})$ 的时间，把 $1$ 到 $K$ 的 $T(i)$ 的前缀和预处理出来。
* 当 $i > \lfloor \sqrt{n} \rfloor$ 时，$i^2 > n$，这意味着 $\frac{n}{i^2} < 1$，所以 $\lfloor \frac{n}{i^2} \rfloor$ **永远等于 0**！
因此，对于所有 $i > K$ 的部分，项极其简化：**$T(i) = \lfloor \frac{n}{i} \rfloor$**。

#### 3. 优化大于 $K$ 部分的求和 ($O(1)$ 查询整除分块)

现在问题变成了：给定一个 $x > K$，如何 $O(1)$ 求 $\sum_{i=K+1}^{x} \lfloor \frac{n}{i} \rfloor$？
通常求 $\lfloor \frac{n}{i} \rfloor$ 的区间和需要用数论分块。但在本题中，因为 $i > K = \lfloor \sqrt{n} \rfloor$，所以 $\lfloor \frac{n}{i} \rfloor$ 的值域域**绝对不会超过 $K$**（即 $1 \le \lfloor \frac{n}{i} \rfloor \le K$）。

既然值域这么小（$\le 10^6$），我们可以**以值域为基础进行预处理**！

* 设 $v = \lfloor \frac{n}{i} \rfloor$，满足该等式的 $i$ 的范围是 $[\lfloor \frac{n}{v+1} \rfloor + 1, \lfloor \frac{n}{v} \rfloor]$。
* 我们可以定义一个数组 `sum_greater[v]`，表示所有使得 $\lfloor \frac{n}{j} \rfloor > v$ 且 $j > K$ 的 $j$ 带来的总贡献。
* 这个数组可以从 $v = K$ 倒推到 $1$ 递推算出来，预处理时间也是 $O(\sqrt{n})$。
* 在查询时，给定 $x > K$。我们先算出 $x$ 所在块的值 $v_x = \lfloor \frac{n}{x} \rfloor$。那么 $\sum_{i=K+1}^x$ 的和就等于：
**（所有 $>v_x$ 的整块的和，即 `sum_greater[v_x]`） + （$v_x$ 这个块在区间内不完整部分的和）**。
这完全是 $O(1)$ 的！

### C++ 代码实现

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    // 必须加上快速 I/O，因为查询量极大
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    int q;
    if (!(cin >> n >> q)) return 0;

    // 确定分界点 K = 根号n
    long long K = sqrt(n);
    while ((K + 1) * (K + 1) <= n) K++;
    while (K * K > n) K--;

    // 预处理第一部分：i <= K 的前缀和
    vector<long long> pref_T(K + 1, 0);
    for (long long i = 1; i <= K; i++) {
        long long v1 = (n / i) % MOD;
        long long v2 = (n / (i * i)) % MOD;
        long long term = (v1 - i * v2) % MOD;
        if (term < 0) term += MOD; // 防负数取模
        pref_T[i] = (pref_T[i - 1] + term) % MOD;
    }

    // 预处理第二部分：i > K 的整除分块后缀和
    vector<long long> sum_greater(K + 2, 0);
    for (long long v = K - 1; v >= 1; v--) {
        // v+2 可能等于 K+1，这是安全的
        long long L_prime = max(K + 1, n / (v + 2) + 1);
        long long R_prime = n / (v + 1);
        long long cnt = max(0LL, R_prime - L_prime + 1) % MOD;
        // sum_greater[v] 存的是对于 j > K，且 floor(n/j) > v 的所有 j 的 floor(n/j) 之和
        sum_greater[v] = (sum_greater[v + 1] + (v + 1) * cnt) % MOD;
    }

    // 定义 O(1) 前缀和查询函数 F(x) = Sum_{i=1}^{x} T(i)
    auto F = [&](long long x) -> long long {
        if (x == 0) return 0;
        if (x <= K) return pref_T[x]; // 小于 K 直接查表
        
        // 大于 K 的部分，先算出包含 K 的基准部分
        long long vx = n / x; // 当前 x 属于的块的 v 值
        
        // 计算属于 vx 块中，有效的大于 K 的边界
        long long L_partial = max(K + 1, n / (vx + 1) + 1);
        long long cnt_partial = max(0LL, x - L_partial + 1) % MOD;
        
        // 大于 vx 的完整块的和 + vx 这个不完整块的部分
        long long Gx = (sum_greater[vx] + (vx % MOD) * cnt_partial) % MOD;
        
        return (pref_T[K] + Gx) % MOD;
    };

    // 响应所有的查询 (前缀和作差)
    for (int i = 0; i < q; i++) {
        long long l, r;
        cin >> l >> r;
        long long ans = (F(r) - F(l - 1)) % MOD;
        if (ans < 0) ans += MOD;
        cout << ans << "\n";
    }

    return 0;
}

```

### 复杂度分析

* **时间复杂度**：预处理两块数组的时间都是严格的 $O(\sqrt{n})$。由于 $n \le 10^{12}$，$\sqrt{n} \le 10^6$，这里大约执行两次百万级别的循环。之后的查询函数 $F(x)$ 内部全都是直接计算的纯常数级推导，单次查询 $O(1)$。总时间复杂度为 $O(\sqrt{n} + q)$，完美通过题目。
* **空间复杂度**：需要开两个大小为 $\approx 10^6$ 的 `long long` 数组，占用内存约为 $16\text{ MB}$，完全在空间限制之内，为 $O(\sqrt{n})$。
```

#### 数学 / 数论 / 因子

**整除.md**

```md
### 一、 尾数判定法

只看数字的最后几位，与前面的数字完全无关。

* **整除 2：** 最后一位是偶数（0, 2, 4, 6, 8）。
* **整除 5：** 最后一位是 0 或 5。
* **整除 4：** 最后两位组成的数字能被 4 整除。
* **整除 8：** 最后三位组成的数字能被 8 整除。

### 二、 求和判定法

将数字的每一位独立拆开相加。

* **整除 3：** 各位数字之和能被 3 整除。
* **整除 9：** 各位数字之和能被 9 整除。

### 三、 加权与交替判定法（从个位开始）

需要对每一位数字赋予不同的“权重”后再相加。**注意：权重都是从个位（即从右向左）开始循环对应的。**

* **整除 11：** 奇数位与偶数位数字的交替和（如 + - + -）能被 11 整除。
* **整除 7：** 从个位起，各位数字分别乘以权值 `{1, 3, 2, 6, 4, 5}` 并循环，加权和能被 7 整除。
* **整除 13：** 从个位起，各位数字分别乘以权值 `{1, 10, 9, 12, 3, 4}` 并循环，加权和能被 13 整除。

### 四、 截尾判定法

利用简单的乘法和减法不断缩小数字的规模。

* **整除 17：** 截去原数的最后一位数字，剩下的数减去**最后一位数字的 5 倍**。如果差能被 17 整除，则原数能被 17 整除。（可反复操作直到能一眼看出来为止）。
* *例子判断 391：* 39 - (1 * 5) = 34，34 能被 17 整除，所以 391 能被 17 整除。



---

### 💻 附：安全的 C++ 大数整除判定模板

在算法竞赛或工程中，判断这种整除规则时，数字往往会大到连 `long long` 都存不下（比如 100 位的数字）。因此，**最标准的做法是将其当作字符串 `std::string` 读入，然后从右向左遍历处理**。这样既杜绝了 `pow` 的浮点误差，又完美解决了大数溢出问题。

**以判断 7 的整除为例（使用权值法）：**

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // 将超大数字作为字符串读入
    string s = "12345678901234567890"; 
    
    // 7 的权值数组
    vector<int> weights = {1, 3, 2, 6, 4, 5}; 
    long long sum = 0;
    
    // 技巧：从个位（字符串的最后一位）开始向左遍历
    int weight_idx = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        // s[i] - '0' 将字符转换回真实的整数
        int digit = s[i] - '0'; 
        
        sum += digit * weights[weight_idx % 6];
        weight_idx++;
    }
    
    if (sum % 7 == 0) {
        cout << s << " 能被 7 整除\n";
    } else {
        cout << s << " 不能被 7 整除\n";
    }
    
    return 0;
}

```

利用这个基于字符串的遍历模板，你只需要替换里面的 `weights` 数组或者加减逻辑，就可以安全且无缝地实现 3、9、11、7、13 的所有判别逻辑了！

```

##### 数学 / 数论 / 因子 / 质因子

**Euler.cpp**

```cpp
#include <vector>
using namespace std;

const int MX = 1e7 + 5;
bool is_prime[MX];     // is_prime[i] 为 true 表示是质数
vector<int> primes;    // 按顺序存放搜集到的所有质数
// 需要在极短时间内求出 1 - N 内的所有质数
void euler_sieve() {
    // 初始化：假设大家都是质数 (除 0 和 1 外)
    fill(is_prime, is_prime + MX, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i < MX; i++) {
        if (is_prime[i]) {
            primes.push_back(i); // 如果是质数，拉入质数群
        }
        
        // 核心内层循环：用 i 和当前已知的质数去拼凑合数
        for (int p : primes) {
            if (i * p >= MX) break; // 越界直接退出
            
            is_prime[i * p] = false; // 筛掉合数
            
            // 💡 欧拉筛的灵魂代码（全场最核心的一句）：
            if (i % p == 0) {
                break; 
            }
            // 为什么这里要 break？
            // 如果 i % p == 0，说明 i 里面已经包含了质因子 p。
            // 既然 p 已经是 i 的因子，那么对于后面更大的质数 p'，
            // 合数 (i * p') 的最小质因子一定还是 p，而不是 p'！
            // 所以 (i * p') 应该留给未来的某个时刻，被 p 给筛掉，现在不需要越俎代庖。
        }
    }
}
```

**spf.cpp**

```cpp

/**
 * 求最小质因数，求质因数个数的代码模板
 */
#include <iostream>
#include <vector>

using namespace std;

const int MX = 1e6 + 5; // 根据题目给定的数字最大范围调整
int spf[MX];    // spf[i] 表示 i 的最小质因数
bool is_inited = false;

// 时间复杂度：O(MX * log(log(MX)))，极其接近 O(MX)
void init_spf() {
    if (is_inited) return;
    is_inited = true;
    
    for (int i = 2; i < MX; i++) {
        spf[i] = i; 
    }
    for (int i = 2; i * i < MX; i++) {
        if (spf[i] == i) { 
            for (int j = i * i; j < MX; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

// 2. 光速分解函数
// 时间复杂度：O(log X)
vector<int> get_prime_factors(int x) {
    vector<int> factors;
    while (x > 1) {
        int p = spf[x];     
        factors.push_back(p); 
        
        // 如果需要去重，继续除以 p 直到不能被 p 整除：
        // while (x % p == 0) x /= p; 
        
        // 如果不需要去重，直接除一次即可：
        x /= p;
    }
    return factors;
}

int main() {
    // 记得在所有测试用例开始前调用一次
    init_spf();
    
    // 假设查询 360 的质因数
    vector<int> res = get_prime_factors(360);
    
    cout << "360 的质因数分解为: ";
    for (int p : res) {
        cout << p << " ";
    }
    // 输出: 2 2 2 3 3 5
    
    return 0;
}
```

#### 数学 / 数论 / 线性基

**code.cpp**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

class LinearBasis {
public:
    static const int MAXL = 60; // 根据值域范围调整，long long 一般 60
    ll basis[MAXL + 1];
    bool zero; // 记录原集合是否能异或出 0 (即是否存在线性相关)

    LinearBasis() {
        fill(basis, basis + MAXL + 1, 0);
        zero = false;
    }

    // 插入一个数
    void insert(ll x) {
        for (int i = MAXL; i >= 0; --i) {
            if (!(x >> i & 1)) continue; // 如果第 i 位是 0，跳过
            
            if (!basis[i]) { // 如果该位还没有基底，直接占坑
                basis[i] = x;
                return;
            }
            x ^= basis[i]; // 有基底了，消元
        }
        // 如果 x 变成了 0，说明 x 可以被表示，存在线性相关
        zero = true; // 说明原集合中存在子集异或为 0
    }

    // 查询能异或出的最大值
    ll query_max() {
        ll ans = 0;
        for (int i = MAXL; i >= 0; --i) {
            // 贪心：如果异或后能变大，就异或
            if ((ans ^ basis[i]) > ans) {
                ans ^= basis[i];
            }
        }
        return ans;
    }
    
    // 查询能异或出的最小值 (不含 0)
    ll query_min() {
        for (int i = 0; i <= MAXL; ++i) {
            if (basis[i]) return basis[i];
        }
        return 0;
    }
};
```

#### 数学 / 概率论 / 期望

**几何分布.md**

```md
在算法竞赛（Competitive Programming）中，**几何分布（Geometric Distribution）** 是概率与期望类题目中**最基础、出现频率最高**的数学模型之一。

很多看起来复杂的期望问题或随机算法，本质上都是几何分布或其变形。下面为你从 **基本公式、四大核心应用场景、关键解题性质、C++代码技巧** 四个方面做系统总结。

---

### 一、 几何分布的核心公式（必背）

**定义**：在独立重复的伯努利试验中，设每次试验成功的概率为 $p$（$0 < p \le 1$），直到**第一次成功**为止所需要的**尝试次数** $X$ 服从几何分布。

| 概念 | 数学公式 | 竞赛中的通俗含义 |
| :--- | :--- | :--- |
| **概率质量函数 (PMF)** | $P(X = k) = (1-p)^{k-1} \cdot p$ | 恰好在第 $k$ 次时取得第一次成功的概率 |
| **期望（平均次数）** | $\mathbb{E}[X] = \frac{1}{p}$ | **全场最重要公式**：成功一次平均需要尝试 $\frac{1}{p}$ 次 |
| **失败次数的期望** | $\mathbb{E}[\text{失败}] = \frac{1-p}{p}$ | 第一次成功之前，平均会失败多少次 |
| **尾概率 (CDF 补集)** | $P(X > k) = (1-p)^k$ | 尝试了 $k$ 次仍然**一次都没有成功**的概率 |

---

### 二、 几何分布在竞赛中的四大核心应用场景

#### 场景 1：赠券收集模型 (Coupon Collector's Problem)
* **模型特征**：为了收集全 $N$ 种不同的物品，每次随机获得一种（概率相等），求收集全所有物品所需的**期望购买次数**。
* **解题方法**：
  将整个过程拆分为 $N$ 个阶段。当已经拥有 $k$ 种物品时，下一次拿到**全新物品**的概率为 $p_k = \frac{N-k}{N}$。
  每个阶段都服从几何分布，因此该阶段期望需要买 $\frac{1}{p_k} = \frac{N}{N-k}$ 瓶。
* **总期望公式**：
  $$E = \sum_{k=0}^{N-1} \frac{N}{N-k} = N \sum_{i=1}^N \frac{1}{i} \approx N \ln N$$
* **经典例题**：
  * 洛谷 P1291 [SHOI2002] 百事世界杯之旅
  * AtCoder / Codeforces 各种“凑齐所有状态”的随机游走题。

---

#### 场景 2：带“自环/失败重试”的期望 DP 化简
* **模型特征**：在期望 DP 中，在状态 $u$ 有 $p$ 的概率转移到下一个目标状态 $v$，有 $1-p$ 的概率**留在原地（或失败重来）**。
* **转移方程原型**：
  $$dp[u] = p \cdot (dp[v] + 1) + (1-p) \cdot (dp[u] + 1)$$
* **利用几何分布秒杀化简**：
  通过移项可以化简为：
  $$dp[u] = dp[v] + \frac{1}{p}$$
* **直观理解**：从 $u$ 成功走到 $v$ 平均需要尝试 $\frac{1}{p}$ 次，每次耗时 1，所以额外花费的期望时间就是 $\frac{1}{p}$。

---

#### 场景 3：随机化算法的时间复杂度证明（Las Vegas 算法）
* **模型特征**：在设计随机化算法（如 QuickSelect、随机跳表 SkipList、Treap、随机抽样）时，分析其时间复杂度。
* **常见分析**：
  * 在快速选择（QuickSelect）算法中，随机选中的主元（Pivot）能将数组划分得比较均匀（例如切掉至少 1/4）的概率是 $p = \frac{1}{2}$。
  * 根据几何分布，**平均只需要随机选 $\frac{1}{1/2} = 2$ 次**，就能选到一个优秀的主元。
  * 这证明了随机化算法的**期望时间复杂度为 $O(N)$**。

---

#### 场景 4：尾概率截断与循环次数确定（High Probability 技巧）
* **模型特征**：在算法中需要做随机尝试，但不确定最多需要尝试多少次才可以停止。
* **极值截断原理**：
  尝试 $k$ 次依然失败的概率是 $P(X > k) = (1-p)^k$。
  如果成功概率 $p = 0.5$：
  尝试 60 次依然失败的概率是 $(0.5)^{60} \approx 8.6 \times 10^{-19}$，这在计算机中几乎是**绝对不可能发生的死事件**。
* **竞赛实战技巧**：
  在随机化搜索、爬山算法或验证算法中，不需要写死循环 `while(true)`，直接写 `for (int i = 0; i < 60; ++i)` 尝试 60 次即可。如果 60 次都没成功，可以安全判定为无解。

---

### 三、 几何分布的核心性质：无记忆性 (Memoryless Property)

这是几何分布在 DP 中最强大的性质：
$$P(X > n + m \mid X > n) = P(X > m)$$

* **直观含义**：
  假设你掷骰子求点数 6，你已经连续掷了 100 次都不是 6（连续失败 100 次），**第 101 次掷出 6 的概率依然是 $\frac{1}{6}$**。前面的失败不会累积“运气”。
* **在 DP 状态设计中的作用**：
  我们在设计 DP 状态时，**完全不需要记录“之前已经失败了多少次”**！
  无论前面失败了多少次，从当前节点出发到成功的未来期望，永远是常数 $\frac{1}{p}$。这极大简化了 DP 的状态维度。

---

### 四、 C++ 竞赛实战代码与模板

#### 1. 模意义下的几何分布期望计算（$p/q \bmod 998244353$）
当题目要求对 $998244353$ 取模输出期望时，$\frac{1}{p}$ 就是求 $p$ 的模逆元：

```cpp
#include <iostream>

using namespace std;

const int MOD = 998244353;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// 几何分布期望 E = 1/p (即 p 的模逆元)
long long getExpectedTrials(long long p_numerator, long long p_denominator) {
    // p = p_numerator / p_denominator
    // E = 1/p = p_denominator / p_numerator
    return (p_denominator % MOD) * power(p_numerator, MOD - 2) % MOD;
}
```

#### 2. C++ 标准库中的几何分布生成器（用于随机化采样/本地对拍）
如果需要写随机化算法或本地生成对拍数据，C++ `<random>` 库内置了几何分布：

```cpp
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    double p = 0.2; // 每次成功的概率为 20%
    geometric_distribution<int> geo(p); 
    // 注意：std::geometric_distribution 产生的是【失败次数】Y = X - 1

    for (int i = 0; i < 5; ++i) {
        int failures = geo(rng);
        int trials = failures + 1; // 尝试次数 = 失败次数 + 1
        cout << "第 " << trials << " 次尝试成功（前面失败了 " << failures << " 次）\n";
    }
    return 0;
}
```

---

### 五、 总结卡片

```text
               几何分布 (Geometric Distribution)
                         │
        ┌────────────────┼────────────────┐
        ▼                ▼                ▼
   基本期望公式       无记忆性          尾概率截断
    E = 1 / p     DP状态无需记录失败数   (1-p)^k ≈ 0 (尝试60次)
        │                │                │
   ┌────┴────┐           │           ┌────┴────┐
   ▼         ▼           ▼           ▼         ▼
赠券收集   期望DP化简   状态压缩     随机算法   对拍/暴力
问题模型   (自环消除)   消去冗余维度 复杂度证明 搜索剪枝
```
```

**理论.md**

```md

---

### 一、 期望最核心的“两条铁律”

1. **期望的本质就是“加权平均值”**：
   $$\text{期望} = \sum (\text{某种结果的数值} \times \text{发生这种结果的概率})$$

2. **期望的拆分（全场最重要：期望的线性性质）**：
   $$\mathbb{E}[A + B] = \mathbb{E}[A] + \mathbb{E}[B]$$
   * **白话理解**：要求一堆东西“总和的期望”，**只需要分别算出每一个东西的期望，然后直接相加！**
   * **最厉害的地方**：哪怕 $A$ 和 $B$ 之间互相影响（不独立），这个拆分公式也**依然成立**！

---

### 二、 知识点

结合刚才那道题（$n$ 个要地，$m$ 次突袭，每次随机选一个要地让 $a_i \leftarrow \lfloor a_i/2 \rfloor$）：

#### 知识点 1：把“总和的期望”拆成“单点的期望”（期望的拆分）
* **题目要**：求所有要地防御力**总和**的期望 $\mathbb{E}\left[\sum a_i\right]$。
* **我们做**：根本不需要考虑这 $n$ 个要地之间怎么互相影响，直接拆成单独求每一个要地 $a_i$ 的期望，最后加起来：
  $$\mathbb{E}[\text{总和}] = \mathbb{E}[a_1] + \mathbb{E}[a_2] + \dots + \mathbb{E}[a_n]$$

#### 知识点 2：计算单点被选中 $k$ 次的概率（二项分布）
* 每次突袭，选中当前要地的概率是 $\frac{1}{n}$，选不中的概率是 $1 - \frac{1}{n}$。
* 突袭 $m$ 次，当前要地**恰好被选中 $k$ 次**的概率 $P(k)$ 为：
  $$P(k) = \binom{m}{k} \times \left(\frac{1}{n}\right)^k \times \left(1 - \frac{1}{n}\right)^{m-k}$$

#### 知识点 3：单点期望的计算
* 如果一个要地被选中了 $k$ 次，它的防御力会变成 $\lfloor \frac{a_i}{2^k} \rfloor$。
* 根据“期望 = 数值 $\times$ 概率”，单点的期望就是：
  $$\mathbb{E}[a_i] = \sum_{k} \left( \lfloor \frac{a_i}{2^k} \rfloor \times P(k) \right)$$

#### 知识点 4：根据数据范围剪枝（缩小枚举）
* 因为初始防御力 $a_i \le 10^9 < 2^{30}$，除以 2 做 30 次向下取整后，防御力**必定变成 0**。
* 所以上面的 $k$ 根本不需要从 $0$ 枚举到 $m$，**最多只需要枚举到 30**（$k \le 30$），大幅降低了计算量。

---

### 💡 一句话总结这道题的解法：

> **“用二项分布算出某个位置被选中 $k$ 次的概率 $P(k)$，算出一个位置做 $k$ 次除法后的平均防御力，最后把所有位置的平均防御力加起来。”**
```

#### 数学 / 线性代数 / 快速幂

**快速幂.md**

```md
```cpp
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
long long fast_pow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res % MOD;
}

// 求 a 的模逆元，即 a^-1 mod MOD
long long mod_inverse(long long a) {
    return fast_pow(a, MOD - 2);
}
// 直接使用 mod_inverse 来计算 a/b mod MOD, 保证结果非负
long long mod_divide(long long a, long long b) {
    return ((a * fast_pow(b, MOD - 2)) % MOD + MOD) % MOD;
}
```

## 费马小定理：如果 $p$ 是素数，且 $a$ 不是 $p$ 的倍数，那么
$$ a^{p-1} \equiv 1 \mod p $$

求 $a^{b^c} \mod p$，可以先计算 $b^c \mod (p-1)$，再计算 $a^{(b^c \mod (p-1))} \mod p$。
```cpp
long long fp(long long base, long long exp, long long MOD) {
    long long res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res % MOD;
}
long long mod_pow(long long a, long long b, long long c) {
    long long exponent = fp(b, c, MOD - 1); // 计算 b^c mod (p-1)
    return fp(a, exponent, MOD); // 计算 a^(b^c) mod p
}

//一般的：
// 先计算指数，注意用 MOD - 1 (费马小定理)，并严格防止负数！
long long exp1 = (n * m - n - m + 1 - k); // 计算指数，一个很大的数
exp1 = (exp1 % (MOD - 1) + (MOD - 1)) % (MOD - 1); // 确保指数非负
long long result = fp(2, exp1, MOD); // 计算 2^exp1 mod MOD
```

```

**矩阵快速幂.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1'000'000'007;

using matrix = vector<vector<long long>>;

// 返回矩阵 a 和矩阵 b 相乘的结果
matrix mul(matrix& a, matrix& b) {
    int n = a.size(), m = b[0].size();
    matrix c = matrix(n, vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < a[i].size(); k++) {
            if (a[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < m; j++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

// a^n * f1
matrix pow_mul(matrix a, int n, matrix& f1) {
    matrix res = f1;
    while (n) {
        if (n & 1) {
            res = mul(a, res);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}
```

##### 数学 / 组合数学 / 位运算 / 试填法

**code.cpp**

```cpp
// 力扣 3518. 字典序最小的回文串
#include <bits/stdc++.h>
#include <ranges>
using namespace std;

class Solution {
public:
    string smallestPalindrome(string s, int k) {
        int n = s.size();
        int m = n / 2;

        int cnt[26]{};
        for (int i = 0; i < m; i++) {
            cnt[s[i] - 'a']++;
        }

        // 为什么这样做是对的？见 62. 不同路径 我的题解
        auto comb = [&](int n, int m) -> int {
            m = min(m, n - m);
            long long res = 1;
            for (int i = 1; i <= m; i++) {
                res = res * (n + 1 - i) / i;
                if (res >= k) { // 太大了
                    return k;
                }
            }
            return res;
        };

        // 计算长度为 sz 的字符串的排列个数
        auto perm = [&](int sz) -> int {
            long long res = 1;
            for (int c : cnt) {
                if (c == 0) {
                    continue;
                }
                // 先从 sz 个里面选 c 个位置填当前字母
                res *= comb(sz, c);
                if (res >= k) { // 太大了
                    return k;
                }
                // 从剩余位置中选位置填下一个字母
                sz -= c;
            }
            return res;
        };

        // k 太大
        if (perm(m) < k) {
            return "";
        }

        // 构造回文串的左半部分
        string left_s(m, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 26; j++) {
                if (cnt[j] == 0) {
                    continue;
                }
                cnt[j]--; // 假设填字母 j，看是否有足够的排列
                int p = perm(m - i - 1); // 剩余位置的排列个数
                if (p >= k) { // 有足够的排列
                    left_s[i] = 'a' + j;
                    break;
                }
                k -= p; // k 太大，要填更大的字母（类似搜索树剪掉了一个大小为 p 的子树）
                cnt[j]++;
            }
        }

        string ans = left_s;
        if (n % 2) {
            ans += s[n / 2];
        }
        // ranges::reverse(left_s);
        reverse(left_s.begin(), left_s.end());
        return ans + left_s;
    }
};
```

**试填法.md**

```md
##  算法实战：字典序第 K 小排列

### 题目应用：[LeetCode 3518. 最小回文排列 II](https://leetcode.cn/problems/smallest-palindromic-rearrangement-ii/description/?envType=daily-question&envId=2026-07-29)

* **题意**：给定回文串 $s$ 和整数 $k$，求 $s$ 按字典序排列的第 $k$ 小回文排列。

### 解题三步法：

1. **折半降维（回文对称性）**：
   * 回文串的前半部分（左半部分）完全决定了后半部分。
   * **化简**：只需求左半部分字符构成的**第 $k$ 小字典序排列**。

2. **逐位确定（试填法 / Digit-by-digit Construction）**：
   * 从左到右依次确定每个位置的字符：
     * 从小到大尝试字符 $c \in ['a', 'z']$。
     * 假设当前位置填 $c$，用乘法原理算出后续剩余字符能构成的**排列总数 $cnt$**。
     * **判断分支**：
       * 若 $k \le cnt$：说明答案就在以 $c$ 开头的分支里！确定选 $c$，进入下一位。
       * 若 $k > cnt$：说明当前分支方案数不够，跳过这 $cnt$ 种情况（$k \leftarrow k - cnt$），尝试下一个字符 $c+1$。

3. **上限裁剪（Cap 技巧防溢出）**：
   * 由于 $k \le 10^6$，若计算出的 $cnt > k$，我们不需要知道准确大数，**直接截断为 $limit = k + 1$**。
   * 这一技巧使得算法可以轻松应对长度高达 $N = 10^4$ 的字符串。

```

#### 数学 / 组合数学 / 排列

**code.cpp**

```cpp
#include <bits/stdc++.h>

using namespace std;

long long C(int n, int m) {
    if (m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1;
    if (m > n - m) m = n - m; // 利用 C(n, m) = C(n, n-m)
    long long res = 1;
    for (int i = 1; i <= m; ++i) {
        // 关键点 1：边乘边除，防止 res 增长过快导致溢出
        // 关键点 2：(n - m + i) 的连续乘积保证每次都能被 i 整除，绝不丢精度
        res = res * (n + 1 - i) / i;
        // 关键点 3：若 res 超过 k，直接截断，避免大数计算。k为题目限制的上限
        //if (res >= k) return k;
    }
    return res;
}

long long permuteCount(const vector<int>& freq, int k) {
    int n = accumulate(freq.begin(), freq.end(), 0);
    long long res = 1;
    for (int i = 0; i < freq.size(); ++i) {
        if (freq[i] == 0) continue;
        // 计算当前字符的组合数 C(n, freq[i])
        res *= C(n, freq[i]);
        n -= freq[i];
    }
    return res;
}
```

**有重复元素排列.md**

```md

---

# 📝 学习笔记：多重集排列、乘法原理与试填法

---

## 一、 理论基础：带重复元素的全排列 (Multiset Permutation)

对一个长度为 $n$，且包含重复字符的字符串（如 `"banana"`），求其**所有不重复的排列总数**。

### 1. 两种视角与公式

#### 视角 1：阶乘去除法（消重视角）
假设字符串中 $k$ 种不同字符出现的频数分别为 $c_1, c_2, \dots, c_k$，且 $\sum c_i = n$：
$$P = \frac{n!}{c_1! \times c_2! \times \dots \times c_k!}$$
* **含义**：如果不考虑重复，总排列为 $n!$。但每种字符内部交换位置不产生新字符串，因此需除以各自的全排列阶乘 $c_i!$。

#### 视角 2：组合数相乘法（填位视角）
准备 $n$ 个空白位置，依次为每种字符挑选放置位置：
$$P = C_n^{c_1} \times C_{n - c_1}^{c_2} \times C_{n - c_1 - c_2}^{c_3} \times \dots \times C_{c_k}^{c_k}$$
* **含义**：先从 $n$ 个位置中选 $c_1$ 个放第一种字符，再从剩下的 $n - c_1$ 个位置中选 $c_2$ 个放第二种字符……依此类推。

### 2. 两种视角的等价性证明
利用组合数展开公式 $C_n^k = \frac{n!}{k!(n-k)!}$ 进行展开：
$$P = \left( \frac{n!}{c_1!(n - c_1)!} \right) \times \left( \frac{(n - c_1)!}{c_2!(n - c_1 - c_2)!} \right) \times \dots$$
**对角线约分**后，只剩下分子 $n!$ 与分母各频数阶乘的乘积，证明两者完全等价。

---

## 二、 核心思想：乘法原理 vs 加法原理

| 原理 | 核心口诀 | 关键特征 | 适用场景 |
| :--- | :--- | :--- | :--- |
| **乘法原理** | **分步**用乘法 | 步骤间**连环相扣**，做完一步还没完，必须做完所有步骤才算完成。 | 组合数填位、多阶段决策树。 |
| **加法原理** | **分类**用加法 | 类别间**独立平行**，完成任意一类就已经独立完成了这件事。 | 按首字母分类计数、多路径求和。 |

---

## 三、 工程实现：组合数计算与防溢出技巧

在 C++ 中计算组合数 $C(n, k)$ 时，为了兼顾**精度**与**不溢出**，采用**边乘边除**的递推策略：

```cpp
long long C(int n, int m) {
    if (m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1;
    if (m > n - m) m = n - m; // 利用 C(n, m) = C(n, n-m)

    long long res = 1;
    for (int i = 1; i <= m; ++i) {
        // 关键点 1：边乘边除，防止 res 增长过快导致溢出
        // 关键点 2：(n - m + i) 的连续乘积保证每次都能被 i 整除，绝不丢精度
        res = res * (n + 1 - i) / i;
        // 关键点 3：若 res 超过 k，直接截断，避免大数计算。k为题目限制的上限
        //if (res >= k) return k;
        
    }
    return res;
}

long long permuteCount(const vector<int>& freq, int k) {
    int n = accumulate(freq.begin(), freq.end(), 0);
    long long res = 1;
    for (int i = 0; i < freq.size(); ++i) {
        if (freq[i] == 0) continue;
        // 计算当前字符的组合数 C(n, freq[i])
        res *= C(n, freq[i]);
        n -= freq[i];
    }
    return res;
}
```

### 为什么 `res * (n - k + i) / i` 必定能整除？
1. **数学定理**：任意 $i$ 个连续自然数的乘积，必能被 $i!$ 整除。
2. **物理含义**：循环执行到第 $i$ 步时，`res` 计算的本质是组合数 $C(n - k + i, i)$。组合数代表实际方案数，**必须是整数**。

---



```

#### 数学 / 组合数学 / 组合数

**逆元组合数.cpp**

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;//1e9 + 7; // 或者是 998244353
const int MAXN = 2e5 + 5; // 根据题目 n 的范围调整

long long fact[MAXN];     // 阶乘数组: fact[i] = i! % MOD
long long invFact[MAXN];  // 阶乘逆元数组: invFact[i] = (i!)^(-1) % MOD

// 1. 快速幂模板：求 a^b % MOD
long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long getInv(long long a) {
    return qpow(a, MOD - 2);
}

void init() {
    fact[0] = 1;
    invFact[0] = 1;
    
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    
    invFact[MAXN - 1] = getInv(fact[MAXN - 1]);
    
    // 解释：1/(i-1)! = (1/i!) * i
    for (int i = MAXN - 2; i >= 1; --i) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    // intt[i] = (mod - mod / i) * intt[mod % i] % mod; intt[i] 是 i 的逆元
}

long long C(int n, int m) {
    if (m < 0 || m > n || n < 0) return 0;
    
    long long res = fact[n];
    res = res * invFact[m] % MOD;
    res = res * invFact[n - m] % MOD;
    
    return res;
}

// 专门对付 n 极大、m 较小的组合数
long long nCr(long long n, long long m) {
    if (m < 0 || n < m) return 0;
    if (m == 0) return 1;
    
    long long num = 1;
    // 分子部分暴力连乘 m 次：n * (n-1) * ... * (n-m+1)
    for (int i = 0; i < m; ++i) {
        num = num * ((n - i) % MOD) % MOD; 
    }
    // 分母部分依然可以使用你的 invFact，因为 m 最大才 10^6
    return num * invFact[m] % MOD;
}

long long A(int n, int m) {
    if (m < 0 || m > n || n < 0) return 0;
    return fact[n] * invFact[n - m] % MOD;
}

```

### 数据结构 / 主席树

**PersistentTree.cpp**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ====================================================================
// 工具类：泛型离散化器 (Discretizer)
// 作用：将任何大范围的值映射到 1 ~ N 的紧凑区间，处理主席树值域过大的必备工具
// ====================================================================
template <typename T> struct Discretizer {
    vector<T> vals;

    // 新增：预分配内存空间，避免 vector 动态扩容带来的性能损耗
    Discretizer(size_t n = 0) {
        if (n > 0)
            vals.reserve(n);
    }

    void add(T x) { vals.push_back(x); }
    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }
    int get_id(T x) const {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    }
    T get_val(int id) const { return vals[id - 1]; }
    int size() const { return vals.size(); }
};
// ====================================================================
// 核心数据结构：主席树 / 可持久化权值线段树 (Persistent Segment Tree)
// 作用：极其稳定、安全的版本控制线段树
// ====================================================================
struct PersistentTree {
    struct Node {
        int l, r; // 左右子节点的索引 (在 tr 数组中的下标)
        int cnt;  // 维护的区间信息：这里是区间内元素的个数
    };

    vector<Node> tr;  // 动态节点池，彻底告别全局大数组
    vector<int> root; // 存储每个版本的根节点索引

    // 构造函数预分配空间，提升性能
    // max_nodes: 预估的最大节点数，一般为 N * 40
    // max_versions: 预估的最大版本数，一般等于操作次数 N
    PersistentTree(int max_nodes = 0, int max_versions = 0) {
        if (max_nodes > 0)
            tr.reserve(max_nodes);
        if (max_versions > 0)
            root.reserve(max_versions + 1);

        // 塞入 0 号节点作为“空节点哨兵”，非常优雅地处理边界情况
        tr.push_back({0, 0, 0});
        root.push_back(0);
    }

    // 核心：复制一个节点并返回新节点的索引
    int clone(int p) {
        tr.push_back(tr[p]);
        return tr.size() - 1;
    }

    // 建空树 (值域 [l, r])
    // 很多时候权值线段树可以省略建空树，这里为了模板的完备性保留
    int build(int l, int r) {
        int p = tr.size();
        tr.push_back({0, 0, 0});
        if (l == r)
            return p;

        int mid = l + (r - l) / 2;
        tr[p].l = build(l, mid);
        tr[p].r = build(mid + 1, r);
        return p;
    }

    // 核心操作：在前一个版本 pre_root 的基础上，在值域 [l, r]
    // 中插入离散化后的值 val_id 返回新版本的根节点
    int insert(int pre, int l, int r, int val_id) {
        int p = clone(pre); // 沿途复制节点，这就是主席树的灵魂
        tr[p].cnt++;        // 当前路径上节点所管辖的区间元素数 + 1

        if (l == r)
            return p; // 抵达叶子节点

        int mid = l + (r - l) / 2;
        if (val_id <= mid) {
            tr[p].l = insert(tr[pre].l, l, mid, val_id);
        } else {
            tr[p].r = insert(tr[pre].r, mid + 1, r, val_id);
        }
        return p;
    }

    // 外部调用插入接口，自动记录新版本 root
    void add_version(int val_id, int val_domain_size) {
        int new_root = insert(root.back(), 1, val_domain_size, val_id);
        root.push_back(new_root);
    }

    // 核心查询：在版本 u (左端点 L-1) 和版本 v (右端点 R) 之间，查询 [l, r]
    // 值域内的第 k 小
    int query_kth(int u, int v, int l, int r, int k) const {
        if (l == r)
            return l; // 找到了！返回具体的离散化 ID

        // 通过两个版本的节点计数相减，得到查询区间内的实际情况 (前缀和思想)
        int left_cnt = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        int mid = l + (r - l) / 2;

        if (left_cnt >= k) {
            // 第 k 小在左边
            return query_kth(tr[u].l, tr[v].l, l, mid, k);
        } else {
            // 第 k 小在右边，需要扣除左边的元素数量
            return query_kth(tr[u].r, tr[v].r, mid + 1, r, k - left_cnt);
        }
    }
};

// ====================================================================
// 测试及使用示例：如何用这个模板解决上面的题目 (静态区间中位数)
// ====================================================================
int main() {
    // 提速必备
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q))
        return 0;

    vector<int> a(n + 1);
    Discretizer<int> d(n); // 实例化我们的离散化工具

    // 1. 读取数据并收集到离散化器中
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        d.add(a[i]);
    }

    // 2. 执行离散化
    d.build();
    int m = d.size(); // 得到值域的范围 1 ~ m

    // 3. 实例化主席树 (预分配内存: max_nodes 预估 N*40，max_versions 预估 N)
    PersistentTree pt(n * 40, n);

    // 初始化版本 0 为一棵值域为 1~m 的空树 (权值线段树可以省略这一步)
    pt.root[0] = pt.build(1, m);

    // 4. 构建所有历史版本
    for (int i = 1; i <= n; i++) {
        int id = d.get_id(a[i]);
        // pt.add_version() 会自动在前一个版本基础上插入，并保存新版本
        pt.add_version(id, m);
    }

    // 5. 应对查询
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;

        int len = r - l + 1;
        int k = (len + 1) / 2; // 中位数就是第 (len+1)/2 小

        // 核心查询逻辑：拿出第 R 个版本，减去第 L-1 个版本，找第 k 小
        int ans_id = pt.query_kth(pt.root[l - 1], pt.root[r], 1, m, k);

        // 查出来的是 ID，别忘了用工具类换回真实值
        cout << d.get_val(ans_id) << "\n";
    }

    return 0;
}

```

**sum.cpp**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ====================================================================
// 工具类：泛型离散化器 (Discretizer)
// ====================================================================
template<typename T>
struct Discretizer {
    vector<T> vals;

    void add(T x) { vals.push_back(x); }
    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }
    int get_id(T x) const { return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1; }
    T get_val(int id) const { return vals[id - 1]; }
    int size() const { return vals.size(); }
};

// ====================================================================
// 核心数据结构：主席树 / 可持久化权值线段树
// ====================================================================
struct PersistentTree {
    struct Node {
        int l, r;       // 左右子节点的索引
        int cnt;        // 区间内元素的个数
        long long sum;  // 新增：区间内元素的真实值总和 (注意用 long long)
    };

    vector<Node> tr;    
    vector<int> root;   

    PersistentTree(int max_nodes = 0, int max_versions = 0) {
        if (max_nodes > 0) tr.reserve(max_nodes);
        if (max_versions > 0) root.reserve(max_versions + 1);
        
        // 0号哨兵节点，sum 也要初始化为 0
        tr.push_back({0, 0, 0, 0LL});
        root.push_back(0); 
    }

    int clone(int p) {
        tr.push_back(tr[p]); // 这一步会自动把旧节点的 cnt 和 sum 都复制过来
        return tr.size() - 1; 
    }

    int build(int l, int r) {
        int p = tr.size();
        tr.push_back({0, 0, 0, 0LL});
        if (l == r) return p;
        
        int mid = l + (r - l) / 2;
        tr[p].l = build(l, mid);
        tr[p].r = build(mid + 1, r);
        return p;
    }

    // 新增：多传了一个 real_val 用于累加 sum
    int insert(int pre, int l, int r, int val_id, long long real_val) {
        int p = clone(pre); 
        tr[p].cnt++;               // 个数 + 1
        tr[p].sum += real_val;     // 新增：累加真实值

        if (l == r) return p; 

        int mid = l + (r - l) / 2;
        if (val_id <= mid) {
            tr[p].l = insert(tr[pre].l, l, mid, val_id, real_val);
        } else {
            tr[p].r = insert(tr[pre].r, mid + 1, r, val_id, real_val);
        }
        // 如果不是权值线段树，而是普通线段树，这里通常会写 push_up:
        // tr[p].sum = tr[tr[p].l].sum + tr[tr[p].r].sum;
        // 但在单点修改的权值线段树中，直接累加更高效。
        return p;
    }

    // 外部接口同步修改，接收真实值
    void add_version(int val_id, int val_domain_size, long long real_val) {
        int new_root = insert(root.back(), 1, val_domain_size, val_id, real_val);
        root.push_back(new_root);
    }

    // 经典查询 1：求第 k 小
    int query_kth(int u, int v, int l, int r, int k) const {
        if (l == r) return l; 

        int left_cnt = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        int mid = l + (r - l) / 2;

        if (left_cnt >= k) {
            return query_kth(tr[u].l, tr[v].l, l, mid, k);
        } else {
            return query_kth(tr[u].r, tr[v].r, mid + 1, r, k - left_cnt);
        }
    }

    // 扩展查询 2：求区间内前 k 小的元素的总和 (利用新增的 sum 变量)
    long long query_sum_kth(int u, int v, int l, int r, int k) const {
        if (l == r) {
            // 到达叶子节点，叶子节点可能包含多个相同的值，按比例取 sum
            // 或者直接用: k * 叶子节点代表的真实值 (这里假设离散化还原能在外部做，但为了模板自洽我们提供思路)
            // 这里为了严谨，我们用 cnt 计算单价，再乘以 k
            int count = tr[v].cnt - tr[u].cnt;
            long long total_sum = tr[v].sum - tr[u].sum;
            if (count == 0) return 0;
            return total_sum / count * k; 
        }

        int left_cnt = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        long long left_sum = tr[tr[v].l].sum - tr[tr[u].l].sum; // 左子树的真实值总和
        int mid = l + (r - l) / 2;

        if (left_cnt >= k) {
            // 前 k 小全部在左子树，只递归左边
            return query_sum_kth(tr[u].l, tr[v].l, l, mid, k);
        } else {
            // 左子树全部包括，并加上右子树中的前 (k - left_cnt) 小
            return left_sum + query_sum_kth(tr[u].r, tr[v].r, mid + 1, r, k - left_cnt);
        }
    }
};

// ====================================================================
// 测试示例
// ====================================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    Discretizer<int> d; 

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        d.add(a[i]);
    }

    d.build();
    int m = d.size(); 

    PersistentTree pt(n * 40, n);
    pt.root[0] = pt.build(1, m);

    for (int i = 1; i <= n; i++) {
        int id = d.get_id(a[i]);
        // 注意这里：除了传入 id，还把真实的 a[i] 传了进去，用于累加 sum
        pt.add_version(id, m, a[i]);
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        
        int len = r - l + 1;
        int k = (len + 1) / 2; 

        int ans_id = pt.query_kth(pt.root[l - 1], pt.root[r], 1, m, k);
        cout << "中位数为: " << d.get_val(ans_id) << "\n";

        // 你现在也可以调用新增的查询接口了！
        // cout << "区间前 " << k << " 小的数字之和为: " << pt.query_sum_kth(pt.root[l - 1], pt.root[r], 1, m, k) << "\n";
    }

    return 0;
}
```

### 数据结构 / 字典树

**01Trie.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;

// 01-Trie 异或最大值模板
const int MAX_NODE = 100005 * 32; // 每个数字最多32位
int ch[MAX_NODE][2];              // 只有0和1两个分叉
int idx = 0;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int u = (x >> i) & 1; 
        if (!ch[p][u]) ch[p][u] = ++idx;
        p = ch[p][u];
    }
}

// 查询数组中谁和 x 异或结果最大，返回那个最大的异或值
int query_max_xor(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int u = (x >> i) & 1;
        int opposite = u ^ 1; 
        
        if (ch[p][opposite]) {
            res |= (1 << i);
            p = ch[p][opposite];
        } else {
            p = ch[p][u];
        }
    }
    return res;
}
```

**Trie.cpp**

```cpp
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
```

### 数据结构 / 对顶堆

**code.cpp**

```cpp
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// 模板：带懒删除的对顶堆 (用于动态维护中位数)
struct DualHeap {
private:
    priority_queue<long long> left; // 大根堆，存较小的一半
    priority_queue<long long, vector<long long>, greater<long long>> right; // 小根堆，存较大的一半
    unordered_map<long long, int> delayed; // 死亡笔记：记录被删除但还在堆里的“幽灵节点”
    
    // left_size 和 right_size 记录的是【抛去幽灵节点后】两个堆真实的有效逻辑大小
    int left_size = 0; 
    int right_size = 0;

    // 核心清道夫：只要堆顶是幽灵节点，就立刻弹出去
    void prune() {
        while (!left.empty() && delayed[left.top()] > 0) {
            delayed[left.top()]--;
            left.pop();
        }
        while (!right.empty() && delayed[right.top()] > 0) {
            delayed[right.top()]--;
            right.pop();
        }
    }

    // 维持平衡：严格保证 left_size == right_size 或 left_size == right_size + 1
    void balance() {
        if (left_size > right_size + 1) {
            right.push(left.top());
            left.pop();
            left_size--;
            right_size++;
            prune(); // 发生物理挪动后，新暴露出在堆顶的元素可能是幽灵，立刻查杀
        } else if (left_size < right_size) {
            left.push(right.top());
            right.pop();
            left_size++;
            right_size--;
            prune();
        }
    }

public:
    // API 1: 插入元素
    void insert(long long x) {
        if (left.empty() || x <= left.top()) {
            left.push(x);
            left_size++;
        } else {
            right.push(x);
            right_size++;
        }
        balance();
    }

    // API 2: 删除元素 (必须保证删除的元素 x 确实存在于当前集合中)
    void erase(long long x) {
        delayed[x]++; // 记上死亡笔记，等待未来其冒到堆顶时被 prune 清除
        if (!left.empty() && x <= left.top()) {
            left_size--;
            if (x == left.top()) prune(); // 如果它碰巧就在堆顶，顺手清理
        } else {
            right_size--;
            if (!right.empty() && x == right.top()) prune();
        }
        balance();
    }

    // API 3: 获取中位数
    double get_median() {
        prune(); // 双保险，取值前强制清理一次可能的幽灵
        if ((left_size + right_size) % 2 == 1) {
            return left.top();
        } else {
            return ((double)left.top() + right.top()) / 2.0;
        }
    }
    
    // API 4: 获取当前有效元素的总个数 (可选)
    int size() {
        return left_size + right_size;
    }
};
```

### 数据结构 / 并查集

**DSU.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> sz; 

public:
    DSU(int n) {
        parent.resize(n + 1); // 下标从 1 开始
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); 
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (sz[rootX] < sz[rootY]) {
                parent[rootX] = rootY;
                sz[rootY] += sz[rootX];
            } else {
                parent[rootY] = rootX;
                sz[rootX] += sz[rootY];
            }
        }
    }
    
    int getSize(int x) {
        return sz[find(x)];
    }
};


```

**带权并查集.cpp**

```cpp
#include <vector>
using namespace std;
template <typename T> class UnionFind {
private:
    vector<int> fa;
    vector<T> dis;  // dis[i] 表示 i 到其父节点的边权值

public:
    int cc;
    UnionFind(int n) : fa(n), dis(n) {
        // ranges::iota(fa, 0); // iota(fa.begin(), fa.end(), 0);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            dis[i] = 0;
        }
        cc = n;
    }

    int find(int x) {
        if (fa[x] != x) {
            int root = find(fa[x]);
            dis[x] ^= dis[fa[x]];
            fa[x] = root;
        }
        return fa[x];
    }

    bool merge(int from, int to, T value) {
        int x = find(from), y = find(to);
        if (x == y) {
            return (dis[from] ^ dis[to]) == value;
        }
        dis[x] = value ^ dis[to] ^ dis[from];
        fa[x] = y;
        cc--;
        return true;
    }

    bool is_same(int x, int y) { return find(x) == find(y); }
};
```

### 数据结构 / 树状数组

**BIT.cpp**

```cpp
#include <vector>
using namespace std;
// 树状数组（Fenwick Tree）
class FenwickTree {
private:
    int n;
    vector<long long> tree;
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    int lowbit(int x) {
        return x & (-x);
    }
    void update(int idx, long long val) {
        while (idx <= n) {
            tree[idx] += val;
            idx += lowbit(idx); 
        }
    }

    long long q(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= lowbit(idx); 
        }
        return res;
    }

    long long query(int l, int r) {
        return q(r) - q(l - 1);
    }

};


```

### 数据结构 / 珂朵莉树

**ODT.cpp**

```cpp
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

struct Node {
    int l, r;
    mutable ll v;
    bool operator<(const Node& other) const {
        return l < other.l;
    }
};

set<Node> odt;

// 分裂操作
auto split(int pos) {
    auto it = odt.lower_bound({pos, 0, 0});
    if (it != odt.end() && it->l == pos) return it;
    --it;
    int l = it->l, r = it->r;
    ll v = it->v;
    odt.erase(it);
    odt.insert({l, pos - 1, v});
    return odt.insert({pos, r, v}).first;
}

// 推平操作 (区间赋值)
void assign(int l, int r, ll val) {
    auto itr = split(r + 1);
    auto itl = split(l);
    odt.erase(itl, itr);
    odt.insert({l, r, val});
}

// 其他操作示例：区间加
void add(int l, int r, ll val) {
    auto itr = split(r + 1);
    auto itl = split(l);
    for (auto it = itl; it != itr; ++it) {
        it->v += val;
    }
}

// 初始化 (非常重要！)
void init(int n) {
    odt.clear();
    // 初始时放入一个覆盖全范围的节点，值根据题目要求定 (比如 0)
    odt.insert({1, n, 0}); 
}

int main() {
    int n = 10;
    init(n);
    
    // 示例操作
    assign(1, 5, 1); // [1, 5] 变成 1
    add(3, 7, 2);    // [3, 7] 加 2
    
    // 此时结构：
    // [1, 2] = 1
    // [3, 5] = 1+2 = 3
    // [6, 7] = 0+2 = 2
    // [8, 10] = 0
    
    return 0;
}
```

### 数据结构 / 线段树

**区间乘法区间求和.cpp**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

class SegmentTree {
private:
    int n;
    vector<long long> tree; 
    vector<long long> lazy; 
    void push_up(int p) {
        tree[p] = (tree[p * 2] + tree[p * 2 + 1]) % MOD; 
    }
    void push_down(int p) {
        if (lazy[p] != 1) { 
            lazy[p * 2] = (lazy[p * 2] * lazy[p]) % MOD;
            lazy[p * 2 + 1] = (lazy[p * 2 + 1] * lazy[p]) % MOD;
            tree[p * 2] = (tree[p * 2] * lazy[p]) % MOD;
            tree[p * 2 + 1] = (tree[p * 2 + 1] * lazy[p]) % MOD;
            lazy[p] = 1;
        }
    }

    void update(int L, int R, long long val, int p, int l, int r) {
        if (L <= l && r <= R) { 
            tree[p] = (tree[p] * val) % MOD; 
            lazy[p] = (lazy[p] * val) % MOD; 
            return;
        }
        push_down(p);
        int mid = l + (r - l) / 2;
        if (L <= mid) update(L, R, val, p * 2, l, mid);
        if (R > mid) update(L, R, val, p * 2 + 1, mid + 1, r);
        push_up(p); 
    }
    long long query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) { 
            return tree[p];
        }
        push_down(p); 
        int mid = l + (r - l) / 2;
        long long res = 0;
        if (L <= mid) res = (res + query(L, R, p * 2, l, mid)) % MOD;
        if (R > mid) res = (res + query(L, R, p * 2 + 1, mid + 1, r)) % MOD;
        return res;
    }
    void build(vector<long long>& arr, int p, int l, int r) {
        if (l == r) {
            tree[p] = arr[l] % MOD;
            return;
        }
        int mid = l + (r - l) / 2;
        build(arr, p * 2, l, mid);
        build(arr, p * 2 + 1, mid + 1, r);
        push_up(p);
    }
public:
    SegmentTree(vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 1); 
        build(arr, 1, 0, n - 1);
    }
    void update(int L, int R, long long val) { // L, R 从 0 开始
        update(L, R, val, 1, 0, n - 1);
    }
    long long query(int L, int R) { // L, R 从 0 开始
        return query(L, R, 1, 0, n - 1);
    }
};

```

**懒更新区间和.cpp**

```cpp
#include <vector>
#include <iostream>
using namespace std;

class SegmentTree {
private:
    long long n;
    vector<long long> tree; 
    vector<long long> lazy; 

    
    void push_up(int p) {
        tree[p] = tree[p * 2] + tree[p * 2 + 1]; // 求和
        // 如果是求最大值: tree[p] = max(tree[p*2], tree[p*2+1]);
    }

    void push_down(int p, int l, int r) {
        if (lazy[p] != 0) {
            int mid = l + (r - l) / 2;
            
            tree[p * 2] += lazy[p] * (mid - l + 1); // 区间和要乘长度
            lazy[p * 2] += lazy[p];
            
            tree[p * 2 + 1] += lazy[p] * (r - mid);
            lazy[p * 2 + 1] += lazy[p];
            
            lazy[p] = 0;
        }
    }

    void build(const vector<long long>& a, int p, int l, int r) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, p * 2, l, mid);
        build(a, p * 2 + 1, mid + 1, r);
        push_up(p);
    }

    void update(int L, int R, long long v, int p, int l, int r) {
        if (L <= l && r <= R) {
            tree[p] += v * (r - l + 1); // 区间和更新
            lazy[p] += v;
            return;
        }
        push_down(p, l, r); // 访问子节点前必须下放标记
        int mid = l + (r - l) / 2;
        if (L <= mid) update(L, R, v, p * 2, l, mid);
        if (R > mid) update(L, R, v, p * 2 + 1, mid + 1, r);
        push_up(p);
    }

    long long query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) return tree[p];
        push_down(p, l, r); // 访问子节点前必须下放标记
        int mid = l + (r - l) / 2;
        long long res = 0;
        if (L <= mid) res += query(L, R, p * 2, l, mid);
        if (R > mid) res += query(L, R, p * 2 + 1, mid + 1, r);
        return res;
    }

public:
    SegmentTree(const vector<long long>& a) {
        n = a.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        // 注意：外部数组通常 0-indexed，线段树内部递归通常用 0~n-1 表示范围
        build(a, 1, 0, n - 1); 
    }

    // 接口：区间 [L, R] 加上 v
    void update(int L, int R, long long v) {
        update(L, R, v, 1, 0, n - 1);
    }

    // 接口：查询 [L, R] 的和
    long long query(int L, int R) {
        return query(L, R, 1, 0, n - 1);
    }
};
```

## 杂项

**数学公式.md**

```md
> 求一个数组中所有子序列的乘积，序列 $a_1, a_2, \ldots, a_n$ 的乘积为 $a_1 \cdot a_2 \cdots a_n$，空序列的乘积为 1。

所以数组`a`的所有子序列的乘积之和为：$$ans = \prod_{i=1}^{n} (a_i + 1) - 1$$
```

**矩阵降维.md**

```md
**二维降一维（行压缩/列压缩）** 这种思想在算法和数据结构中**非常有普遍性，也是解决二维区间/子矩阵问题的核心技巧之一。**

我们可以把这种思想看作是“降维打击”：将一个复杂的二维问题，通过枚举一个维度（通常是行或列的边界），将其压缩转化成我们熟悉且有高效解法的一维问题。

以下是这种思想的普遍性体现和常见的应用场景：

### 1. 核心应用场景与经典问题

#### **A. 最大子矩阵和问题**

这是最经典的降维应用。

* **一维版本：** “最大子数组和”（Kadane 算法，时间复杂度 $O(N)$）。
* **二维版本：** 给定一个包含正负数的二维矩阵，求元素总和最大的子矩阵。
* **降维思路：** 枚举子矩阵的上边界 `top` 和下边界 `bottom`。将 `top` 到 `bottom` 之间的每一列元素相加，得到一个一维数组 `col_sum`。然后对 `col_sum` 使用一维的 Kadane 算法。
* **时间复杂度降低：** 暴力枚举四个边界需要 $O(N^2M^2)$，使用二维前缀和需要 $O(N^2M^2)$，而降维打击将其优化到了 $O(N^2 \cdot M)$。

#### **B. 最大全 1 子矩阵 (或最大矩形面积)**

* **一维（变体）版本：** “直方图中最大的矩形”（单调栈，时间复杂度 $O(N)$）。
* **二维版本：** 给定一个只包含 0 和 1 的矩阵，求只包含 1 的最大矩形面积。
* **降维思路：** 以矩阵的每一行作为底边，将上方连续的 1 看作直方图的高度。这样就将每一行都转换成了一个“直方图最大矩形”的一维问题。
* **复杂度：** $O(NM)$。

#### **C. 满足特定条件的子矩阵寻找**

这就是你刚才做的那道题的类型。

* **一维版本：** 寻找和大于等于 $K$ 的最短/最长子数组（双指针/前缀和+单调队列，时间复杂度 $O(N)$ 或 $O(N \log N)$）。
* **二维版本：** 寻找元素和大于等于 $K$ 的面积最小/最大的子矩阵。
* **降维思路：** 同样是枚举上下边界压缩成一维，然后用一维的高效算法解决。

#### **D. 二维匹配/字符串查找问题**

* **二维 KMP / 二维哈希（Rabin-Karp）：** 在一个大矩阵中寻找一个小矩阵。
* **降维思路：** 可以将小矩阵和待匹配的大矩阵区域的列哈希值压缩成一维数组，然后在行方向上进行一维的字符串匹配算法。

### 2. 为什么这种思想很重要？

1. **复用一维的高效算法：** 我们在一维数组上积累了大量的高效算法工具（如滑动窗口、双指针、单调栈/队列、线段树、KMP 等）。降维使得我们可以直接套用这些“神兵利器”，而不需要去发明复杂的二维算法。
2. **降低复杂度级别：** 在二维网格中，如果枚举所有可能的子矩阵，通常需要 4 个嵌套循环 $O(N^2M^2)$。通过压缩一维（例如固定上下边界花费 $O(N^2)$），剩下一维的问题如果能用 $O(M)$ 或 $O(M \log M)$ 解决，总复杂度就会大幅下降至 $O(N^2M)$。
3. **空间优化：** 在某些情况下（如滚动数组），降维思想不仅降低了时间复杂度，还使得我们不需要存储完整的二维状态，从而极大优化空间复杂度。

### 3. 降维思想的本质与拓展

**本质：分离变量，局部固定。**
我们无法同时高效处理行和列的动态变化。因此，我们选择“固定”一个方向（例如，枚举出所有可能的高度区间），使得在这个固定的区间内，问题在另一个方向上（例如宽度）变成线性的。

**不仅仅是二维降一维，高维同样适用：**

* **三维降二维：** 例如求三维空间中的最大长方体和。可以枚举两层的高度，将其压缩成二维平面的最大子矩阵和问题，进一步再降为一维。
* **动态规划中的状态压缩（状压 DP）：** 也可以看作是一种“降维”。将一个集合的状态（原本需要多维数组表示）压缩成一个整数（一维），从而降低空间和时间常数。

### 总结

当你遇到“在二维矩阵中寻找满足条件的子矩形/区域”**且直接暴力求解复杂度过高（如 $O(N^4)$）时，**“枚举上下边界 + 列向压缩 -> 转化为一维问题” 应该是你脑海中弹出的第一个或者第二个通用解题模板。这种思想不仅有普遍性，而且是必须掌握的核心技巧。
```

**逆序对.md**

```md

---
# 逆序对的定义
>在一个数组中，如果存在两个下标 i 和 j，使得 i < j 且 arr[i] > arr[j]，则称 (i, j) 为一个逆序对。
## 结论
*相邻交换排序的最小次数 = 逆序对总数*
> 比如说，数组 [3, 1, 2] 中，逆序对有 (0, 1), (0, 2), (1, 2) 共 3 个，所以最少需要交换 3 次才能将数组排序。

---
```

**随机数生成.md**

```md
# 📝 算法笔记：利用随机哈希与线性DP解决“好数组”计数

#### A. 随机化哈希 (Randomized Hashing)

为了在 $O(1)$ 时间内检查区间 $[L, R]$ 内所有数是否都等于 $V$，我们使用随机哈希来避免普通求和的冲突。

  * **映射**：给每个数值 $x$ 分配一个 64 位的随机大整数 `val_hash[x]`。
  * **前缀和**：维护哈希值的前缀和 `pre[i]`。
  * **O(1) 校验**：
    $$pre[R] - pre[L-1] == val\_hash[V] \times (R - L + 1)$$
  * **数据类型**：使用 `unsigned long long` 利用自然溢出（自动取模 $2^{64}$），既省去了取模运算，又保证了正确性。

### 3\. 代码模板 (Code Snippet)

```cpp
// 1. 随机数生成器准备
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
unsigned long long val_hash[MAXN];
unsigned long long pre[MAXN];
int dp[MAXN];

// 2. 初始化哈希映射
for(int i=1; i<=n; i++) val_hash[i] = rng();

// 3. 计算前缀和
for(int i=1; i<=n; i++) pre[i] = pre[i-1] + val_hash[a[i]];

// 4. DP 转移
for(int i=1; i<=n; i++) {
    int len = a[i];         // 锁死最后一块的长度
    int l = i - len + 1;    // 倒推左边界
    
    if (l >= 1) { // 边界检查
        // 哈希检查：区间和 是否等于 目标值 * 长度
        unsigned long long actual = pre[i] - pre[l-1];
        unsigned long long target = val_hash[len] * len;
        
        if (actual == target) {
            dp[i] = dp[l-1] + 1;
        }
    }
    ans += dp[i];
}
```

### 4\. 易错点备忘

1.  **哈希冲突**：不要用 `int` 或简单的求和（如 $1+4+4 = 3+3+3$），一定要用大随机数。
2.  **前缀和下标**：注意 `pre` 数组通常从 1 开始，`pre[0]` 设为 0。`dp[l-1]` 同理。
3.  **溢出问题**：`unsigned long long` 的溢出是安全的（特性），不要害怕溢出。

```

