// template Created by q3Wood on 2026/7/7
#include <bits/stdc++.h>
#include <numeric>
#include <sys/types.h>

#define int long long
#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define i128 __int128
#define uint unsigned long long

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
const int knight_moves[8][2] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                                {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int dirs[8][2] = {{0, 1}, {1, 0},  {0, -1}, {-1, 0},
                        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
struct node {
    int x, y;
    bool operator<(const node& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};
void solve() {
    vector<int> l[25];
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int t1 = n / 2;
    for (int i = 0; i < (1 << t1); i++) {
        int xor_sum = 0;
        int cnt = 0;
        for (int j = 0; j < t1; j++) {
            if (i & (1 << j)) {
                xor_sum ^= a[j];
                cnt++;
            }
        }
        l[cnt].push_back(xor_sum);
    }
    for (int i = 0; i <= t1; i++) {
        sort(all(l[i]));
    }
    int ans = 0;
    int t2 = n - t1;
    for (int i = 0; i < (1 << t2); i++) {
        int xor_sum = 0;
        int cnt = 0;
        for (int j = 0; j < t2; j++) {
            if (i & (1 << j)) {
                xor_sum ^= a[t1 + j];
                cnt++;
            }
        }
        int need = k - cnt;
        if (need < 0 || need > t1) continue;
        int target = xor_sum ^ x;
        auto it = lower_bound(all(l[need]), target);
        auto it2 = upper_bound(all(l[need]), target);
        ans = (ans + (it2 - it)) % mod;
    }
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}