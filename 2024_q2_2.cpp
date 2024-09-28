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
#include <cstring>

using namespace std;

static int dist[8][8][8];
static int dpMin[8][1<<16];
static int dpMax[8][1<<16];
static int N;

pair<int, int> dfs(int city, int trans, int prevCity)
{
	if (city == ((1<<N) - 1)) {
		for (int i = 0; i < N; i++) {
			if (((1<<i) & trans) == 0) {
				if (dist[i][prevCity][0] != 0) {
					int ret = dist[i][prevCity][0];
					return make_pair(ret, ret);
				}
			}
		}

		return make_pair(0, 0);
	}

	int mask = city | (trans<<8);
	if (dpMin[prevCity][mask] != -1) {
		return make_pair(dpMax[prevCity][mask], dpMin[prevCity][mask]);
	}

	int mx = 0;
	int mn = numeric_limits<int>::max();
	for (int i = 0; i < N; i++) {
		if (((1<<i) & trans) == 0) {
			for (int j = 0; j < N; j++) {
				if ((dist[i][prevCity][j] != 0) && (((1<<j) & city) == 0)) {
					auto n = dfs(city | (1<<j), trans | (1<<i), j);
					if (n.first != 0 && n.second != 0) {
						mx = max(mx, n.first + dist[i][prevCity][j]);
						mn = min(mn, n.second + dist[i][prevCity][j]);
					}
				}
			}
		}
	}

	if (mx == 0 && mn == numeric_limits<int>::max()) {
		dpMin[prevCity][mask] = dpMax[prevCity][mask] = 0;
		return make_pair(0, 0);
	}
	else {
		dpMin[prevCity][mask] = mn;
		dpMax[prevCity][mask] = mx;
		return make_pair(mx, mn);
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
		memset(dist, 0, sizeof(dist));
		memset(dpMin, -1, sizeof(dpMin));
		memset(dpMax, -1, sizeof(dpMax));

		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					cin >> dist[i][j][k];
				}
			}
		}

		auto n = dfs(1, 0, 0);
		cout << n.second << ' ' << n.first << '\n';
	}

	return 0;
}

