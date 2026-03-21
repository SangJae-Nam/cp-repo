#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <limits>
#include <cassert>
#include <map>

using namespace std;

class Solve {
private:
	int N, K;
	vector<tuple<int, int, int, int>> SEPD;
	map<int, pair<vector<int>, vector<int>>> points; //x : starts, ends
public:
	Solve () {}

	void input() {
		cin >> N >> K;
		SEPD.resize(N);

		for (int i = 0; i < N; i++) {
			int s, e, p, d;
			cin >> s >> e >> p >> d;
			SEPD[i] = {s, e, p, d};

			points[s].first.push_back(i);
			points[e].second.push_back(i);

			if (points.find(s - 1) == points.end()) {
				points[s - 1] = pair<vector<int>, vector<int>>();
			}
			if (points.find(s + 1) == points.end()) {
				points[s + 1] = pair<vector<int>, vector<int>>();
			}
			if (points.find(e - 1) == points.end()) {
				points[e - 1] = pair<vector<int>, vector<int>>();
			}
			if (points.find(e + 1) == points.end()) {
				points[e + 1] = pair<vector<int>, vector<int>>();
			}
		}
	}

	void solve() {
		long long int ans = numeric_limits<long long int>::max();
		int nitems = 0;
		//p + di * si - di * t
		long long int a = 0;
		long long int b = 0;

		for (auto &n : points) {
			for (int idx : n.second.first) {
				int s, e, p, d;
				tie(s, e, p, d) = SEPD[idx];

				nitems++;
				a += p + 1ll * d * s;
				b += -1ll * d;
			}

			if (nitems >= K) {
				const int &t = n.first;
				ans = min(ans, a + b * t);
			}

			for (int idx : n.second.second) {
				int s, e, p, d;
				tie(s, e, p, d) = SEPD[idx];

				nitems--;
				a -= p + 1ll * d * s;
				b -= -1ll * d;
			}
		}

		if (ans == numeric_limits<long long int>::max()) {
			cout << "-1\n";
		}
		else {
			cout << ans << '\n';
		}
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
