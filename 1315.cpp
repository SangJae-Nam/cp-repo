#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <cassert>
#include <limits>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int maxs = 0;
	int maxi = 0;
	vector<int> STR(N), INT(N), PTR(N);
	for (int i = 0; i < N; i++) {
		cin >> STR[i] >> INT[i] >> PTR[i];
		maxs = max(maxs, STR[i]);
		maxi = max(maxi, INT[i]);
	}

	vector<vector<bool>> ables(1001, vector<bool>(1001));
	vector<vector<int>> points(1001, vector<int>(1001));

	ables[0][1] = true;
	ables[1][0] = true;
	points[1][0] = 1;
	points[0][1] = 1;

	int ret = 0;
	for (int s = 1; s <= maxs; s++) {
		for (int i = 1; i <= maxi; i++) {
			int count = 0;
			for (int q = 0; q < N; q++) {
				if (STR[q] <= s || INT[q] <= i) {
					count++;
					points[s][i] += PTR[q];
				}
			}
			points[s][i] -= s + i - 2;

			if (ables[s-1][i] && points[s-1][i] > 0) {
				ables[s][i] = true;
			}
			else if (ables[s][i-1] && points[s][i-1] > 0) {
				ables[s][i] = true;
			}

			if (ables[s][i]) {
				ret = max(ret, count);
			}

			cout << "S: " << s << " / I: " << i << " / " << points[s][i] << ", " << ables[s][i] << endl;
		}
	}

	cout << ret << '\n';

	return 0;
}
