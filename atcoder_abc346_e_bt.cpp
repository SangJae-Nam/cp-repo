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

	vector<vector<int>> arr(H, vector<int>(W));
	for (int i = 0; i < M; i++) {
		int t, a, x;
		cin >> t >> a >> x;
		a--;

		if (t == 1) {
			for (int c = 0; c < W; c++) {
				arr[a][c] = x;
			}
		}
		else if (t == 2) {
			for (int r = 0; r < H; r++) {
				arr[r][a] = x;
			}
		}
	}

	int kindOfColors = 0;
	vector<long long int> numColors(200001);
	for (int r = 0; r < H; r++) {
		for (int c = 0; c < W; c++) {
			int &color = arr[r][c];
			numColors[color]++;
			if (numColors[color] == 1) {
				kindOfColors++;
			}
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
