#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cstring>

using namespace std;
using ll = long long;

class Solve {
private:
	int N;
	vector<int> A;
	vector<vector<ll>> dp;

	ll run(int left, int right) {
		if (left > right) {
			return 0ll;
		}

		ll &ret = dp[left][right];
		if (ret != -1) {
			return ret;
		}

		ll lrun = run(left + 1, right);
		ll rrun = run(left, right - 1);

		if (N % 2 != (left + right) % 2) {
			// Taro
			ret = max(A[left] + lrun, A[right] + rrun);
		}
		else {
			// Jiro
			ret = min(lrun - A[left], rrun - A[right]);
		}

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		A.resize(N);
		dp.resize(N, vector<ll>(N, -1));
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}
	}

	void solve() {
		cout << run(0, N - 1) << '\n';
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
