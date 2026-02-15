#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

class Solve {
private:
	int N, X;
	int hs, ha, hb, hc;
	int ws, wa, wb, wc;

public:
	Solve () {}

	void input() {
		cin >> N >> X;
		cin >> hs >> ha >> hb >> hc;
		cin >> ws >> wa >> wb >> wc;
	}

	void solve() {
		deque<pair<long long int, long long int>> maxq;

		long long int ret = -1;
		long long int H, W;
		H = hs % hc + 1;
		W = ws % wc + 1;
		maxq.push_back({H * W, H});

		for (int i = 1; i < N; i++) {
			H = H + 1 + (H * ha + hb) % hc;
			W = (W * wa + wb) % wc + 1;
			long long hw = H * W;

			while (!maxq.empty() && maxq.front().second + X < H) {
				maxq.pop_front();
			}

			if (!maxq.empty()) {
				ret = max(ret, hw + maxq.front().first);
			}

			while (!maxq.empty() && maxq.back().first < hw) {
				maxq.pop_back();
			}
			maxq.push_back({hw, H});
		}

		cout << ret << '\n';
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

