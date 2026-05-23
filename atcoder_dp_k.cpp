#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstring>
#include <bitset>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

class Solve {
private:
	int N;
	int K;
	vector<int> A;
	vector<int> dp;

	int run(int remain) {
		assert(remain >= 0 && remain <= K);

		int &ret = dp[remain];
		if (ret != -1) {
			return ret;
		}

		if (remain == 0) {
			return ret = 0;
		}

		ret = 0;
		for (int i = N - 1; i >= 0; i--) {
			if (remain >= A[i]) {
				ret = run(remain - A[i]);
				if (ret == 0) {
					ret = 1;
					break;
				}
				else {
					ret = 0;
				}
			}
		}
		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> K;
		A.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}
		dp.resize(K + 1, -1);
	}

	void solve() {
		if (run(K) == 1) {
			cout << "First\n";
		}
		else {
			cout << "Second\n";
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
