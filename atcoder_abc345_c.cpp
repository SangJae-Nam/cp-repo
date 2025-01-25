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

	string S;
	cin >> S;
	int slen = static_cast<int>(S.size());

	vector<vector<int>> prefixSum(26, vector<int>(slen + 1));

	for (int i = 0; i < slen; i++) {
		for (int j = 0; j < 26; j++) {
			prefixSum[j][i + 1] = prefixSum[j][i];
		}
		int idx = S[i] - 'a';
		prefixSum[idx][i + 1]++;
	}

	bool allDifferent = true;
	for (int i = 0; i < 26; i++) {
		if (prefixSum[i][slen] > 1) {
			allDifferent = false;
			break;
		}
	}

	long long int ret = 0;
	for (int i = 0; i < slen; i++) {
		int len = slen - i;
		int idx = S[i] - 'a';
		int curCnt = prefixSum[idx][slen] - prefixSum[idx][i];

		ret += len - curCnt;
	}

	if (!allDifferent) {
		ret++; // swap same characters
	}

	cout << ret << '\n';

	return 0;
}
