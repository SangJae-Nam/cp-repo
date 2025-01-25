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

	int numWeights;
	int numBeads;

	cin >> numWeights;
	vector<int> weights(numWeights);
	for (int i = 0; i < numWeights; i++) {
		cin >> weights[i];
	}

	cin >> numBeads;
	vector<int> beads(numBeads);
	for (int i = 0; i < numBeads; i++) {
		cin >> beads[i];
	}

	vector<vector<int>> dp(numWeights, vector<int>(40001));
	dp[0][0] = 1;
	dp[0][weights[0]] = 1;
	for (int i = 1; i < numWeights; i++) {
		dp[i][0] = 1;
		for (int j = 0; j < 40001; j++) {
			dp[i][j] = (dp[i - 1][j] == 1) ? 1 : dp[i][j];
			if (dp[i - 1][j] == 0) {
				continue;
			}
			int newWeight = j + weights[i];
			if (newWeight > 0 && newWeight < 40001) {
				dp[i][newWeight] = 1;
			}
			newWeight = abs(j - weights[i]);
			if (newWeight > 0 && newWeight < 40001) {
				dp[i][newWeight] = 1;
			}
		}
	}

	for (int i = 0; i < numBeads; i++) {
		if (dp[numWeights - 1][beads[i]] != 0) {
			cout << "Y ";
		}
		else {
			cout << "N ";
		}
	}
	cout << '\n';

	return 0;
}
