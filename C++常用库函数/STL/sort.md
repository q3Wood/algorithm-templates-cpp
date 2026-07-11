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