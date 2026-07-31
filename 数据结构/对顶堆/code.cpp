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