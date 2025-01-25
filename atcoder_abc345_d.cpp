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
	int N, H, W;
	vector<pair<int, int>> AB;
	vector<vector<bool>> arr;
	vector<bool> used;

	pair<int, int> findNext(int x, int y) {
		if (x == W) {
			x = 0;
			y++;
		}

		for (int h = y; h < H; h++) {
			int sx = (h == y) ? x : 0;
			for (int w = sx; w < W; w++) {
				if (!arr[h][w]) {
					return make_pair(w, h);
				}
			}
		}

		return make_pair(W, H);
	}

	bool fill(int sx, int sy, int width, int height, bool val) {
		vector<pair<int, int>> filled;
		filled.reserve(100);

		bool failed = false;
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				if (val && arr[sy + h][sx + w]) {
					failed = true;
					break;
				}
				else {
					arr[sy + h][sx + w] = val;
					filled.push_back(make_pair(w, h));
				}
			}
			if (failed) {
				break;
			}
		}

		if (failed) {
			//rollback
			for (auto &xy : filled) {
				arr[sy + xy.second][sx + xy.first] = false;
			}
		}

		return !failed;
	}

	bool dfs(int x, int y) {
		if (x >= W && y >= H) {
			return true;
		}

		for (int i = 0; i < N; i++) {
			if (used[i]) {
				continue;
			}

			if (x + AB[i].first <= W && y + AB[i].second <= H) {
				if (!fill(x, y, AB[i].first, AB[i].second, true)) {
					continue;
				}
				auto next = findNext(x + AB[i].first, y);
				used[i] = true;
				if (dfs(next.first, next.second)) {
					return true;
				}
				used[i] = false;
				fill(x, y, AB[i].first, AB[i].second, false);
			}

			if (x + AB[i].second <= W && y + AB[i].first <= H) {
				if (!fill(x, y, AB[i].second, AB[i].first, true)) {
					continue;
				}
				auto next = findNext(x + AB[i].second, y);
				used[i] = true;
				if (dfs(next.first, next.second)) {
					return true;
				}
				used[i] = false;
				fill(x, y, AB[i].second, AB[i].first, false);
			}
		}

		return false;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> H >> W;
		AB.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> AB[i].first >> AB[i].second;
		}
	}

	void solve() {
		arr.resize(H, vector<bool>(W));
		used.resize(N);

		if (dfs(0, 0)) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
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
