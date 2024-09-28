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

constexpr int MOD = 1000000007;
long long int dp[1000005][2];

long long int solve(const string &L, int index, int useNumber)
{
	if (index >= L.size()) {
		return 1;
	}

	long long int &ret = dp[index][useNumber];
	if (ret != -1) {
		return ret;
	}

	if (useNumber) {
		if (L[index] == '1') {
			ret = 2 * solve(L, index + 1, 1) % MOD;
			ret += solve(L, index + 1, 0) % MOD;
			ret %= MOD;
		}
		else {
			ret = solve(L, index + 1, 1) % MOD;
		}
	}
	else {
		ret = 3 * solve(L, index + 1, 0) % MOD;
	}

	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string L;
	cin >> L;
	memset(dp, -1, sizeof(dp));
	cout << solve(L, 0, 1) << endl;

	return 0;
}
