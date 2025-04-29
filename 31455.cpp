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

class PrefixSum2D {
private:
	int row;
	int col;
	vector<vector<long long int>> arr;

public:
	PrefixSum2D() {}

	//좌표는 1부터 시작
	void init(vector<vector<int>> &input) {
		row = static_cast<int>(input.size());
		col = static_cast<int>(input[0].size());

		arr.resize(row);
		for (int r = 0; r < row; r++) {
			arr[r].resize(col);
			for (int c = 1; c < col; c++) {
				arr[r][c] += arr[r][c - 1] + input[r][c];
			}
		}

		for (int c = 0; c < col; c++) {
			for (int r = 1; r < row; r++) {
				arr[r][c] += arr[r - 1][c];
			}
		}
	}

	long long int sum(int x1, int y1, int x2, int y2) {
		assert(x1 <= x2 && y1 <= y2);

		long long int ret = arr[y2][x2];
		ret -= arr[y2][x1 - 1];
		ret -= arr[y1 - 1][x2];
		ret += arr[y1 - 1][x1 - 1];

		return ret;
	}
};

class Solve {
private:
	int N;
	vector<vector<int>> A;
	PrefixSum2D prefixSum;

	long long int run(int sx, int sy, int ex, int ey) {
		if (sx == ex && sy == ey) {
			return A[sy][sx];
		}

		int mx = ((ex - sx + 1) / 2) + sx;
		int my = ((ey - sy + 1) / 2) + sy;

		long long int ret = 0;
		long long int sum = prefixSum.sum(sx, sy, ex, ey);
		switch (sum % 4) {
			case 0:
				ret += run(mx, sy, ex, my - 1);//1
				ret += run(sx, my, mx - 1, ey);//2
				ret += run(mx, my, ex, ey);//3
				break;

			case 1:
				ret += run(sx, sy, mx - 1, my - 1);//0
				ret += run(sx, my, mx - 1, ey);//2
				ret += run(mx, my, ex, ey);//3
				break;

			case 2:
				ret += run(sx, sy, mx - 1, my - 1);//0
				ret += run(mx, sy, ex, my - 1);//1
				ret += run(mx, my, ex, ey);//3
				break;

			case 3:
				ret += run(sx, sy, mx - 1, my - 1);//0
				ret += run(mx, sy, ex, my - 1);//1
				ret += run(sx, my, mx - 1, ey);//2
				break;
		}

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		A.resize(N + 1, vector<int>(N + 1));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				char ch;
				cin >> ch;
				A[i][j] = ch - '0';
			}
		}
	}

	void solve() {
		prefixSum.init(A);
		cout << run(1, 1, N, N) << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		Solve s;
		s.input();
		s.solve();
	}

	return 0;
}
