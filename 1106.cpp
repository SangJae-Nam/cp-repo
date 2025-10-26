#include <algorithm>
#include <iostream>
#include <utility>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int C, N;
	cin >> C >> N;

	pair<int, int> items[20];
	for (int i = 0; i < N; i++) {
		cin >> items[i].first >> items[i].second;
	}

	int dp[100001];
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;

	int ans = 100000;
	for (int k = 0; k < 1000; k++) {
		for (int i = 100000; i >= 0; i--) {
			if (dp[i] != -1) {
				for (int j = 0; j < N; j++) {
					int &target = dp[i + items[j].first];
					target = max(target, dp[i] + items[j].second);
					if (target >= C) {
						ans = min(ans, i + items[j].first);
					}
				}
			}
		}
	}

	cout << ans << '\n';

	return 0;
}
