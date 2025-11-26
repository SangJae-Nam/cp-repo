#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cstring>

using namespace std;

class Solve {
private:
	int N;
	int root;
	vector<int> V;
	vector<vector<int>> adj;
	long long int dp[100001][2];

	long long int run(int cur, int enable) {
		long long int &ret = dp[cur][enable];
		if (ret != -1) {
			return ret;
		}

		ret = 0;
		if (enable) {
			ret = V[cur];
			for (int next : adj[cur]) {
				ret += run(next, 0);
			}
		}
		else {
			long long int maxEnable = -10000000000000000ll;
			bool enabled = false;

			for (int next : adj[cur]) {
				long long r1 = run(next, 1);
				long long r0 = run(next, 0);

				if (r1 >= r0) {
					enabled = true;
					ret += r1;
				}
				else {
					ret += r0;
					maxEnable = max(maxEnable, r1 - r0);
				}
			}

			if (!enabled && adj[cur].size() > 0) {
				ret += maxEnable;
			}
		}

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		V.resize(N + 1);
		adj.clear();
		adj.resize(N + 1);

		for (int i = 1; i <= N; i++) {
			cin >> V[i];
		}
		for (int i = 1; i <= N; i++) {
			int p;
			cin >> p;
			if (p == 0) {
				root = i;
			}
			else {
				adj[p].push_back(i);
			}
		}
	}

	void solve() {
		memset(dp, -1, sizeof(dp));
		cout << max(run(root, 1), run(root, 0)) << '\n';
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
