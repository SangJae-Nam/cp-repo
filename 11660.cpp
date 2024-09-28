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

	vector<vector<int>> arr(N + 1, vector<int>(N + 1));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	vector<vector<int>> queries(M, vector<int>(4));
	for (int i = 0; i < M; i++) {
		cin >> queries[i][0];
		cin >> queries[i][1];
		cin >> queries[i][2];
		cin >> queries[i][3];
	}

	vector<vector<int>> prefixsum(N + 1, vector<int>(N + 1));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			prefixsum[i][j] = prefixsum[i][j - 1] + arr[i][j];
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			prefixsum[i][j] += prefixsum[i - 1][j];
		}
	}

	for (int i = 0; i < M; i++) {
		int &x1 = queries[i][0];
		int &y1 = queries[i][1];
		int &x2 = queries[i][2];
		int &y2 = queries[i][3];
		int sum = prefixsum[x2][y2];
		sum -= prefixsum[x2][y1 - 1];
		sum -= prefixsum[x1 - 1][y2];
		sum += prefixsum[x1 - 1][y1 - 1];

		cout << sum << '\n';
	}

	return 0;
}
