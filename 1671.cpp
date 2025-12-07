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

	int N;
	cin >> N;

	vector<tuple<int, int, int>> sharks(N);
	for (int i = 0; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		sharks[i] = make_tuple(a, b, c);
	}

	BipartiteMatch2 bm(N * 2, N);
	for (int i = 0; i < N; i++) {
		int a, b, c;
		tie(a, b, c) = sharks[i];
		for (int j = i + 1; j < N; j++) {
			int d, e, f;
			tie(d, e, f) = sharks[j];
			if (a >= d && b >= e && c >= f) {
				bm.addEdge(i * 2, j);
				bm.addEdge(i * 2 + 1, j);
			}
			else if (a <= d && b <= e && c <= f) {
				bm.addEdge(j * 2, i);
				bm.addEdge(j * 2 + 1, i);
			}
		}
	}

	cout << N - bm.bipartiteMatch() << '\n';

	return 0;
}
