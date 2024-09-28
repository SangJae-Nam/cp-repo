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

	int nTestcases;
	cin >> nTestcases;
	for (int t = 1; t <= nTestcases; t++) {
		long long int N, K;
		cin >> N >> K;

		vector<int> S(N);
		for (int i = 0; i < N; i++) {
			cin >> S[i];
		}
		sort(S.begin(), S.end());

		long long int elapsed = 0;
		int left = N;
		while (elapsed <= K && left > 0) {
			elapsed += S[0];
			left -= 2;

			if (left > 0) {
				elapsed += S[0];
				left++;
			}
		}

		if (elapsed <= K && left <= 0) {
			cout << "Case #" << t << ": YES\n";
		}
		else {
			cout << "Case #" << t << ": NO\n";
		}
	}

	return 0;
}
