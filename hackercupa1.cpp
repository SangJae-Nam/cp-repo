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

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	for (int t = 1; t <= nTestcases; t++) {
		int S, D, K;
		cin >> S >> D >> K;

		int numBurns = S * 2 + D * 2;
		int numPatties = S + D * 2;

		if (numPatties >= K && numBurns >= K + 1) {
			cout << "Case #" << t << ": YES" << '\n';
		}
		else {
			cout << "Case #" << t << ": NO" << '\n';
		}
	}

	return 0;
}
