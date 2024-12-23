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

	int H, W, M;
	cin >> H >> W >> M;

	vector<int> T(M), A(M), X(M);
	for (int i = 0; i < M; i++) {
		cin >> T[i] >> A[i] >> X[i];
	}

	// color, num of overwritten
	vector<pair<int, int>> row(200001, {-1, 0});
	vector<pair<int, int>> col(200001, {-1, 0});
	int numRows = 0;
	int numCols = 0;

	for (int i = M - 1; i >= 0; i--) {
		int &t = T[i];
		int &a = A[i];
		int &x = X[i];

		if (t == 1) {
			if (row[a].first == -1) {
				row[a].first = x;
				row[a].second = numCols;
				numRows++;
			}
		}
		else if (t == 2) {
			if (col[a].first == -1) {
				col[a].first = x;
				col[a].second = numRows;
				numCols++;
			}
		}
		else {
			assert(false);
		}
	}

	vector<long long int> numColors(200001);
	long long int total = 0;
	for (int i = 1; i < 200001; i++) {
		if (row[i].first != -1) {
			int n = W - row[i].second;
			total += n;
			numColors[row[i].first] += n;
		}
		if (col[i].first != -1) {
			int n = H - col[i].second;
			total += n;
			numColors[col[i].first] += n;
		}
	}

	long long int zeros = static_cast<long long int>(H) * W - total;
	numColors[0] += zeros;

	int kindOfColors = 0;
	for (int i = 0; i < 200001; i++) {
		if (numColors[i] > 0) {
			kindOfColors++;
		}
	}

	cout << kindOfColors << '\n';
	for (int i = 0; i < 200001; i++) {
		if (numColors[i] > 0) {
			cout << i << ' ' << numColors[i] << '\n';
		}
	}

	return 0;
}
