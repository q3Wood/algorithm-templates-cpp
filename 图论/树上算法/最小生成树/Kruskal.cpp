#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct node {
	int u, v, val;
};
int fa[5005];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	vector<node> e(m);
	for (int i = 0; i < m; i++) {
		cin >> e[i].u >> e[i].v >> e[i].val;
	}
	sort(e.begin(), e.end(), [&](node a, node b) {
		return a.val < b.val;
		});
	int ans = 0, cnt = 0;
	for (int i = 0; i < m; i++) {
		int u = find(e[i].u);
		int v = find(e[i].v);
		if (u == v) continue;
		cnt++;
		ans += e[i].val;
		fa[v] = u;
	}
	if (cnt == n - 1) cout << ans << endl;
	else cout << "orz" << endl;
	return 0;
}