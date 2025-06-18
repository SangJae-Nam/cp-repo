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
	vector<bool> visited;
	map<pair<int, int>, int> dp;

	int dfs(int cur, int prev) {
		auto key = make_pair(cur, prev);
		if (dp.find(key) != dp.end()) {
			return dp[key];
		}

		visited[cur] = true;
		vector<pair<int, int>> connected;
		for (int next : adj[cur]) {
			if (next == prev) {
				continue;
			}

			if (adj[next].size() >= 4) {
				int conn = dfs(next, cur);
				connected.push_back(make_pair(conn, next));
			}
		}

		int sum = 1; //self
		int sizeOfConnect = (prev == -1) ? 4 : 3;
		if (connected.size() > sizeOfConnect) {
			sort(connected.begin(), connected.end());
			for (int i = 0; i < sizeOfConnect; i++) {
				sum += connected[connected.size() - 1 - i].first;
			}
			for (int i = sizeOfConnect; i < connected.size(); i++) {
				visited[connected[connected.size() - 1 - i].second] = false;
			}
		}
		else {
			for (auto &n : connected) {
				sum += n.first;
			}
			sum += (sizeOfConnect - connected.size());
		}

		dp[key] = sum;
		return sum;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		adj.resize(N + 1);
		visited.resize(N + 1);

		int a, b;
		for (int i = 0; i < N - 1; i++) {
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}

	void solve() {
		int ret = -1;
		for (int i = 1; i <= N; i++) {
			if (!visited[i] && adj[i].size() >= 4) {
				ret = max(ret, dfs(i, -1));
			}
		}
		cout << ret << '\n';
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
