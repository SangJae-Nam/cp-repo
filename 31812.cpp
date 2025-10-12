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

// 서로 다른 두 노드 사이에 간선이 2개 이상이면 사용하지 못함
// -> 두 간선을 합치면 됨
class MaxFlowMatrix {
	public:
		MaxFlowMatrix(int s) : size(s) {
			capacity = vector<vector<int>>(s, vector<int>(s));
			flow = vector<vector<int>>(s, vector<int>(s));
			adj = vector<vector<int>>(s);
		}

		void addEdge(int s, int e, int c) {
			capacity[s][e] = c;
			adj[s].push_back(e);
			adj[e].push_back(s);
		}

		int calculateFlow(int source, int sink) {
			int totalFlow = 0;

			while (true) {
				int f = bfs(source, sink);
				if (f <= 0) {
					break;
				}
				totalFlow += f;
			}

			return totalFlow;
		}

	private:
		int size;
		vector<vector<int>> capacity;
		vector<vector<int>> flow;
		vector<vector<int>> adj;

		int bfs(const int source, const int sink) {
			vector<int> parent(size, -1);
			queue<int> q;
			parent[source] = source;
			q.push(source);

			while (!q.empty() && parent[sink] == -1) {
				int here = q.front();
				q.pop();

				for (int there : adj[here]) {
					if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
						q.push(there);
						parent[there] = here;
					}
				}
			}

			if (parent[sink] == -1) {
				return 0;
			}

			int amount = numeric_limits<int>::max();
			for (int p = sink; p != source; p = parent[p]) {
				amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
			}

			for (int p = sink; p != source; p = parent[p]) {
				flow[parent[p]][p] += amount;
				flow[p][parent[p]] -= amount;
			}

			return amount;
		}
};

class Solve {
private:
	int N, M;
	vector<vector<int>> robots;
	vector<pair<int, int>> buildings; //min, max
	int minScore;

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		robots.resize(N);
		for (int i = 0; i < N; i++) {
			int g;
			cin >> g;
			robots[i].resize(g);
			for (int j = 0; j < g; j++) {
				cin >> robots[i][j];
				robots[i][j]--;
			}
		}

		minScore = 0;
		buildings.resize(M);
		for (int i = 0; i < M; i++) {
			cin >> buildings[i].first >> buildings[i].second;
			minScore += buildings[i].first;
		}
	}

	void solve() {
		vector<int> S(M);

		constexpr int MINCASE = 1;
		constexpr int MAXCASE = 2;
		int curCase = MINCASE;

		int source = 0;
		int sink = 1;
		int robotStart = 2;
		int buildingStart = 2 + N;

		for (int i = 0; i < M; i++) {
			MaxFlowMatrix maxFlow(2 + N + M);
			for (int j = 0; j < N; j++) {
				maxFlow.addEdge(source, robotStart + j, i + 1);
				for (int robot2Building : robots[j]) {
					maxFlow.addEdge(robotStart + j, buildingStart + robot2Building, 1);
				}
			}

			if (curCase == MINCASE) {
				for (int j = 0; j < M; j++) {
					maxFlow.addEdge(buildingStart + j, sink, buildings[j].first);
				}
				int score = maxFlow.calculateFlow(source, sink);
				if (score < minScore) {
					S[i] = -1;
				}
				else {
					curCase = MAXCASE;
					i--;
				}
			}
			else {
				for (int j = 0; j < M; j++) {
					maxFlow.addEdge(buildingStart + j, sink, buildings[j].second);
				}
				int score = maxFlow.calculateFlow(source, sink);
				S[i] = score;
			}
		}

		for (int s : S) {
			cout << s << ' ';
		}
		cout << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;
	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
