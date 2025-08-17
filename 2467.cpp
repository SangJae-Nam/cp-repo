#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

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

	int l = 0;
	int r = N - 1;

	int ans = abs(arr[l] + arr[r]);
	int ans1 = arr[l], ans2 = arr[r];

	while (l < r) {
		int sum = arr[l] + arr[r];
		if (abs(sum) < ans) {
			ans = abs(sum);
			ans1 = arr[l];
			ans2 = arr[r];
		}

		if (sum < 0) {
			l++;
		}
		else if (sum == 0) {
			break;
		}
		else {
			r--;
		}
	}

	cout << ans1 << ' ' << ans2 << '\n';

	return 0;
}
