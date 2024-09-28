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

	int N;
	cin >> N;
	vector<pair<int, int>> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
	sort(arr.begin(), arr.end());

	int maxLeft = 0;
	for (int i = 0; i < N; i++) {
		if (arr[i].second > i) {
			maxLeft = max(maxLeft, arr[i].second - i);
		}
	}
	cout << maxLeft + 1 << '\n';

	return 0;
}

/*
//반례 : 1 2 0 2 1
//1 0 2 1 2
0 1 1 2 2
2 0 5 1 3
*/
