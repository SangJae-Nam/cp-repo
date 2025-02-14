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
				visited = vector<bool>(leftSize, false);
				if (dfs(left)) {
					size++;
				}
			}

			return size;
		}

		void print() {
			for (int l = 0; l < leftSize; l++) {
				for (int r = 0; r < rightSize; r++) {
					cout << (adj[l][r] ? '1' : '0') << ' ';
				}
				cout << '\n';
			}
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

	int N;
	cin >> N;

	vector<tuple<int, int, int>> sharks(N);
	for (int i = 0; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		sharks[i] = make_tuple(a, b, c);
	}

	BipartiteMatch bm(N * 2, N);
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
