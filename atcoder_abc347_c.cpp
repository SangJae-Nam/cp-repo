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

	int N, A, B;
	cin >> N >> A >> B;

	vector<int> D(N);
	for (int i = 0; i < N; i++) {
		cin >> D[i];
	}

	bool able = true;
	int left = 1;
	int right = A;
	int daysOfWeek = A + B;
	for (int i = 1; i < N; i++) {
		left += D[i] - D[i - 1];
		left %= daysOfWeek;

		right += D[i] - D[i - 1];
		right %= daysOfWeek;

		if (left > right) {
			swap(left, right);
		}

		if ((left > A) && (right > A)) {
			able = false;
			break;
		}

		right = (right > A) ? A : right;
	}

	if (able) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}

	return 0;
}
