#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;

class Solve {
private:
	int N, S;
	vector<int> X;

	bool check(int mid) {
		int last = 0;
		int s = 1;
		for (int i = 1; i < N && s < S; i++) {
			if (X[i] - X[last] >= mid) {
				s++;
				last = i;
			}
		}

		return s >= S;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> S;
		X.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> X[i];
		}
	}

	void solve() {
		sort(X.begin(), X.end());

		long long int lo = 0;
		long long int hi = 1000000001;
		while (lo + 1 < hi) {
			long long int mid = (lo + hi) / 2;
			if (check(static_cast<int>(mid))) {
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

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
