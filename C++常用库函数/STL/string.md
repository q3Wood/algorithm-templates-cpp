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