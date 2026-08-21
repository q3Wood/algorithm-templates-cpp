#include <iostream>
#include <vector>

// 手写手算法：求两个数的 GCD（欧几里得算法/辗转相除法）
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 手写算法：求两个数的 LCM
// ⚠️ 注意：一定要先除以 GCD 再乘 b，防止 intermediate（中间结果）溢出！
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

// 求多个数的 GCD
long long get_array_gcd(const std::vector<long long>& nums) {
    if (nums.empty()) return 0;
    long long ans = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        ans = gcd(ans, nums[i]);
        if (ans == 1) break;
    }
    return ans;
}

// 求多个数的 LCM
long long get_array_lcm(const std::vector<long long>& nums) {
    if (nums.empty()) return 0;
    long long ans = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        ans = lcm(ans, nums[i]);
    }
    return ans;
}

int main() {
    std::vector<long long> nums = {12, 18, 24, 30};

    std::cout << "GCD: " << get_array_gcd(nums) << std::endl; // 输出: 6
    std::cout << "LCM: " << get_array_lcm(nums) << std::endl; // 输出: 360

    return 0;
}