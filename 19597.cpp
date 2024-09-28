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
	int N;
	vector<string> strings[2];
	vector<vector<int>> dp;

	static constexpr int INV = 2;

	int dfs(int i, int reverse) {
		if (i >= N - 1) {
			return 1;
		}

		if (dp[i][reverse] != -1) {
			return dp[i][reverse];
		}

		int &ret = dp[i][reverse];
		string &cur = strings[reverse][i];
		if (cur.compare(strings[0][i + 1]) < 0) {
			if (dfs(i + 1, 0) != INV) {
				return ret = 0;
			}
		}

		if (cur.compare(strings[1][i + 1]) < 0) {
			if (dfs(i + 1, 1) != INV) {
				return ret = 1;
			}
		}

		return ret = INV;
	}

public:
	Solve() {
	}

	void input() {
		cin >> N;
		strings[0].resize(N);
		strings[1].resize(N);

		for (int i = 0; i < N; i++) {
			cin >> strings[0][i];
			strings[1][i] = strings[0][i];
			reverse(strings[1][i].begin(), strings[1][i].end());
		}
	}

	void solve() {
		dp.clear();
		dp = vector<vector<int>>(N, vector<int>(2, -1));
		if (dfs(0, 0) != INV) {
			string ret = "0";
			int cur = 0;
			ret.reserve(N);
			for (int i = 0; i < N - 1; i++) {
				ret += static_cast<char>(dp[i][cur] + '0');
				cur = dp[i][cur];
			}

			cout << ret << '\n';
			return;
		}

		if (dfs(0, 1) != INV) {
			string ret = "1";
			int cur = 1;
			ret.reserve(N);
			for (int i = 0; i < N - 1; i++) {
				ret += static_cast<char>(dp[i][cur] + '0');
				cur = dp[i][cur];
			}

			cout << ret << '\n';
			return;
		}

		assert(false);
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
