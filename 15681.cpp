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
	int N, R, Q;
	vector<vector<int>> adj;

	int ett;
	vector<int> ettIn;
	vector<int> ettOut;

	void dfs(int cur, int parent) {
		ettIn[cur] = ett++;
		for (int next : adj[cur]) {
			if (next == parent) {
				continue;
			}
			dfs(next, cur);
		}
		ettOut[cur] = ett++;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> R >> Q;
		adj.resize(N + 1);
		ettIn.resize(N + 1);
		ettOut.resize(N + 1);

		for (int i = 0; i < N - 1; i++) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
	}

	void solve() {
		ett = 0;
		dfs(R, -1);

		for (int q = 0; q < Q; q++) {
			int u;
			cin >> u;

			int in = ettIn[u];
			int out = ettOut[u];

			cout << (out - in + 1) / 2 << '\n';
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
