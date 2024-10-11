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

constexpr int INF = 10000000;

class Solve {
private:
	int N, M;
	string A;
	string SA;
	vector<int> L, R, C;

	unordered_map<string, vector<pair<string, int>>> adj;

public:
	Solve () {}

	void input() {
		cin >> N;
		A.resize(N);
		for (int i = 0; i < N; i++) {
			int a;
			cin >> a;
			a--;
			A[i] = '0' + a;
		}

		cin >> M;
		L.resize(M);
		R.resize(M);
		C.resize(M);

		for (int i = 0; i < M; i++) {
			cin >> L[i] >> R[i] >> C[i];
			L[i]--;
			R[i]--;
		}
	}

	void solve() {
		SA = A;
		sort(SA.begin(), SA.end());

		// Make graph
		unordered_map<string, int> dist;
		do {
			adj[SA] = vector<pair<string, int>>();
			dist[SA] = INF;
			for (int i = 0; i < M; i++) {
				string s(SA);
				swap(s[L[i]], s[R[i]]);
				adj[SA].push_back(make_pair(s, C[i]));
			}
		} while (next_permutation(SA.begin(), SA.end()));

		//Dijkstra
		priority_queue<pair<int, string>> q;
		dist[A] = 0;
		q.push(make_pair(0, A));

		while (!q.empty()) {
			auto cur = q.top();
			q.pop();
			int curDist = -cur.first;
			string &curStr = cur.second;

			if (dist[curStr] < curDist) {
				continue;
			}

			for (auto next : adj[curStr]) {
				int nextDist = curDist + next.second;
				string &nextStr = next.first;
				if (nextDist < dist[nextStr]) {
					dist[nextStr] = nextDist;
					q.push(make_pair(-nextDist, nextStr));
				}
			}
		}

		if (dist[SA] == INF) {
			cout << "-1\n";
		}
		else {
			cout << dist[SA] << '\n';
		}
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
