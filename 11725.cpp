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
	vector<int> parents;

	void dfs(int node, int prev) {
		parents[node] = prev;

		for (int next : adj[node]) {
			if (next != prev) {
				dfs(next, node);
			}
		}
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		adj.resize(N + 1);
		parents.resize(N + 1);

		for (int i = 0 ; i < N - 1; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}

	void solve() {
		dfs(1, -1);
		for (int i = 2; i <= N; i++) {
			cout << parents[i] << '\n';
		}
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
