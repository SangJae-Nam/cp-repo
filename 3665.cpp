#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <array>
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

class Solve
{
private:
	int n;
	vector<vector<int>> adj;
	vector<int> indegree;
	vector<int> priority;

public:
	Solve() {}
	void input() {
		cin >> n;

		adj.resize(n + 1, vector<int>(n + 1));
		indegree.resize(n + 1);
		priority.resize(n + 1);

		vector<int> last(n);
		for (int i = 0; i < n; i++) {
			cin >> last[i];
			priority[last[i]] = n - i;
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				adj[last[i]][last[j]] = 1;
			}
		}

		int m;
		cin >> m;
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;

			if (adj[a][b] == 1) {
				adj[b][a] = 1;
				adj[a][b] = 0;
			}
			else if (adj[b][a] == 1) {
				adj[a][b] = 1;
				adj[b][a] = 0;
			}
			else {
				assert(false);
				adj[a][b] = 1;
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (adj[i][j] == 1) {
					indegree[j]++;
				}
			}
		}
	}

	void solve() {
		vector<int> ts;
		ts.reserve(n);

		priority_queue<pair<int, int>> q;
		for (int i = 1; i <= n; i++) {
			if (indegree[i] == 0) {
				q.push(make_pair(priority[i], i));
			}
		}

		while (!q.empty()) {
			auto cur = q.top();
			q.pop();

			int curIdx = cur.second;

			for (int next = 1; next <= n; next++) {
				if (adj[curIdx][next] == 1) {
					indegree[next]--;

					if (indegree[next] == 0) {
						q.push(make_pair(priority[next], next));
					}
				}
			}

			ts.push_back(curIdx);
		}

		if (ts.size() != n) {
			cout << "IMPOSSIBLE\n";
		}
		else {
			for (int n : ts) {
				cout << n << ' ';
			}
			cout << '\n';
		}
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		Solve s;
		s.input();
		s.solve();
	}

	return 0;
}
