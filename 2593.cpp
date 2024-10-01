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

pair<int, int> getMinMax(pair<int, int> &elevator, int N)
{
	int mn = elevator.second;
	int mx = (N - elevator.second) / elevator.first;
	mx *= elevator.first;
	mx += elevator.second;

	return make_pair(mn, mx);
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, A, B;
	cin >> N >> M;
	vector<pair<int, int>> elevators(M + 1);
	vector<vector<int>> floorToEle(N + 1);
	for (int i = 1; i <= M; i++) {
		cin >> elevators[i].second >> elevators[i].first;

		int &a = elevators[i].first;
		int &b = elevators[i].second;
		int f = b;
		do {
			floorToEle[f].push_back(i);
			f += a;
		} while (f <= N);
	}
	cin >> A >> B;

	vector<vector<int>> adj(M + 1, vector<int>(M + 1));
	for (int f = 1; f <= N; f++) {
		if (floorToEle[f].size() >= 2) {
			int size = static_cast<int>(floorToEle[f].size());
			for (int i = 0; i < size; i++) {
				for (int j = i + 1; j < size; j++) {
					int &t = floorToEle[f][i];
					int &e = floorToEle[f][j];
					adj[t][e] = 1;
					adj[e][t] = 1;
				}
			}
		}
	}

	// A에서 B로 가는 플로이드 워셜
	vector<vector<int>> dist(M + 1, vector<int>(M + 1));
	vector<vector<int>> next(M + 1, vector<int>(M + 1));

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= M; j++) {
			if (i == j) {
				dist[i][j] = 0;
			}
			else if(adj[i][j] == 1) {
				dist[i][j] = 1;
			}
			else {
				dist[i][j] = INF;
			}
		}
	}

	for (int k = 1; k <= M; k++) {
		for (int i = 1; i <= M; i++) {
			if (dist[i][k] == INF) {
				continue;
			}
			for (int j = 1; j <= M; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					next[i][j] = k;
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	int minVal = INF;
	int minA = -1;
	int minB = -1;

	for (int i : floorToEle[A]) {
		for (int j : floorToEle[B]) {
			if (dist[i][j] < minVal) {
				minVal = dist[i][j];
				minA = i;
				minB = j;
			}
		}
	}

	if (minVal == INF) {
		cout << "-1\n";
	}
	else {
		cout << dist[minA][minB] + 1 << '\n';

		vector<int> path;
		findPath(minA, minB, next, path);
		for (int p : path) {
			cout << p << '\n';
		}
	}

	return 0;
}
