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

### 合并两个vector
```cpp
vec1.insert(vec1.end(), vec2.begin(), vec2.end());
```