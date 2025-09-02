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

void dijkstra(int start, vector<vector<pair<int, int>>> &adj, vector<pair<int, int>> &dist, int maxSize = 100000000) {
	dist.resize(adj.size(), make_pair(maxSize, -1));  // dist, prev
	priority_queue<pair<int, int>> pq;  // -dist, node

	pq.push(make_pair(0, start));
	dist[start] = make_pair(0, start);

	while (!pq.empty()) {
		int curNode = pq.top().second;
		int curDist = -pq.top().first;
		pq.pop();

		if (dist[curNode].first < curDist) {
			continue;
		}

		for (auto &n : adj[curNode]) {
			int nextNode = n.first;
			int nextDist = curDist + n.second;

			if (nextDist < dist[nextNode].first) {
				dist[nextNode] = make_pair(nextDist, curNode);
				pq.push(make_pair(-nextDist, nextNode));
			}
		}
	}
}

class Solve {
private:
	int N, M;
	int T[3];
	vector<vector<pair<int, int>>> adj;
	vector<vector<int>> adj2;

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		adj.resize(N + 1);
		adj2.resize(N + 1, vector<int>(N + 1));

		for (int i = 0; i < M; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
			adj2[a][b] = c;
			adj2[b][a] = c;
		}

		cin >> T[0] >> T[1] >> T[2];
	}

	void solve() {
		int ret = 200000000;
		vector<pair<int, int>> minLinks;

		for (int c = 1; c <= N; c++) {
			vector<vector<bool>> visited(N + 1, vector<bool>(N + 1));
			vector<pair<int, int>> dist;

			dijkstra(c, adj, dist);

			int d = 0;
			vector<pair<int, int>> links;
			for (int t = 0; t < 3; t++) {
				d += dist[T[t]].first;
				int cur = T[t];
				while (cur != c) {
					int prev = dist[cur].second;
					if (visited[cur][prev] || visited[prev][cur]) {
						d -= adj2[cur][prev];
					}
					else {
						links.push_back(make_pair(min(cur, prev), max(cur, prev)));
					}
					visited[cur][prev] = true;
					visited[prev][cur] = true;
					cur = prev;
				}
			}

			if (d < ret) {
				ret = d;
				minLinks = links;
			}
		}

		cout << ret << ' ' << minLinks.size() << '\n';
		for (auto &l : minLinks) {
			cout << l.first << ' ' << l.second << '\n';
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
