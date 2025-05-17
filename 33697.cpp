#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

constexpr int UP = 0;
constexpr int DN = 1;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, Q;
	cin >> N >> M >> Q;

	vector<vector<vector<int>>> adj(2, vector<vector<int>>(N));

	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;

		if (x > y) {
			swap(x, y);
		}

		adj[UP][x].push_back(y);
		adj[DN][y].push_back(x);
	}

	vector<tuple<int, int, int>> quiries;
	quiries.reserve(Q);
	for (int i = 0; i < Q; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		x--;
		y--;
		quiries.emplace_back(make_tuple(x, y, z));
	}

	vector<int> ret(N);
	vector<vector<bool>> visited(2, vector<bool>(N));
	for (int i = Q - 1; i >= 0; i--) {
		int node, updown, light;
		tie(node, updown, light) = quiries[i];

		if (visited[updown][node]) {
			continue;
		}

		queue<int> q;
		q.push(node);
		visited[updown][node] = true;

		while (!q.empty()) {
			int cur = q.front();
			q.pop();

			if (ret[cur] == 0) {
				ret[cur] = light;
			}

			for (int next : adj[updown][cur]) {
				if (!visited[updown][next]) {
					visited[updown][next] = true;
					q.push(next);
				}
			}
		}
	}

	for (int n : ret) {
		cout << n << ' ';
	}
	cout << '\n';

	return 0;
}
