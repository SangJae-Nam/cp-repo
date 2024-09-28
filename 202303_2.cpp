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
#include <cstring>

using namespace std;

int N;
int dist[16][16];
int dp[16][1<<16];

int shortestPath(int here, int visited)
{
	if (visited == (1 << (N+1)) - 1) {
		return 0;
	}

	int &ret = dp[here][visited];
	if (ret != -1) {
		return ret;
	}

	ret = 10000000;
	for (int next = 0; next <= N; next++) {
		if (visited & (1 << next)) {
			continue;
		}

		int len = dist[here][next] + shortestPath(next, visited + (1 << next));
		ret = min(len, ret);
	}

	return ret;
}

// 에스켈레이터 빼고
int getMinLength(int az, int ax, int ay, int bz, int bx, int by, int W, int L)
{
	int dx[] = {1, W, 1, W};
	int dy[] = {1, 1, L, L};

	if (az == bz) {
		return abs(ax - bx) + abs(ay - by);
	}
	else {
		int minLength = 10000000;
		for (int i = 0; i < 4; i++) {
			int len = abs(ax - dx[i]) + abs(ay - dy[i]) + abs(bx - dx[i]) + abs(by - dy[i]);
			minLength = min(minLength, len);
		}

		return minLength;
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int F, W, L;
		cin >> F >> W >> L >> N;

		vector<pair<int, pair<int, int>>> people(N + 1); // 0 -> sz,sx,sy
		for (int i = 0; i <= N; i++) {
			cin >> people[i].first >> people[i].second.first >> people[i].second.second;
		}

		memset(dist, 0, sizeof(dist));
		for (int i = 0; i < N; i++) {
			auto &a = people[i].second;
			for (int j = i + 1; j <= N; j++) {
				auto &b = people[j].second;
				int len = getMinLength(people[i].first, a.first, a.second,
										people[j].first, b.first, b.second,
										W, L);
				int height = abs(people[i].first - people[j].first);

				if (people[i].first > people[j].first) {
					dist[i][j] = len + height;
					dist[j][i] = len + height * 2;
				}
				else {
					dist[i][j] = len + height * 2;
					dist[j][i] = len + height;
				}
			}
		}

		/*
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				cout << i << "->" << j << ": " << dist[i][j] << '\n';
			}
		}
		*/

		memset(dp, -1, sizeof(dp));
		cout << shortestPath(0, 1) << '\n';
	}

	return 0;
}
