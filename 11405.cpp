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
class MCMF { // Minimum Cost Maximum Flow using SPFA(Shortest Path Faster Algorithm)
             // https://en.wikipedia.org/wiki/Shortest_Path_Faster_Algorithm
	public:
		MCMF(int s) : size(s) {
			capacity = vector<vector<int>>(s, vector<int>(s));
			flow = vector<vector<int>>(s, vector<int>(s));
			cost = vector<vector<int>>(s, vector<int>(s));
			adj = vector<vector<int>>(s);
		}

		void addEdge(int s, int e, int capa, int c) {
			capacity[s][e] = capa;
			cost[s][e] = c;
			cost[e][s] = -c;
			adj[s].push_back(e);
			adj[e].push_back(s);
		}

		pair<int, int> calculateFlow(int source, int sink) {
			int totalFlow = 0;
			int totalCost = 0;

			while (true) {
			 	auto fc = bfs(source, sink);
				int &f = fc.first;
				int &c = fc.second;
				if (f <= 0) {
					break;
				}
				totalFlow += f;
				totalCost += c;
			}

			return make_pair(totalFlow, totalCost);
		}

	private:
		int size;
		vector<vector<int>> capacity;
		vector<vector<int>> flow;
		vector<vector<int>> cost;
		vector<vector<int>> adj;
		static constexpr int INF = 79797979;

		pair<int, int> bfs(const int source, const int sink) {
			vector<int> parent(size, -1);
			vector<bool> inqueue(size, false);
			vector<int> c(size, INF); //cost
			queue<int> q;
			parent[source] = source;
			inqueue[source] = true;
			c[source] = 0;
			q.push(source);

			while (!q.empty()) {
				int here = q.front();
				q.pop();
				inqueue[here] = false;

				for (int there : adj[here]) {
					if (capacity[here][there] - flow[here][there] > 0 &&
						c[there] > c[here] + cost[here][there])
					{
						c[there] = c[here] + cost[here][there];
						parent[there] = here;
						if (!inqueue[there]) {
							q.push(there);
							inqueue[there] = true;
						}
					}
				}
			}

			if (c[sink] == INF) {
				return make_pair(0, INF);
			}

			int amount = numeric_limits<int>::max();
			for (int p = sink; p != source; p = parent[p]) {
				amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
			}

			int curCost = 0;
			for (int p = sink; p != source; p = parent[p]) {
				flow[parent[p]][p] += amount;
				flow[p][parent[p]] -= amount;
				curCost += amount * cost[parent[p]][p];
			}

			return make_pair(amount, curCost);
		}
};


class Solve {
private:
	int N, M;
	vector<int> A;
	vector<int> B;
	vector<vector<int>> C;

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		A.resize(N);
		B.resize(M);
		C.resize(N, vector<int>(M)); // rotate

		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}
		for (int i = 0; i < M; i++) {
			cin >> B[i];
		}
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> C[j][i];
			}
		}
	}

	void solve() {
		MCMF mcmf(N + M + 2); // S, E

		constexpr int S = 0;
		constexpr int E = 1;
		int beginN = 2;
		int beginM = 2 + N;

		for (int i = 0; i < N; i++) {
			mcmf.addEdge(S, beginN + i, A[i], 0);
		}

		for (int i = 0; i < N; i++) {
			int man = beginN + i;

			for (int j = 0; j < M; j++) {
				mcmf.addEdge(man, beginM + j, A[i], C[i][j]);
			}
		}

		for (int i = 0; i < M; i++) {
			mcmf.addEdge(beginM + i, E, B[i], 0);
		}

		auto ret = mcmf.calculateFlow(S, E);
		cout << ret.second << '\n';
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

