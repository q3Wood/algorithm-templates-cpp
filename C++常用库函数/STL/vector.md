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
```