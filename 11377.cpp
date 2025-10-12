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
	int N, M, K;

public:
	Solve () {}

	void input() {
		cin >> N >> M >> K;
	}

	void solve() {
		MaxFlowMatrix maxFlow(N + M + 3); // S, E, K

		constexpr int S = 0;
		constexpr int beginK = 1;
		constexpr int E = 2;
		int beginN = 3;
		int beginM = 3 + N;

		for (int i = 0; i < N; i++) {
			int man = beginN + i;
			int njobs;
			cin >> njobs;
			for (int j = 0; j < njobs; j++) {
				int job;
				cin >> job;
				job--;
				maxFlow.addEdge(man, beginM + job, 1);
			}
		}

		for (int i = 0; i < N; i++) {
			maxFlow.addEdge(S, beginN + i, 1);
			maxFlow.addEdge(beginK, beginN + i, 1);
		}
		maxFlow.addEdge(S, beginK, K);
		for (int i = 0; i < M; i++) {
			maxFlow.addEdge(beginM + i, E, 1);
		}

		cout << maxFlow.calculateFlow(S, E) << '\n';
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

