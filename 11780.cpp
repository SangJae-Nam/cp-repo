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

constexpr int INF = 100000000;

void findPath(int from, int to, const vector<vector<int>> &next, vector<int> &ret)
{
	if (next[from][to] == 0) {
		ret.push_back(from);
		if (from != to) {
			ret.push_back(to);
		}
	}
	else {
		int k = next[from][to];
		findPath(from, k, next, ret);
		ret.pop_back(); //to가 중복으로 들어가므로 지운다.
		findPath(k, to, next, ret);
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	vector<vector<int>> adj(N + 1, vector<int>(N + 1, INF));
	for (int i = 1; i <= N; i++) {
		adj[i][i] = 0;
	}

	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		adj[a][b] = min(adj[a][b], c);
	}

	vector<vector<int>> next(N + 1, vector<int>(N + 1));
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			if (adj[i][k] == INF) {
				continue;
			}
			for (int j = 1; j <= N; j++) {
				if (adj[i][j] > adj[i][k] + adj[k][j]) {
					next[i][j] = k;
					adj[i][j] = adj[i][k] + adj[k][j];
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (adj[i][j] == INF) {
				cout << "0 ";
			}
			else {
				cout << adj[i][j] << ' ';
			}
		}
		cout << '\n';
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (adj[i][j] == 0 || adj[i][j] == INF) {
				cout << "0\n";
				continue;
			}

			vector<int> path;
			findPath(i, j, next, path);
			cout << path.size() << ' ';
			for (int p : path) {
				cout << p << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
