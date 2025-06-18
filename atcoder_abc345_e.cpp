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
	int N, K;
	vector<int> C;
	vector<int> V;

	vector<vector<map<int, long long int>>> dp;

	long long int dfs(int idx, int prevColor, int numRemove) {
		if (idx >= N) {
			return (numRemove == K) ? 0 : -1;
		}
		else if (numRemove > K) {
			return -1;
		}

		if (dp[idx][numRemove].count(prevColor) > 0) {
			return dp[idx][numRemove][prevColor];
		}

		long long int ret1 = -1, ret2 = -1;
		// remove
		ret1 = dfs(idx + 1, prevColor, numRemove + 1);
		//leave
		if (prevColor != C[idx]) {
			ret2 = dfs(idx + 1, C[idx], numRemove);
			if (ret2 != -1) {
				ret2 += V[idx];
			}
		}

		if (ret1 == -1 && ret2 == -1) {
			dp[idx][numRemove][prevColor] = -1;
			return -1;
		}
		else if (ret1 == -1) {
			dp[idx][numRemove][prevColor] = ret2;
			return ret2;
		}
		else if (ret2 == -1) {
			dp[idx][numRemove][prevColor] = ret1;
			return ret1;
		}
		else {
			dp[idx][numRemove][prevColor] = max(ret1, ret2);
			return max(ret1, ret2);
		}
	}

public:
	Solve () {}

	void input() {
		cin >> N >> K;
		C.resize(N);
		V.resize(N);

		for (int i = 0; i < N; i++) {
			cin >> C[i] >> V[i];
		}

		dp.resize(N + 1, vector<map<int, long long int>>(K + 1));
	}

	void solve() {
		cout << dfs(0, -1, 0) << '\n';
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
