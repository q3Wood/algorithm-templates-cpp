
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