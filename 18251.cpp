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
	int N;
	int maxDepth;
	bool allMinus;
	vector<int> tree;
	vector<int> weights;

	int wseq;
	void dfs(int node, int depth, const bitset<20> &zeroDepths) {
		int l = node * 2;
		int r = node * 2 + 1;

		if (l <= N) {
			dfs(l, depth + 1, zeroDepths);
		}

		if (zeroDepths[depth]) {
			weights[wseq++] = 0;
		}
		else {
			weights[wseq++] = tree[node];
		}
		maxDepth = max(maxDepth, depth);

		if (r <= N) {
			dfs(r, depth + 1, zeroDepths);
		}
	}

	long long int maxSeq(const vector<int> &seq) {
		long long int ans = -1000000001;
		long long int di = 0;
		for (int i = 0; i < N; i++) {
			di = max(di + weights[i], static_cast<long long int>(weights[i]));
			if (allMinus && di >= 0) {
				continue;
			}
			ans = max(di, ans);
		}

		return ans;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		tree.resize(N + 1);
		allMinus = true;
		for (int i = 1; i <= N; i++) {
			cin >> tree[i];

			if (tree[i] >= 0) {
				allMinus = false;
			}
		}
	}

	void solve() {
		maxDepth = 0;
		weights.resize(N);
		wseq = 0;
		dfs(1, 1, bitset<20>());

		long long int ans = numeric_limits<long long int>::min();
		ans = max(ans, maxSeq(weights));

		for (int i = 0; i < maxDepth; i++) {
			bitset<20> zero;
			for (int up = 1; up <= i; up++) {
				zero[up] = true;
			}
			for (int j = 0; j < maxDepth - i; j++) {
				if (j > 0) {
					zero[maxDepth + 1 - j] = true;
				}
				wseq = 0;
				dfs(1, 1, zero);
				ans = max(ans, maxSeq(weights));
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

