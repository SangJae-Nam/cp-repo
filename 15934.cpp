#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstring>
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
	// 1 based index
	// Referred https://www.geeksforgeeks.org/dsa/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
	public:
		BipartiteMatch2(int lSize, int rSize) : leftSize(lSize), rightSize(rSize) {
			adj.resize(lSize + 1);
		}

		void addEdge(int left, int right) {
			assert(left > 0 && right > 0);
			adj[left].push_back(right);
		}

		int bipartiteMatch() {
			leftMatch = vector<int>(leftSize + 1, 0);
			rightMatch = vector<int>(rightSize + 1, 0);
			dist = vector<int>(leftSize + 1, 0);

			int size = 0;
			while (bfs()) {
				for (int left = 1; left <= leftSize; left++) {
					if (leftMatch[left] == 0 && dfs(left)) {
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

			for (int left = 1; left <= leftSize; left++) {
				if (leftMatch[left] == 0) {
					dist[left] = 0;
					q.push(left);
				}
				else {
					dist[left] = INF;
				}
			}

			dist[0] = INF;
			while (!q.empty()) {
				int left = q.front();
				q.pop();

				if (dist[left] < dist[0]) {
					for (int right : adj[left]) {
						int pairLeft = rightMatch[right];
						if (dist[pairLeft] == INF) {
							dist[pairLeft] = dist[left] + 1;
							q.push(pairLeft);
						}
					}
				}
			}
			return dist[0] != INF;
		}

		bool dfs(int left) {
			if (left == 0) {
				return true;
			}

			for (int right : adj[left]) {
				int pairLeft = rightMatch[right];
				if (dist[pairLeft] == dist[left] + 1 && dfs(pairLeft)) {
					leftMatch[left] = right;
					rightMatch[right] = left;
					return true;
				}
			}
			dist[left] = INF;
			return false;
		}
};

class Solve {
private:
	int R, C, D, W;
	int Y[50][50];
	int city[50][50];
	vector<int> ys;

	long long int calc(int Z) {
		memset(city, 0, sizeof(city));
		int nCity = 0;
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				if (Y[r][c] <= Z) {
					city[r][c] = 1;
					nCity++;
				}
			}
		}
		if ((R * C - nCity) % 2 != 0) {
			return numeric_limits<long long int>::max();
		}

		BipartiteMatch2 bm((R+1) * (C+1) / 2, (R+1) * (C+1) / 2);
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				int lr = ((r % 2) + c) % 2; // 0 == l, 1 == r
				if (city[r][c] == 0) {
					if (c < C - 1 && city[r][c + 1] == 0) {
						if (lr == 0) {
							bm.addEdge((r * C + c) / 2 + 1, (r * C + c + 1) / 2 + 1);
						}
						else {
							bm.addEdge((r * C + c + 1) / 2 + 1, (r * C + c) / 2 + 1);
						}
					}
					if (r < R - 1 && city[r + 1][c] == 0) {
						if (lr == 0) {
							bm.addEdge((r * C + c) / 2 + 1, ((r + 1) * C + c) / 2 + 1);
						}
						else {
							bm.addEdge(((r + 1) * C + c) / 2 + 1, (r * C + c) / 2 + 1);
						}
					}
				}
			}
		}

		int nParks = bm.bipartiteMatch();
		if ((R * C - nCity) / 2 != nParks) {
			return numeric_limits<long long int>::max();
		}

		long long int ret = 1ll * Z * W;
		ret += 1ll * nParks * D;
		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> R >> C >> D >> W;
		ys.reserve(R * C);
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				cin >> Y[r][c];
				ys.push_back(Y[r][c]);
			}
		}
		ys.push_back(0);
		sort(ys.begin(), ys.end());
		ys.erase(unique(ys.begin(), ys.end()), ys.end());
	}

	void solve() {
		long long int ret = numeric_limits<long long int>::max();
		for (int i = ys.size() - 1; i >= 0; i--) {
			ret = min(ret, calc(ys[i]));
		}
		assert(ret != numeric_limits<long long int>::max());
		assert(ret > 0);
		cout << ret << '\n';
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
