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
	int M, N;
	vector<int> L;

	bool check(int len) {
		int m = 0;
		int i = lower_bound(L.begin(), L.end(), len) - L.begin();
		for (; (i < N) && (m < M); i++) {
			int cur = L[i];
			while ((cur >= len) && (m < M)) {
				m++;
				cur -= len;
			}
		}

		return m >= M;
	}

public:
	Solve () {}

	void input() {
		cin >> M >> N;
		L.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> L[i];
		}
		sort(L.begin(), L.end());
	}

	void solve() {
		int lo = 0;
		int hi = 1000000001;

		while (lo + 1 < hi) {
			int mid = (lo + (long long int)hi) / 2;
			if (check(mid)) {
				lo = mid;
			}
			else {
				hi = mid;
			}
		}

		cout << lo << '\n';
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
