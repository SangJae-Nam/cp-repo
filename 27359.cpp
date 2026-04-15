#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <numeric>
#include <cassert>
#include <cstring>
#include <limits>

using namespace std;

class Solve {
private:
	static constexpr long long int _MAX = numeric_limits<long long int>::max();
	int N, B, C;
	vector<int> P;
	vector<int> F;
	vector<int> D;
	long long int dp[1001][1001];

	long long int run(int i, int curr) {
		if (i >= N) {
			if (curr >= B) {
				return 0;
			}
			else {
				return _MAX;
			}
		}

		long long int &ret = dp[i][curr];
		if (ret != -1) {
			return ret;
		}

		ret = _MAX;
		long long int r;
		if (curr >= D[i]) {
			r = run(i + 1, curr - D[i]);
			if (r != _MAX) {
				ret = r;
			}
		}
		r = run(i + 1, min(curr + P[i], C));
		if (r != _MAX) {
			ret = min(ret, r + 1ll * D[i] * F[i]);
		}

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> B >> C;
		P.resize(N);
		F.resize(N);
		D.resize(N);

		for (int i = 0; i < N; i++) {
			cin >> P[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> F[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> D[i];
		}
	}

	void solve() {
		memset(dp, -1, sizeof(dp));
		cout << run(0, B) << '\n';
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
