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
### set的遍历
```cpp
set<int> s = {1, 2, 3, 4, 5};
for (auto it = s.begin(); it != s.end(); ++it) {
    cout << *it << " ";
}

// 遍历时删除元素
for (auto it = s.begin(); it != s.end(); ) {
    if (*it % 2 == 0) { // 删除偶数
        it = s.erase(it); // erase 返回下一个元素的迭代器
    } else {
        ++it;
    }
}
```