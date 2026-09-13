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
    int n;
    cin >> n;
    vector<int> a(2 * n);
    vector<int> index(n + 1, -1);
    for (int i = 0; i < 2 *n; i++) {
        cin >> a[i];
        if (index[a[i]] == -1) {
            index[a[i]] = i;
        }
    }
    vector<int> pre(2 * n + 1);
    for (int i = 0; i < 2 * n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }
    vector<int> f(2 * n + 1);
    int m = 2 * n;
    for (int i = 0; i < m; i++) {
        f[i + 1] = f[i];
        if (index[a[i]] != i) {
            f[i + 1] = max(f[i + 1], f[index[a[i]]] + pre[i + 1] - pre[index[a[i]]]);
        }
    }
    cout << f[m];
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