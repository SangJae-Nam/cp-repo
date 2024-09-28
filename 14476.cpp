#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <cassert>
#include <numeric>

using namespace std;


int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;
	vector<int> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	vector<int> leftGCD(N);
	vector<int> rightGCD(N);

	leftGCD[0] = arr[0];
	for (int i = 1; i < N; i++) {
		leftGCD[i] = gcd(leftGCD[i - 1], arr[i]);
	}

	rightGCD[N - 1] = arr[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		rightGCD[i] = gcd(rightGCD[i + 1], arr[i]);
	}

	int maxGCD = -1;
	int maxGCDIdx = -1;
	int curGCD;

	curGCD = rightGCD[1];
	if ((arr[0] % curGCD != 0) && (maxGCD < curGCD)) {
		maxGCD = curGCD;
		maxGCDIdx = 0;
	}

	curGCD = leftGCD[N - 2];
	if ((arr[N - 1] % curGCD != 0) && (maxGCD < curGCD)) {
		maxGCD = curGCD;
		maxGCDIdx = N - 1;
	}

	for (int i = 1; i < N - 1; i++) {
		curGCD = gcd(leftGCD[i - 1], rightGCD[i + 1]);
		if ((arr[i] % curGCD != 0) && (maxGCD < curGCD)) {
			maxGCD = curGCD;
			maxGCDIdx = i;
		}
	}

	if (maxGCD != -1) {
		cout << maxGCD << ' ' << arr[maxGCDIdx] << '\n';
	}
	else {
		cout << -1 << '\n';
	}

	return 0;
}
