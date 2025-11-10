#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

class Solve {
private:
	int N, M, K;
	int dp[11][221][221];

	int f(int n, int m, int s) {
		if (s > m) {
			return 0;
		}
		if (n == 1) {
			return 1;
		}
		assert(m >= 0);
		assert(n <= 10 && m <= 220 && s <= 220);

		int &ret = dp[n][m][s];
		if (ret != -1) {
			return ret;
		}

		ret = 0;
		for (int i = s; i <= m; i++) {
			int r = f(n - 1, m - i, i);
			if (r <= 0) {
				break;
			}
			ret += r;
		}
		return ret;
	}

public:
	Solve () {
		memset(dp, -1, sizeof(dp));
	}

	void input() {
		cin >> N >> M >> K;
	}

	void solve() {
		vector<int> ret;
		ret.reserve(N);

		int start = 1;
		int m = M;
		int k = K;
		for (int n = N; n > 0; n--) {
			int tot = f(n, m, start);
			assert(tot > 0);
			
			for (int s = start; s <= m; s++) {
				if (k <= tot - f(n, m, s + 1)) {
					ret.push_back(s);
					if (s > start) {
						k -= tot - f(n, m, s);
					}
					m -= s;
					start = s;
					break;
				}
			}
		}
		assert(ret.size() == N);

		for (int n : ret) {
			cout << n << ' ';
		}
		cout << '\n';
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

