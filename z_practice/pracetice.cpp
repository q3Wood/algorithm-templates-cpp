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
    vector<int> a(n);
    set<int> dist;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] != 0) {
            dist.insert(a[i]);
        }
    }
    if (dist.size() == 0) {
        cout << 2;
        for (int i = 1; i < n; i++) {
            cout << " 1";
        }
        return;
    }
    if (dist.size() > 2) {
        cout << -1;
        return;
    }
    if (dist.size() == 2) {
        auto it = dist.begin();
        int u = *it++;
        int v = *it;
        if (abs(u - v) != 1) {
            cout << -1;
            return;
        }
        int max_u = -1, min_u = n;
        int max_v = -1, min_v = n;
        for (int i = 0; i < n; i++) {
            if (a[i] == u) {
                max_u = max(max_u, i);
                min_u = min(min_u, i);
            } else if (a[i] == v) {
                max_v = max(max_v, i);
                min_v = min(min_v, i);
            }
        }
        if (max_u < min_v) {
            for (int i = 0; i < min_v; i++) a[i] = u;
            for (int i = min_v; i < n; i++) a[i] = v;
        } else if (max_v < min_u) {
            for (int i = 0; i < min_u; i++) a[i] = v;
            for (int i = min_u; i < n; i++) a[i] = u;
        } else {
            cout << -1;
            return;
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        return;
    }
    if (dist.size() == 1) {
        int x = *dist.begin();
        int first = -1, last = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] == x) {
                if (first == -1) first = i;
                last = i;
            }
        }
        if (first == 0 && last == n - 1) {
            cout << -1;
            return;
        }

        int y = (x == 1) ? 2 : (x - 1);
        
    }

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