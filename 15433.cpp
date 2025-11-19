#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <cassert>
#include <unordered_map>

using namespace std;

class Solve {
private:
	int N, K;
	vector<tuple<int, int, int>> XYB;
	vector<int> square3;

	int root3(int b) {
		auto it = upper_bound(square3.begin(), square3.end(), b);
		return static_cast<int>(it - square3.begin()) - 1;
	}

public:
	Solve () {
		square3.resize(501);
		for (int i = 1; i <= 500; i++) {
			square3[i] = i * i * i;
		}
	}

	void input() {
		cin >> N >> K;
		XYB.resize(K);

		for (int i = 0; i < K; i++) {
			int x, y, b;
			cin >> x >> y >> b;
			XYB[i] = make_tuple(x, y, b);
		}
	}

	void solve() {
		unordered_map<int, vector<pair<int, int>>> xp;

		for (int i = 0; i < K; i++) {
			auto [x, y, b] = XYB[i];
			int hw = root3(b);
			int left = max(0, x - hw);
			int right = min(N, x + hw);

			for (int j = left; j <= right; j++) {
				int xx = abs(x - j);
				xx = xx * xx * xx;
				int hh = root3(b - xx);
				assert(hh >= 0);
				xp[j].push_back(make_pair(max(0, y - hh), min(N, y + hh)));
			}
		}

		long long int ans = (N + 1ll) * (N + 1ll);
		for (auto it = xp.begin(); it != xp.end(); it++) {
			sort(it->second.begin(), it->second.end());

			int lasty = -1;
			for (auto &yrange : it->second) {
				int &yt = yrange.first;
				int &yb = yrange.second;

				if (yb <= lasty) {
					continue;
				}

				int s = max(yt, lasty + 1);
				int e = yb;

				ans -= e - s + 1;
				lasty = e;
			}
		}

		cout << ans << '\n';
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
