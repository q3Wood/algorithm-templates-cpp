#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    // 关闭同步流，加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    while (q--) {
        int x;
        cin >> x;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == x) cnt++;
        }
        cout << cnt;
    }
    
    return 0;
}