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

class TopologicalSort2 {  // Queue를 이용한 위상정렬
private:
	vector<vector<int>> &adj;
	vector<int> &indegree; // 진입차수

public:
	TopologicalSort2(vector<vector<int>> &a, vector<int> &i) : adj(a), indegree(i) {
		ts.reserve(a.size());
	}

	void sort() {
		int size = static_cast<int>(adj.size());
		priority_queue<int> q;

		for (int i = 1; i < size; i++) {
			if (indegree[i] == 0) {
				q.push(-i);
			}
		}

		while (!q.empty()) {
			int cur = -q.top();
			q.pop();

			for (int next : adj[cur]) {
				indegree[next]--;
				if (indegree[next] == 0) {
					q.push(-next);
				}
			}

			ts.push_back(cur);
		}
	}

	vector<int> ts; // 순서대로 들어감
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	vector<vector<int>> adj(N + 1);
	vector<int> indegree(N + 1);
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		indegree[b]++;
	}

	TopologicalSort2 ts(adj, indegree);
	ts.sort();

	for (int n : ts.ts) {
		cout << n << ' ';
	}
	cout << '\n';

	return 0;
}
