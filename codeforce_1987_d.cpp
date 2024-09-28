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

int solve(vector<char> &selected, vector<short> &A)
{
	for (

	int ret = 0;
	for (int i = 0; i < A.size(); i++) {
		if (!selected[i]) {
			ret = max(ret, solve(
		}
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

		vector<short> A(n);
		for (int i = 0; i < n; i++) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());

		vector<short> aliceSel;
		aliceSel.reserve(n);
		aliceSel.push_back(0);

		cout << solve(aliceSel, A) << '\n';
	}

	return 0;
}
