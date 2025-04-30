#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <set>
#include <cstring>

using namespace std;

static long long int dp[1<<15][15];
class Solve {
private:
	int N;
	int M;
	vector<int> X;
	vector<int> Y;

	long long int run(int bcards, int apoints) {
		int idx = __builtin_popcount(bcards);
		if (idx >= N) {
			return (apoints == M) ? 1 : 0;
		}

		long long int &ret = dp[bcards][apoints];
		if (ret != -1) {
			return ret;
		}

		ret = 0;
		if (N - idx + apoints < M) {
			return 0;
		}

		int &acard = X[idx];
		for (int i = 0; i < N; i++) {
			if ((bcards & (1<<i)) == 0) {
				int &bcard = Y[i];
				int newapoints = apoints;
				if (((acard < 0) && (bcard < 0)) || ((acard > 0) && (bcard > 0))) {
					if (abs(acard) > abs(bcard)) {
						newapoints += 1;
					}
				}
				else {
					newapoints += 1;
				}
				ret += run(bcards | (1<<i), newapoints);
			}
		}

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		X.resize(N);
		set<int> y;
		for (int i = 0; i < N; i++) {
			y.insert(i + 1);
			y.insert(-i - 1);
		}

		for (int i = 0; i < N; i++) {
			cin >> X[i];
			y.erase(X[i]);
		}
		Y = vector<int>(y.begin(), y.end());
		memset(dp, -1, sizeof(dp));
	}

	void solve() {
		cout << run(0, 0) << '\n';
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
