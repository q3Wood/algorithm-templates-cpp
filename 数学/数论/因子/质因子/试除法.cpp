#include <iostream>
#include <map>

using namespace std;

void factorize(long long n, map<long long, int>& cnt) {
    for (long long d = 2; d * d <= n; ++d) {
        while (n % d == 0) {
            cnt[d]++;
            n /= d;
        }
    }
    if (n > 1) {
        cnt[n]++;
    }
}
int main() {
    return 0;
}