#include <algorithm>
#include <iostream>
#include <utility>
#include <numeric>
#include <cassert>
#include <cstring>
#include <limits>

using namespace std;

class Solve {
private:
	int N, M;
	int alliance[5000];
public:
	Solve () {}

	void solve() {
		cin >> N >> M;
		memset(alliance, 0, sizeof(int) * N);

		for (int i = 0; i < M; i++) {
			int x, y;
			cin >> x >> y;
			alliance[x - 1]++;
			alliance[y - 1]++;
		}

		long long int ret = 0;
		for (int i = 0; i < N; i++) {
			ret += 1ll * alliance[i] * (N - 1 - alliance[i]);
		}
		ret >>= 1;

		cout << (1ll * N * (N - 1) * (N - 2) / 6) - ret << '\n';

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
		s.solve();
	}

	return 0;
}
