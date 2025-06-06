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

pair<long long int, long long int> cal(const vector<long long int> &prefixSum, long long int len, long long int count)
{
	long long int maxVal = 0;
	long long int minVal = 0;

	int N = static_cast<int>(prefixSum.size()) - 1;
	minVal = prefixSum[count] * len;
	maxVal = (prefixSum[N] - prefixSum[N - count]) * len;

	return make_pair(minVal, maxVal);
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int M, N;
	cin >> N >> M;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	sort(A.begin(), A.end());
	vector<long long int> prefixSum(N + 1);
	for (int i = 1; i <= N; i++) {
		prefixSum[i] = prefixSum[i - 1] + A[i - 1];
	}

	constexpr int START = 1;
	constexpr int END = 2;
	map<pair<int, int>, int> points; // (point, start/end), count
	for (int i = 0; i < M; i++) {
		int s, e;
		cin >> s >> e;
		points[make_pair(s, START)]++;
		points[make_pair(e, END)]++;
	}

	long long int minVal = 0;
	long long int maxVal = 0;
	long long int count = 0;
	long long int cur = -1;
	for (auto it = points.begin(); it != points.end(); it++) {
		if (count == 0) {
			assert(it->first.second == START);
			cur = it->first.first;
			count = it->second;
		}
		else {
			if (it->first.second == START) {
				auto c = cal(prefixSum, it->first.first - cur, count);
				minVal += c.first;
				maxVal += c.second;

				cur = it->first.first;
				count += it->second;
			}
			else {
				auto c = cal(prefixSum, it->first.first - cur + 1, count);
				minVal += c.first;
				maxVal += c.second;

				cur = it->first.first + 1;
				count -= it->second;
			}
		}
	}
	assert(count == 0);

	cout << minVal << ' ' << maxVal << '\n';

	return 0;
}
