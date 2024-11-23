#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<vector<int>> adj(N + 1);
	vector<int> A(N + 1);

	for (int i = 2; i <= N; i++) {
		int p;
		cin >> p;
		adj[p].push_back(i);
	}
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}

	priority_queue<pair<int, int>> roots;

	roots.push(make_pair(-A[1], 1));
	while (!roots.empty()) {
		auto c = roots.top();
		roots.pop();
		int cur = c.second;
		cout << -c.first << '\n';

		for (int next : adj[cur]) {
			roots.push(make_pair(-A[next], next));
		}
	}

	return 0;
}
