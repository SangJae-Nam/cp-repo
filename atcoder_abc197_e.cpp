#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <numeric>
#include <cassert>
#include <cstring>
#include <set>

using namespace std;

class Solve {
private:
	int N;
	vector<pair<int, int>> ballLeftRight;
	vector<int> colors;
	vector<vector<long long int>> dp;

	long long int run(int idx, int lr) {
		long long int &ret = dp[idx][lr];
		if (ret != -1) {
			return ret;
		}

		auto &blr = ballLeftRight[colors[idx]];
		ret = blr.second - blr.first;
		if (idx < colors.size() - 1) {
			auto &nblr = ballLeftRight[colors[idx + 1]];
			long long int r1 = run(idx + 1, 0);
			if (lr == 0) {
				r1 += abs(nblr.first - blr.second);
			}
			else {
				r1 += abs(nblr.first - blr.first);
			}

			long long int r2 = run(idx + 1, 1);
			if (lr == 0) {
				r2 += abs(nblr.second - blr.second);
			}
			else {
				r2 += abs(nblr.second - blr.first);
			}

			ret += min(r1, r2);
		}
		else {
			if (lr == 0) {
				ret += abs(blr.second);
			}
			else {
				ret += abs(blr.first);
			}
		}

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		ballLeftRight.resize(N + 1, {1000000001, -1000000001}); //mn, mx
		set<int> cs;
		for (int i = 0; i < N; i++) {
			int x, c;
			cin >> x >> c;

			ballLeftRight[c].first = min(ballLeftRight[c].first, x);
			ballLeftRight[c].second = max(ballLeftRight[c].second, x);

			cs.insert(c);
		}
		colors = vector<int>(cs.begin(), cs.end());
		dp.resize(N + 1, vector<long long int>(2, -1));
	}

	void solve() {
		long long int r1 = run(0, 0) + abs(ballLeftRight[colors[0]].first);
		long long int r2 = run(0, 1) + abs(ballLeftRight[colors[0]].second);
		cout << min(r1, r2) << '\n';
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
