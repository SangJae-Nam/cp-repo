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

int N, M, P;
vector<vector<int>> adj;

pair<int, int> findLeafs(int prev, int cur, int depth)
{
	int maxDepth = 0;
	int numLeafs = 0;
	for (int next : adj[cur]) {
		if (next == prev) {
			continue;
		}

		auto c = findLeafs(cur, next, depth + 1);
		maxDepth = max(maxDepth, c.first);
		numLeafs += c.second;
	}

	if (numLeafs == 0) {
		numLeafs = 1;
		maxDepth = depth;
	}

	return make_pair(maxDepth, numLeafs);
}

int required;
int dfs(int prev, int cur, int deadline)
{
	if (prev == -1) {
		required = 0;
	}

	int elapsed = 99999999;
	for (int next : adj[cur]) {
		if (next == prev) {
			continue;
		}

		elapsed = min(elapsed, dfs(cur, next, deadline));
	}

	if (elapsed == 99999999) {
		elapsed = 0;
		required++;
	}
	else {
		elapsed = (elapsed + 1) % deadline;
		if (elapsed == 0 && cur != P) {
			required++;
		}
	}

	return elapsed;
}

bool can(int time)
{
	dfs(-1, P, time);
	return required <= M;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M >> P;
	adj.resize(N);

	P--;
	for (int i = 0; i < N - 1; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	auto r = findLeafs(-1, P, 0);
	int &maxDepth = r.first;
	int &numLeafs = r.second;

	if (numLeafs > M) {
		cout << "-1\n";
	}
	else {
		int low = 1;
		int high = maxDepth;
		int answer = high;

		while (low <= high) {
			int mid = (low + high) / 2;
			if (can(mid)) {
				answer = mid;
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}

		cout << answer << '\n';
	}

	return 0;
}

