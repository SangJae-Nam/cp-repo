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

	int N, K;
	cin >> N >> K;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	unordered_set<int> used;
	long long int sum = (1ll + K) * K / 2;
	for (int i = 0; i < N; i++) {
		if (A[i] <= K) {
			if (used.count(A[i]) == 0) {
				sum -= A[i];
			}
			used.insert(A[i]);
		}
	}

	cout << sum << '\n';

	return 0;
}
