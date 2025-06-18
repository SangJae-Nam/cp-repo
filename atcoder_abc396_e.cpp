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

class Solve {
private:
	int N, M;
	vector<vector<pair<int, int>>> adj;

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		adj.resize(N + 1);
		for (int i = 0; i < M; i++) {
			int x, y, z;
			cin >> x >> y >> z;

			adj[x].push_back(make_pair(y, z));
			adj[y].push_back(make_pair(x, z));
		}
	}

	void solve() {
		queue<int> q;
		vector<int> A(N + 1, -1);
		vector<vector<int>> groups(N + 1);

		for (int i = 1; i <= N; i++) {
			if (A[i] != -1) {
				continue;
			}

			q.push(i);
			A[i] = 0;
			groups[i].push_back(i);
			while (!q.empty()) {
				int curNode = q.front();
				q.pop();

				for (auto &n : adj[curNode]) {
					int &nextNode = n.first;
					int &nextVal = n.second;

					if (A[nextNode] != -1) {
						if ((A[curNode] ^ A[nextNode]) != nextVal) {
							cout << "-1\n";
							return;
						}
					}
					else {
						q.push(nextNode);
						groups[i].push_back(nextNode);
						A[nextNode] = A[curNode] ^ nextVal;
					}
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			if (groups[i].empty()) {
				continue;
			}

			int newVal = 0;
			for (int bb = 0; bb < 31; bb++) {
				int b = 0;
				for (int node : groups[i]) {
					if ((A[node] & (1<<bb)) != 0) {
						b++;
					}
				}
				if (b > groups[i].size() / 2) {
					newVal |= (1<<bb);
				}
			}
			A[groups[i][0]] = newVal;
			vector<bool> visited(N + 1);

			q.push(groups[i][0]);
			visited[groups[i][0]] = true;
			while (!q.empty()) {
				int curNode = q.front();
				q.pop();

				for (auto &n : adj[curNode]) {
					int &nextNode = n.first;
					int &nextVal = n.second;

					if (visited[nextNode]) {
						continue;
					}

					q.push(nextNode);
					visited[nextNode] = true;
					A[nextNode] = A[curNode] ^ nextVal;
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			cout << A[i] << ' ';
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
	s.input();
	s.solve();

	return 0;
}
