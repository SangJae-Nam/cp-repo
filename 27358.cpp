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
	vector<int> D, R;
	string S;

	bool run(long long int x) {
		long long int cur = x;
		for (int i = 0; i < N; i++) {
			cur -= D[i];
			if (cur <= 0) {
				return false;
			}

			if (S[i] == '+') {
				if (numeric_limits<long long int>::max() - R[i] < cur) {
					return true;
				}
				cur += R[i];
			}
			else if (S[i] == '*') {
				if (numeric_limits<long long int>::max() / R[i] < cur) {
					return true;
				}
				cur *= R[i];
			}
			else {
				assert(false);
			}
		}

		return true;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		D.resize(N);
		R.resize(N);

		for (int i = 0; i < N; i++) {
			cin >> D[i];
		}
		cin >> S;
		for (int i = 0; i < N; i++) {
			cin >> R[i];
		}
	}

	void solve() {
		long long int lo = 0;
		long long int hi = numeric_limits<long long int>::max();

		while (lo + 1 < hi) {
			long long int mid = lo + (hi - lo) / 2;
			if (!run(mid)) {
				lo = mid;
			}
			else {
				hi = mid;
			}
		}

		cout << hi << '\n';
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
