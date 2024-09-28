#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <array>
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
	while (nTestcases--) {
		int N, K;
		long long int a, b;
		cin >> N >> K >> a >> b;

		vector<int> sticks(N);
		int maxLength = 0;
		for (int i = 0; i < N; i++) {
			cin >> sticks[i];
			maxLength += sticks[i];
		}

		long long int MAX_VAL = 1e18;
		vector<long long int> dp(maxLength + 1, MAX_VAL);
		dp[0] = 0;

		for (int i = 0; i < N; i++) {
			for (int j = maxLength; j >= 0; j--) {
				if (dp[j] == MAX_VAL) {
					continue;
				}

				long long int cost;
				if (sticks[i] > 1) {
					cost = a * (sticks[i] - 1) * (sticks[i] - 1) + b;
				}
				else {
					cost = 0ll;
				}

				int newLen = j + sticks[i];
				dp[newLen] = min(dp[j] + cost, dp[newLen]);
			}
		}

		long long int ret = numeric_limits<long long int>::max();
		for (int i = K; i <= maxLength; i++) {
			ret = min(ret, dp[i]);
		}

		cout << ret << '\n';
	}

	return 0;
}
