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

	int t, n;
	cin >> t >> n;
	vector<int> m(n);
	for (int i = 0; i < n; i++) {
		cin >> m[i];
	}

	int maxLen = 1;
	for (int left = 0; left < n; left++) {
		int maxVal = m[left];
		int minVal = m[left];
		for (int right = left + 1; right < n; right++) {
			maxVal = max(maxVal, m[right]);
			minVal = min(minVal, m[right]);

			if (maxVal - minVal <= t) {
				maxLen = max(maxLen, right - left + 1);
			}
			else {
				break;
			}
		}
	}
	cout << maxLen << '\n';

	return 0;
}
