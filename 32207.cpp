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
	int N, M, K;
	int maxIdx;
	vector<pair<int, int>> rubies;
	set<int> selectedRubies;
	const int dr[4] = {-1, 0, 1, 0};
	const int dc[4] = {0, -1, 0, 1};

	int dfs(int seq, int lastSel) {
		if (seq >= min(maxIdx, K)) {
			return 0;
		}

		int maxVal = 0;
		for (int i = lastSel + 1; i < maxIdx; i++) {
			int ir = rubies[i].second / M;
			int ic = rubies[i].second % M;

			bool canUse = true;
			for (int x = 0; x < 4; x++) {
				int nr = ir + dr[x];
				int nc = ic + dc[x];

				if (selectedRubies.find(nr * M + nc) != selectedRubies.end()) {
					canUse = false;
					break;
				}
			}

			if (canUse) {
				selectedRubies.insert(rubies[i].second);
				maxVal = max(maxVal, dfs(seq + 1, i) + rubies[i].first);
				selectedRubies.erase(rubies[i].second);
			}
		}

		return maxVal;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> M >> K;
		rubies.resize(N * M);

		for (int i = 0; i < N * M; i++) {
			cin >> rubies[i].first;
			rubies[i].second = i;
		}
	}

	void solve() {
		sort(rubies.begin(), rubies.end(), greater<pair<int, int>>());
		maxIdx = min(N * M, K * 5 - 4);
		cout << dfs(0, -1) << '\n';
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
