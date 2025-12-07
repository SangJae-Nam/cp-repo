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

class BipartiteMatch2 {
	public:
		BipartiteMatch2(int lSize, int rSize) : leftSize(lSize), rightSize(rSize) {
			adj.resize(lSize);
		}

		void addEdge(int left, int right) {
			adj[left].push_back(right);
		}

		int bipartiteMatch() {
			leftMatch = vector<int>(leftSize, -1);
			rightMatch = vector<int>(rightSize, -1);
			dist = vector<int>(leftSize, 0);

			int size = 0;
			while (bfs()) {
				for (int left = 0; left < leftSize; left++) {
					if (leftMatch[left] == -1 && dfs(left)) {
						size++;
					}
				}
			}
			return size;
		}

	private:
		int leftSize;
		int rightSize;
		vector<vector<int>> adj;
		vector<int> leftMatch;
		vector<int> rightMatch;
		vector<int> dist;

		const int INF = 1e9;

		bool bfs() {
			queue<int> q;

			for (int left = 0; left < leftSize; left++) {
				if (leftMatch[left] == -1) {
					dist[left] = 0;
					q.push(left);
				}
				else {
					dist[left] = INF;
				}
			}

			bool ret = false;
			while (!q.empty()) {
				int left = q.front();
				q.pop();

				for (int right : adj[left]) {
					int pairLeft = rightMatch[right];
					if (pairLeft != -1 && dist[pairLeft] == INF) {
						dist[pairLeft] = dist[left] + 1;
						q.push(pairLeft);
					}
					if (pairLeft == -1) {
						ret = true;
					}
				}
			}
			return ret;
		}

		bool dfs(int left) {
			for (int right : adj[left]) {
				int pairLeft = rightMatch[right];
				if (pairLeft == -1 || (dist[pairLeft] == dist[left] + 1 && dfs(pairLeft))) {
					leftMatch[left] = right;
					rightMatch[right] = left;
					return true;
				}
			}
			dist[left] = INF;
			return false;
		}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;
	BipartiteMatch2 bm(N*2 + 1, M + 1);

	for (int i = 1; i <= N; i++) {
		int size, m;
		cin >> size;
		for (int j = 0; j < size; j++) {
			cin >> m;
			bm.addEdge(i, m);
			bm.addEdge(i + N, m);
		}
	}

	cout << bm.bipartiteMatch() << '\n';

	return 0;
}
