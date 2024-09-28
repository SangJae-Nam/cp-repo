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

static int N, M, K;

constexpr int XSUM = 1;
constexpr int YSUM = 2;
constexpr int PSUM = 3;//말의 개수

void makePrefixSum(vector<string> &src, char target, int kind, vector<vector<int>> &dst)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int val;
			switch (kind) {
				case XSUM:
					val = i + 1;
					break;
				case YSUM:
					val = j + 1;
					break;
				case PSUM:
					val = 1;
					break;
			}

			if (src[i][j] == target) {
				dst[i+1][j+1] = dst[i+1][j] + val;
			}
			else {
				dst[i+1][j+1] = dst[i+1][j];
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			dst[i][j] += dst[i - 1][j];
		}
	}
}

int sum(int x1, int y1, int x2, int y2, const vector<vector<int>> &prefixSum)
{
	assert(x1 <= x2 && y1 <= y2);
	return prefixSum[x2][y2] - prefixSum[x2][y1 - 1] - prefixSum[x1 - 1][y2] + prefixSum[x1 - 1][y1 - 1];
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M >> K;
	vector<string> arr(N);

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	vector<vector<int>> prefixSum1X(N+1, vector<int>(M+1));
	vector<vector<int>> prefixSum1Y(N+1, vector<int>(M+1));
	vector<vector<int>> prefixSum1P(N+1, vector<int>(M+1));
	vector<vector<int>> prefixSum2X(N+1, vector<int>(M+1));
	vector<vector<int>> prefixSum2Y(N+1, vector<int>(M+1));
	vector<vector<int>> prefixSum2P(N+1, vector<int>(M+1));

	makePrefixSum(arr, '1', XSUM, prefixSum1X);
	makePrefixSum(arr, '1', YSUM, prefixSum1Y);
	makePrefixSum(arr, '1', PSUM, prefixSum1P);
	makePrefixSum(arr, '2', XSUM, prefixSum2X);
	makePrefixSum(arr, '2', YSUM, prefixSum2Y);
	makePrefixSum(arr, '2', PSUM, prefixSum2P);

	int ret = numeric_limits<int>::max();
	for (int i = 1; i <= N - K + 1; i++) {
		int mx = i + (K - 1) / 2;
		for (int j = 1; j <= M - K + 1; j++) {
			int my = j + (K - 1) / 2;

			//LU
			int s1 = -sum(i, j, mx, my, prefixSum1X);
			s1 += sum(i, j, mx, my, prefixSum1P) * mx;
			s1 += -sum(i, j, mx, my, prefixSum1Y);
			s1 += sum(i, j, mx, my, prefixSum1P) * my;

			//RU
			if (M > 1 && K > 1) {
				s1 += -sum(i, my + 1, mx, j + K - 1, prefixSum1X);
				s1 += sum(i, my + 1, mx, j + K - 1, prefixSum1P) * mx;
				s1 += sum(i, my + 1, mx, j + K - 1, prefixSum1Y);
				s1 += -sum(i, my + 1, mx, j + K - 1, prefixSum1P) * my;
			}

			//LD
			if (N > 1 && K > 1) {
				s1 += sum(mx + 1, j, i + K - 1, my, prefixSum1X);
				s1 += -sum(mx + 1, j, i + K - 1, my, prefixSum1P) * mx;
				s1 += -sum(mx + 1, j, i + K - 1, my, prefixSum1Y);
				s1 += sum(mx + 1, j, i + K - 1, my, prefixSum1P) * my;
			}

			//RD
			if (M > 1 && N > 1 && K > 1) {
				s1 += sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum1X);
				s1 += -sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum1P) * mx;
				s1 += sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum1Y);
				s1 += -sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum1P) * my;
			}

			//LU
			int s2 = -sum(i, j, mx, my, prefixSum2X);
			s2 += sum(i, j, mx, my, prefixSum2P) * mx;
			s2 += -sum(i, j, mx, my, prefixSum2Y);
			s2 += sum(i, j, mx, my, prefixSum2P) * my;

			//RU
			if (M > 1 && K > 1) {
				s2 += -sum(i, my + 1, mx, j + K - 1, prefixSum2X);
				s2 += sum(i, my + 1, mx, j + K - 1, prefixSum2P) * mx;
				s2 += sum(i, my + 1, mx, j + K - 1, prefixSum2Y);
				s2 += -sum(i, my + 1, mx, j + K - 1, prefixSum2P) * my;
			}

			//LD
			if (N > 1 && K > 1) {
				s2 += sum(mx + 1, j, i + K - 1, my, prefixSum2X);
				s2 += -sum(mx + 1, j, i + K - 1, my, prefixSum2P) * mx;
				s2 += -sum(mx + 1, j, i + K - 1, my, prefixSum2Y);
				s2 += sum(mx + 1, j, i + K - 1, my, prefixSum2P) * my;
			}

			//RD
			if (M > 1 && N > 1 && K > 1) {
				s2 += sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum2X);
				s2 += -sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum2P) * mx;
				s2 += sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum2Y);
				s2 += -sum(mx + 1, my + 1, i + K - 1, j + K - 1, prefixSum2P) * my;
			}

			ret = min(ret, abs(s1 - s2));
		}
	}

	cout << ret << '\n';

	return 0;
}
