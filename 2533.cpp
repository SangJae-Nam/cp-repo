#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <bitset>
#include <queue>
#include <limits>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solve {
private:
	int N;
	vector<vector<int>> adj;
	vector<vector<int>> dp;

	int dfs(int cur, int prev, int ea) {
		int &ret = dp[cur][ea];
		if (ret != -1) {
			return ret;
		}

		ret = ea; //0 or 1
		for (int next : adj[cur]) {
			if (next == prev) {
				continue;
			}

			if (ea == 0) {
				ret += dfs(next, cur, 1);
			}
			else {
				int r0 = dfs(next, cur, 0);
				int r1 = dfs(next, cur, 1);
				ret += min(r0, r1);
			}
		}

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		adj.resize(N);
		dp.resize(N, vector<int>(2, -1));
		for (int i = 0; i < N - 1; i++) {
			int u, v;
			cin >> u >> v;
			u--;
			v--;

			adj[u].push_back(v);
			adj[v].push_back(u);
		}
	}

	void solve() {
		int r0 = dfs(0, -1, 0);
		int r1 = dfs(0, -1, 1);
		cout << min(r0, r1) << '\n';
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
