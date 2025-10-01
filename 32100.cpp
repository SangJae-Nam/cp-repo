#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <numeric>
#include <cassert>
#include <cstring>

using namespace std;

class Solve {
private:
	int N;
	int D[8][8][8];
	int dpMx[8][256][256];
	int dpMn[8][256][256];
	static constexpr int INF = 0x7FEFFFF;
	static constexpr int MINF = -100000000;

	pair<int, int> run(int pos, int cities, int trans) {
		if ((cities == ((1<<N) - 1)) && (trans == ((1<<N) - 1))) {
			return make_pair(0, 0);
		}

		int &retMx = dpMx[pos][cities][trans];
		int &retMn = dpMn[pos][cities][trans];
		if (retMx != -1) {
			return make_pair(retMx, retMn);
		}

		int mx = MINF;
		int mn = INF;

		for (int t = 0; t < N; t++) {
			if (trans & (1<<t)) {
				continue;
			}

			if (cities == ((1<<N) - 1)) {  // Return to 1
				cities &= 0xFFFFFFFE;
			}
			for (int next = 0; next < N; next++) {
				if (D[t][pos][next] == 0) {
					continue;
				}
				if (cities & (1<<next)) {
					continue;
				}

				auto r = run(next, (cities | (1<<next)), (trans | (1<<t)));
				if (r.first != MINF && r.second != INF) {
					mx = max(mx, r.first + D[t][pos][next]);
					mn = min(mn, r.second + D[t][pos][next]);
				}
			}
		}

		retMx = mx;
		retMn = mn;
		return make_pair(mx, mn);
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					cin >> D[i][j][k];
				}
			}
		}
	}

	void solve() {
		memset(dpMx, -1, sizeof(dpMx));
		memset(dpMn, -1, sizeof(dpMn));
		auto ret = run(0, 1, 0);
		if (ret.first == MINF && ret.second == INF) {
			cout << "0 0\n";
		}
		else {
			cout << ret.second << ' ' << ret.first << '\n';
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
