// Created by q3Wood on 2026/7/7
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
const int dirs[8][2] = {{0, 1},   {1, 0},   {0, -1},  {-1, 0},
                        {1, 1},   {1, -1},  {-1, 1},  {-1, -1}};
struct node {
    int x, y;
    bool operator<(const node& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};
void solve() {
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T; 
    while (T--) {
        solve();
    }
    return 0;
}