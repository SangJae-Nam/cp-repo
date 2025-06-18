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
	vector<int> AB;

	int check(int d) {
		int ret = 0;
		int right = upper_bound(AB.begin() + 1, AB.end(), AB[0] + d) - AB.begin();
		for (int i = 0; i < N - 1; i++) {
			int x = AB[i] + d;
			right = max(right, i + 1);
			while (right < N && AB[right] <= x) {
				right++;
			}
			int count = right - (i + 1);
			ret += count;
		}
		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> K;
		AB.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> AB[i];
		}
		for (int i = 0; i < N; i++) {
			int b;
			cin >> b;
			AB[i] -= b;
		}
	}

	void solve() {
		sort(AB.begin(), AB.end());

		int lo = -1;
		int hi = abs(*AB.begin() - *AB.rbegin()) + 1;
		int cd = -1;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			cd = check(mid);
			if (cd >= K) {
				hi = mid;
			}
			else {
				lo = mid;
			}
		}

		if (check(hi) == K) {
			cout << hi << '\n';
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
	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
