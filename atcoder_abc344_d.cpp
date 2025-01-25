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

class Solve {
private:
	static const int MAX_VAL = 10000;
	string T;
	int N;
	vector<vector<string>> S;
	int dp[101][101];

	int dfs(int sidx, int tidx) {
		if (sidx >= N) {
			if (tidx == static_cast<int>(T.size())) {
				return 0;
			}
			else {
				return MAX_VAL;
			}
		}
		if (tidx == static_cast<int>(T.size())) {
			return 0;
		}
		else if (tidx > static_cast<int>(T.size())) {
			return MAX_VAL;
		}

		int &ret = dp[sidx][tidx];
		if (ret != -1) {
			return ret;
		}

		ret = MAX_VAL;
		for (auto &s : S[sidx]) {
			if (s.size() > T.size() - tidx) {
				continue;
			}

			bool same = true;
			for (size_t i = 0; i != s.size(); i++) {
				if (s[i] != T[tidx + i]) {
					same = false;
					break;
				}
			}

			if (!same) {
				continue;
			}

			ret = min(ret, dfs(sidx + 1, tidx + static_cast<int>(s.size())) + 1);
		}
		ret = min(ret, dfs(sidx + 1, tidx));

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> T >> N;
		S.resize(N);

		for (int i = 0; i < N; i++) {
			int a;
			cin >> a;
			S[i].resize(a);
			for (int j = 0; j < a; j++) {
				cin >> S[i][j];
			}
		}
	}

	void solve() {
		memset(dp, -1, sizeof(dp));
		int ret = dfs(0, 0);
		if (ret != MAX_VAL) {
			cout << ret << '\n';
		}
		else {
			cout << "-1\n";
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
