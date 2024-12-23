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

	int N, Q;
	cin >> N >> Q;

	vector<long long int> A(N + 1);
	vector<long long int> prefixSum(Q + 1);
	vector<int> S(N + 1);
	int ssize = 0;

	for (int q = 1; q <= Q; q++) {
		int x;
		cin >> x;

		if (S[x] != 0) {
			A[x] += prefixSum[q - 1] - prefixSum[S[x] - 1];
			S[x] = 0;
			ssize--;
		}
		else {
			S[x] = q;
			ssize++;
		}

		prefixSum[q] = prefixSum[q - 1] + ssize;
	}

	for (int i = 1; i <= N; i++) {
		if (S[i] != 0) {
			A[i] += prefixSum[Q] - prefixSum[S[i] - 1];
		}
	}

	for (int i = 1; i <= N; i++) {
		cout << A[i] << ' ';
	}
	cout << '\n';

	return 0;
}

