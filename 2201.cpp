#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>

using namespace std;

constexpr int MAX_N = 90;
static long long int dp[MAX_N + 1];

long long int f(int n)
{
	long long int &ret = dp[n];
	if (ret != -1) {
		return ret;
	}

	ret = 1 + f(n - 2) + f(n - 1);
	return ret;
}

long long int g(int n)
{
	return f(n - 1) + 1;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long int K;
	cin >> K;

	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;

	int lo = 1;
	int hi = MAX_N;
	vector<char> ans(MAX_N + 1, '0');
	int start = 0;

	while (K != 0) {
		assert(K > 0);
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (g(mid) <= K) {
				lo = mid;
			}
			else {
				hi = mid;
			}
		}

		K -= g(lo);
		ans[lo - 1] = '1';
		start = max(start, lo - 1);
		hi = lo;
		lo = 1;
	}

	for (int i = start; i >= 0; i--) {
		cout << ans[i];
	}
	cout << '\n';

	return 0;
}
