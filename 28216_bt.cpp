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

	constexpr int LEN = 1001;
	vector<vector<int>> arr(LEN, vector<int>(LEN));

	for (int i = 0; i < N; i++) {
		int x, y, w;
		cin >> x >> y >> w;

		arr[y][x] = w;
	}

	int x = 1, y = 1;
	long long int ret = 0;
	for (int q = 0; q < Q; q++) {
		int d, v;
		cin >> d >> v;

		int nx = x, ny = y;
		if (d == 0) {
			nx += v;
			for (int xx = x + 1; xx <= nx; xx++) {
				ret += arr[y][xx];
			}
		}
		else if (d == 1) {
			ny += v;
			for (int yy = y + 1; yy <= ny; yy++) {
				ret += arr[yy][x];
			}
		}
		else if (d == 2) {
			nx -= v;
			for (int xx = x - 1; xx >= nx; xx--) {
				ret += arr[y][xx];
			}
		}
		else if (d == 3) {
			ny -= v;
			for (int yy = y - 1; yy >= ny; yy--) {
				ret += arr[yy][x];
			}
		}

		x = nx;
		y = ny;
	}

	cout << ret << '\n';

	return 0;
}
