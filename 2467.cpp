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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<int> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());

	int ans = numeric_limits<int>::max();
	int ans1 = 0, ans2 = 1;

	for (int i = 0; i < N - 1; i++) {
		int v = abs(arr[i + 1] + arr[i]);
		if (v < ans) {
			ans = v;
			ans1 = arr[i];
			ans2 = arr[i + 1];
		}
	}

	if (arr[0] >= 0 || arr[N - 1] <= 0 || ans == 0) {
		cout << ans1 << ' ' << ans2 << '\n';
		return 0;
	}

	for (int i = 0; i < N; i++) {
		if (arr[i] > 0) {
			break;
		}

		auto it = lower_bound(arr.begin() + i + 1, arr.end(), -arr[i]);
		int idx = it - arr.begin();

		for (int j = idx - 1; j <= idx && j < N && i < j; j++) {
			int v = abs(arr[i] + arr[j]);
			if (v < ans) {
				ans = v;
				ans1 = arr[i];
				ans2 = arr[j];
			}
			if (v == 0) {
				break;
			}
		}
	}

	cout << ans1 << ' ' << ans2 << '\n';

	return 0;
}
