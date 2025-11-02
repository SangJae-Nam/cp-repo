#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

class Solve {
private:
	int N;
	int dp[10000][2];
	vector<int> weights;
	vector<vector<int>> adj;

	int dfs(int cur, int prev, int used) {
		int &ret = dp[cur][used];
		if (ret != -1) {
			return ret;
		}

		if (used) {
			ret = weights[cur];
			for (int next : adj[cur]) {
				if (next != prev) {
					ret += dfs(next, cur, 0);
				}
			}
			return ret;
		}
		else {
			ret = 0;
			for (int next : adj[cur]) {
				if (next != prev) {
					int r1 = dfs(next, cur, 1);
					int r2 = dfs(next, cur, 0);
					if (r1 >= r2) {
						ret += r1;
					}
					else {
						ret += r2;
					}
				}
			}
			return ret;
		}
	}

	void dfs2(int cur, int prev, int used, vector<bool> &sel) {
		if (used) {
			sel[cur] = true;
			for (int next : adj[cur]) {
				if (next != prev) {
					dfs2(next, cur, 0, sel);
				}
			}
		}
		else {
			for (int next : adj[cur]) {
				if (next != prev) {
					if (dp[next][1] >= dp[next][0]) {
						dfs2(next, cur, 1, sel);
					}
					else {
						dfs2(next, cur, 0, sel);
					}
				}
			}
		}
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		weights.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> weights[i];
		}

		adj.resize(N);
		for (int i = 0; i < N - 1; i++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}

	void solve() {
		memset(dp, -1, sizeof(dp));

		int r1 = dfs(0, -1, 1);
		int r2 = dfs(0, -1, 0);

		vector<bool> sel(N);

		if (r1 > r2) {
			dfs2(0, -1, 1, sel);
		}
		else {
			dfs2(0, -1, 0, sel);
		}

		cout << max(r1, r2) << '\n';
		for (int i = 0; i < N; i++) {
			if (sel[i]) {
				cout << i + 1 << ' ';
			}
		}
		cout << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;
	s.input();
	s.solve();

	return 0;
}
