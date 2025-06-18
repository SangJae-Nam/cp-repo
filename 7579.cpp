#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <numeric>
#include <cassert>
#include <limits>
#include <cmath>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;
	vector<int> ms(N);
	vector<int> cs(N);

	for (int i = 0; i < N; i++) {
		cin >> ms[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> cs[i];
	}

	constexpr int MAX = 10000;
	vector<int> dp(MAX + 1, -1);
	dp[0] = 0;
	int ret = numeric_limits<int>::max();
	for (int i = 0; i < N; i++) {
		for (int j = MAX - cs[i]; j >= 0; j--) {
			if (dp[j] != -1) {
				int key = j + cs[i];
				dp[key] = max(dp[key], dp[j] + ms[i]);
				if (dp[key] >= M) {
					ret = min(ret, key);
				}
			}
		}
	}

	cout << ret << '\n';

	return 0;
}
