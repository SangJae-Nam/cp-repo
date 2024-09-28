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

class MaxFlowMatrix {
	public:
		MaxFlowMatrix(int s) : size(s) {
			capacity = vector<vector<int>>(s, vector<int>(s));
			flow = vector<vector<int>>(s, vector<int>(s));
		}

		void addEdge(int s, int e, int c) {
			capacity[s][e] = c;
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

	protected:
		int size;
		vector<vector<int>> capacity;
		vector<vector<int>> flow;

		int bfs(const int source, const int sink) {
			vector<int> parent(size, -1);
			queue<int> q;
			parent[source] = source;
			q.push(source);

			while (!q.empty() && parent[sink] == -1) {
				int here = q.front();
				q.pop();

				for (int there = 0; there < size; there++) {
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

class MaxFlowMatrix2 : public MaxFlowMatrix {
	public:
		MaxFlowMatrix2(int s) : MaxFlowMatrix(s) {}
		void addEdge(int s, int e, int c) {
			capacity[s][e] += c;
		}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	MaxFlowMatrix2 maxFlow(52);
	for (int i = 0; i < N; i++) {
		char s, e;
		int c;

		cin >> s >> e >> c;

		int si, ei;
		if (s >= 'A' && s <= 'Z') {
			si = s - 'A';
		}
		else {
			si = s - 'a' + 26;
		}
		if (e >= 'A' && e <= 'Z') {
			ei = e - 'A';
		}
		else {
			ei = e - 'a' + 26;
		}
		maxFlow.addEdge(si, ei, c);
		maxFlow.addEdge(ei, si, c);
	}

	cout << maxFlow.calculateFlow(0, 'Z' - 'A') << '\n';

	return 0;
}
