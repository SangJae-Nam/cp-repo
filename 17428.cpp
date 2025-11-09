#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <cassert>
#include <cstring>

using namespace std;

class Solve {
private:
	int N;
	long long int K;

	static constexpr int MAX_N = 50;
	static constexpr int MAX_L = 50;
	long long int dp[MAX_N + 1][MAX_L + 1];

	long long int f(int n, int l) {
		assert(l <= MAX_L);
		if (n <= 0) {
			return 0;
		}
		if (l < 0) {
			return 0;
		}

		long long int &ret = dp[n][l];
		if (ret != -1) {
			return ret;
		}

		if (n == 1) {
			ret = (l == 1) ? 1 : 0;
			return ret;
		}

		ret = f(n - 1, l + 1) + f(n - 1, l - 1);
		return ret;
	}

public:
	Solve () {
		memset(dp, -1, sizeof(dp));
	}

	void input() {
		cin >> N >> K;
	}

	void solve() {
		if (K >= f(N, 0)) {
			cout << "-1\n";
			return;
		}

		string ret;
		ret.reserve(N + 1);
		ret.push_back('(');
		int n = N - 1;
		int l = 1;
		long long int k = K;
		while (n > 0) {
			if (k < f(n - 1, l + 1)) {
				ret.push_back('(');
				n--;
				l++;
			}
			else {
				ret.push_back(')');
				k -= f(n - 1, l + 1);
				n--;
				l--;
			}
		}
		ret.push_back('\n');

		cout << ret;
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
