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

	int N, M;
	cin >> N >> M;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	sort(A.begin(), A.end());

	int prev = -1;
	int ret = 0;
	for (int i = 0; i < N; i++) {
		if (prev == A[i]) {
			continue;
		}
		prev = A[i];

		int e = (A[N - 1] - A[i] < M) ? A[N - 1] + 1 : A[i] + M;
		auto it = lower_bound(A.begin() + i, A.end(), e);
		if (it == A.end()) {
			ret = max(ret, N - i);
		}
		else {
			ret = max(ret, static_cast<int>(it - A.begin()) - i);
		}
	}

	cout << ret << '\n';

	return 0;
}
