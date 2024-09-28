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
#include <cstring>

using namespace std;

static int N, K;
static vector<long long int> prefixSum;
static long long int dp[500005][2];

long long int run(int idx, int prev)
{
	if (idx > N) {
		return 0;
	}

	long long int &ret = dp[idx][prev];
	if (ret != -1) {
		return ret;
	}

	ret = 0;
	int end = (idx + K - 1 <= N) ? idx + K - 1 : N;

	if (prev == 1) {
		ret = max(ret, run(idx + 1, 1) + prefixSum[idx] - prefixSum[idx - 1]);
	}
	ret = max(ret, run(end + 1, 1) + prefixSum[end] - prefixSum[idx - 1]);
	ret = max(ret, run(idx + 1, 0));

	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> K;
	prefixSum.resize(N + 1);

	for (int i = 1; i <= N; i++) {
		int A;
		cin >> A;
		prefixSum[i] = prefixSum[i - 1] + A;
	}

	memset(dp, -1, sizeof(dp));
	cout << run(1, 1) << '\n';

	return 0;
}
