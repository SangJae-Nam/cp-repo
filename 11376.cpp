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

class BipartiteMatch {
	public:
		BipartiteMatch(int lSize, int rSize) : leftSize(lSize), rightSize(rSize) {
			adj.resize(lSize, vector<bool>(rSize));
			leftMatch.resize(lSize, -1);
			rightMatch.resize(rSize, -1);
		}

		void addEdge(int left, int right) {
			adj[left][right] = true;
		}

		int bipartiteMatch() {
			int size = 0;
			for (int left = 0; left < leftSize; left++) {
				for (int k = 0; k < 2; k++) {
					visited = vector<bool>(leftSize, false);
					if (dfs(left)) {
						size++;
					}
				}
			}

			return size;
		}

	private:
		int leftSize;
		int rightSize;
		vector<vector<bool>> adj;
		vector<int> leftMatch;
		vector<int> rightMatch;
		vector<bool> visited;

		bool dfs(int left) {
			if (visited[left]) {
				return false;
			}
			visited[left] = true;

			for (int right = 0; right < rightSize; right++) {
				if (adj[left][right]) {
					if (rightMatch[right] == -1 || dfs(rightMatch[right])) {
						leftMatch[left] = right;
						rightMatch[right] = left;
						return true;
					}
				}
			}
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
	BipartiteMatch bm(N + 1, M + 1);

	for (int i = 1; i <= N; i++) {
		int size, m;
		cin >> size;
		for (int j = 0; j < size; j++) {
			cin >> m;
			bm.addEdge(i, m);
		}
	}

	cout << bm.bipartiteMatch() << '\n';

	return 0;
}
