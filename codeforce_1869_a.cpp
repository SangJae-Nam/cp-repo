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

using namespace std;

void solve(const vector<short> &a)
{
	int n = static_cast<int>(a.size());

	short allXor = 0;
	for (short ai : a) {
		allXor ^= ai;
	}

	vector<pair<int, int>> result;
	if (allXor == 0) {
		result.push_back(make_pair(1, n));
	}
	else if (n % 2 == 0) {
		result.push_back(make_pair(1, n));
		result.push_back(make_pair(1, n));
	}
	else {
		int leftNotZeroIdx = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] != 0) {
				leftNotZeroIdx = i;
				break;
			}
		}
		int rightNotZeroIdx = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (a[i] != 0) {
				rightNotZeroIdx = i;
				break;
			}
		}

		int notZeroCnt = n - leftNotZeroIdx - (n - 1 - rightNotZeroIdx);
		if (notZeroCnt % 2 == 0) {
			result.push_back(make_pair(leftNotZeroIdx + 1, rightNotZeroIdx + 1));
			result.push_back(make_pair(leftNotZeroIdx + 1, rightNotZeroIdx + 1));
		}
		else {
			result.push_back(make_pair(1, n));
			result.push_back(make_pair(1, n - 1));
			result.push_back(make_pair(n - 1, n));
			result.push_back(make_pair(n - 1, n));
		}
	}

	cout << result.size() << '\n';
	for (auto &r : result) {
		cout << r.first << ' ' << r.second << '\n';
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int n;
		cin >> n;

		vector<short> a(n);
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}

		solve(a);
	}

	return 0;
}
