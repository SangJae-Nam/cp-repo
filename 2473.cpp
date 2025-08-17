#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <numeric>
#include <limits>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<long long int> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());

	long long int ans = numeric_limits<long long int>::max();
	long long int ans1 = 0, ans2 = 1, ans3 = 2;

	for (int i = 0; i < N - 2; i++) {
		int l = i + 1;
		int r = N - 1;

		while (l < r) {
			long long int s = arr[i] + arr[l] + arr[r];
			if (abs(s) < ans) {
				ans = abs(s);
				ans1 = arr[i];
				ans2 = arr[l];
				ans3 = arr[r];
			}

			if (s == 0) {
				break;
			}
			else if (s < 0) {
				l++;
			}
			else {
				r--;
			}
		}
        
        if (ans == 0) {
            break;
        }
	}

	cout << ans1 << ' ' << ans2 << ' ' << ans3 << '\n';

	return 0;
}

