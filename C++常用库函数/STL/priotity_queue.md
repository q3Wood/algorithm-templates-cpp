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