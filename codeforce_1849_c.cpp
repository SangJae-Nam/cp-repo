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
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int n, m;
		string s;

		cin >> n >> m;
		cin >> s;

		vector<int> zero;
		vector<int> one;

		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				zero.push_back(-i - 1);
			}
			else {
				one.push_back(i + 1);
			}
		}

		set<pair<int, int>> strings;
		for (int i = 0; i < m; i++) {
			int l, r;
			cin >> l >> r;

			if (l == r) {
				strings.insert(make_pair(-1, -1));
			}

			int left, right;
			auto itLeft = lower_bound(one.begin(), one.end(), l);
			if (itLeft != one.end()) {
				if (*itLeft > r) {
					left = n + 1;
				}
				else {
					left = *itLeft;
				}
			}
			else {
				left = n + 1;
			}

			auto itRight = lower_bound(zero.rbegin(), zero.rend(), -r);
			if (itRight != zero.rend()) {
				if (-*itRight < l) {
					right = -1;
				}
				else {
					right = -*itRight;
				}
			}
			else {
				right = -1;
			}

			if (left >= right) {
				strings.insert(make_pair(-1, -1));
			}
			else {
				strings.insert(make_pair(left, right));
			}
		}

		cout << strings.size() << '\n';
	}

	return 0;
}
