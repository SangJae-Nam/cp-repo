#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <numeric>
#include <limits>

using namespace std;

class Solve {
private:
	int N, M;
	vector<int> D;

	bool can(long long int maxEnergy) {
		if (maxEnergy < 0) {
			return false;
		}

		int groups = 1;
		long long int count = 0;
		long long int curEnergy = 0;
		long long int addEnergy = 0;
		for (int d : D) {
			count++;
			addEnergy += d * count;
			curEnergy += addEnergy;
			if (curEnergy > maxEnergy) {
				groups++;
				curEnergy = 0;
				addEnergy = 0;
				count = 0;
			}

			if (groups > M) {
				return false;
			}
		}

		return groups <= M;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		D.resize(N - 1);
		long long int sum = 0;
		for (int i = 0; i < N - 1; i++) {
			cin >> D[i];
			sum += D[i];
		}
	}

	void solve() {
		long long int lo = -1;
		long long int hi = 10e16;

		while (lo + 1 < hi) {
			long long int mid = (lo + hi) / 2;
			if (can(mid)) {
				hi = mid;
			}
			else {
				lo = mid;
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

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		Solve s;
		s.input();
		s.solve();
	}

	return 0;
}
