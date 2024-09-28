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

	int H, W;
	cin >> H >> W;
	vector<vector<int>> A(H + 1, vector<int>(W + 1));
	vector<vector<int>> B(H + 1, vector<int>(W + 1));

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cin >> B[i][j];
		}
	}

	vector<int> row(H + 1);
	for (int i = 1; i <= H; i++) {
		row[i] = i;
	}
	vector<int> col(W + 1);
	for (int i = 1; i <= W; i++) {
		col[i] = i;
	}

	int answer = 1e9;
	do {
		do {
			bool match = true;
			for (int i = 1; i <= H; i++) {
				for (int j = 1; j <= W; j++) {
					if (A[row[i]][col[j]] != B[i][j]) {
						match = false;
						break;
					}
				}
				if (!match) {
					break;
				}
			}
			if (!match) {
				continue;
			}

			int count = 0;
			for (int i = 1; i <= H; i++) {
				for (int j = i + 1; j <= H; j++) {
					if (row[i] > row[j]) {
						count++;
					}
				}
			}
			for (int i = 1; i <= W; i++) {
				for (int j = i + 1; j <= W; j++) {
					if (col[i] > col[j]) {
						count++;
					}
				}
			}
			answer = min(answer, count);

		} while (next_permutation(col.begin() + 1, col.end()));
	} while (next_permutation(row.begin() + 1, row.end()));

	if (answer >= 1e9) {
		cout << "-1\n";
	}
	else {
		cout << answer << '\n';
	}

	return 0;
}
