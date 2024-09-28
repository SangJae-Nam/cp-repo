#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

inline int solve(const long long int X, vector<long long int> &C)
{
	int ret = 0;
	long long int bonus = X / 2;

	sort(C.begin(), C.end());
	int right = lower_bound(C.begin(), C.end(), X) - C.begin();
	if (right == 0) {
		return C.size();
	}
	else {
		ret += C.size() - right;
	}

	int left = lower_bound(C.begin(), C.begin() + right, X - bonus - C[right - 1]) - C.begin();
	int notIncluded = left;
	right--;
	while (left < right) {
		if (C[left] + C[right] + bonus >= X) {
			ret++;
			left++;
			right--;
		}
		else {
			notIncluded++;
			left++;
		}
	}
	if (left == right) {
		notIncluded++;
	}

	ret += notIncluded / 3;

	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	long long int X;
	cin >> N >> X;

	vector<long long int> C(N);
	for (int i = 0; i < N; i++) {
		cin >> C[i];
	}

	cout << solve(X, C) << '\n';

	return 0;
}
