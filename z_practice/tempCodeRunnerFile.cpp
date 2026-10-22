// template Created by q3Wood on 2026/7/7
#include <bits/stdc++.h>

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
struct Node {
    int x, y;
    string s;
    int cnt;
    bool operator<(const Node& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    for (int i = 2; i < n; i++) {
        int cur = a[i - 1];
        int l = i - 1, r = a[i];
        while (cur <= 900 && l > 0) {
            if (cur % r == 0) ans++;
            l--;
            cur += a[l];
        }
    }
    cout << ans;
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
