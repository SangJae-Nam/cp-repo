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
#include <cstring>

using namespace std;

// https://en.wikipedia.org/wiki/Alternating_permutation
// https://www.geeksforgeeks.org/entringer-number/
// https://mathworld.wolfram.com/EntringerNumber.html
class Zigzag {
public:
	Zigzag (int sz) {
		maxSize = sz + 1;
		dp.resize(maxSize, vector<long long int>(maxSize, -1));
	}

	// An -> up/down/up/.... from (1 to n) == E(n, n)
	long long int numberOfZigzag(int n) {
		if (n <= maxSize) {
			return entringerNumber(n, n);
		}
		else {
			return -1;
		}
	}

private:
	int maxSize;
	vector<vector<long long int>> dp;

	// Return Entringer Number E(n, k)
	long long int entringerNumber(int n, int k) {
		// Base case
		if (k == 0) {
			if (n == 0) {
				return 1;
			}
			else {
				return 0;
			}
		}

		long long int &ret = dp[n][k];
		if (ret != -1) {
			return ret;
		}

		ret = entringerNumber(n, k - 1) + entringerNumber(n - 1, n - k);
		return ret;
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Zigzag zigzag(20);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int N;
		cin >> N;
		if (N == 1) {
			cout << "1\n";
		}
		else {
			cout << zigzag.numberOfZigzag(N) * 2 << '\n';
		}
	}

	return 0;
}
