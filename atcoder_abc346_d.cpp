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
	string S;

	cin >> N >> S;
	vector<int> C(N);
	for (int i = 0; i < N; i++) {
		cin >> C[i];
	}

	int same = 0;
	for (int i = 0; i < N - 1; i++) {
		if (S[i] == S[i + 1]) {
			same++;
		}
	}

	if (same == 1) {
		cout << "0\n";
		return 0;
	}

	vector<vector<long long int>> costs(2, vector<long long int>(N + 1));
	for (int start = 0; start < 2; start++) {
		int cur = start;
		for (int i = 0; i < N; i++) {
			if (cur != (S[i] - '0')) {
				costs[start][i + 1] += C[i];
			}
			costs[start][i + 1] += costs[start][i];
			cur ^= 1;
		}
	}

	long long int ret = numeric_limits<long long int>::max();
	for (int start = 0; start < 2; start++) {
		int other = start ^ 1;
		for (int i = 1; i < N; i++) {
			long long int cost = costs[start][i];
			cost += costs[other][N] - costs[other][i];
			ret = min(ret, cost);
		}
	}

	cout << ret << '\n';

	return 0;
}
