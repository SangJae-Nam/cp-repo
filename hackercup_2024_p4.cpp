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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	for (int t = 1; t <= nTestcases; t++) {
		int N, G;
		cin >> N >> G;

		vector<int> E(N);
		for (int i = 0; i < N; i++) {
			cin >> E[i];
		}
		sort(E.begin(), E.end());

		auto it = upper_bound(E.begin(), E.end(), G);
		int pick;
		if (it != E.end()) {
			int idx = static_cast<int>(it - E.begin());
			if (idx != 0) {
				if (E[idx] - G <= G - E[idx - 1]) {
					pick = idx;
				}
				else {
					pick = idx - 1;
				}
			}
			else {
				pick = 0;
			}
		}
		else {
			pick = N - 1;
		}

		cout << "Case #" << t << ": " << N - pick << ' ' << abs(G - E[pick]) << '\n';
	}

	return 0;
}
