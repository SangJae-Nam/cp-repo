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
	int ett;
	vector<vector<int>> adj;
	vector<vector<int>> depth2ett;
	vector<int> ettIn;
	vector<int> ettOut;

	void dfs(int cur, int depth) {
		ettIn[cur] = ett;
		depth2ett[depth].push_back(ett);
		ett++;

		for (int next : adj[cur]) {
			dfs(next, depth + 1);
		}

		ettOut[cur] = ett++;
	}

public:
	Solve() {}
	void input() {
		cin >> N;
		adj.resize(N + 1);
		depth2ett.resize(N + 1);
		ettIn.resize(N + 1);
		ettOut.resize(N + 1);
		for (int i = 2; i <= N; i++) {
			int p;
			cin >> p;
			adj[p].push_back(i);
		}
	}

	void solve() {
		ett = 0;
		dfs(1, 0);

		int Q;
		cin >> Q;
		while (Q--) {
			int u, d;
			cin >> u >> d;

			auto b = lower_bound(depth2ett[d].begin(), depth2ett[d].end(), ettIn[u]);
			auto e = lower_bound(depth2ett[d].begin(), depth2ett[d].end(), ettOut[u]);
			cout << static_cast<int>(e - b) << '\n';
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
