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

long long int solve(int beg, int end, const vector<int> &cols)
{
	if (beg == end) {
		return cols[beg];
	}

	int mid = (beg + end) / 2;
	// 좌, 우 중에 답이 있는 경우
	long long int ret = max(solve(beg, mid, cols), solve(mid + 1, end, cols));

	// 걸치는 경우
	int l = mid;
	int r = mid + 1;
	int height = min(cols[mid], cols[mid + 1]);

	while (true) {
		long long int width = r - l + 1;
		ret = max(ret, width * height);

		if (l > beg && r < end) {
			if (cols[l - 1] > cols[r + 1]) {
				height = min(height, cols[--l]);
			}
			else {
				height = min(height, cols[++r]);
			}
		}
		else if (l > beg) {
			height = min(height, cols[--l]);
		}
		else if (r < end) {
			height = min(height, cols[++r]);
		}
		else {
			break;
		}
	}

	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<int> cols(N);
	for (int i = 0; i < N; i++) {
		cin >> cols[i];
	}

	cout << solve(0, N - 1, cols) << '\n';

	return 0;
}
