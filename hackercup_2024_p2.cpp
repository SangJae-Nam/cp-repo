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

	cout << fixed;
	cout.precision(18);

	int nTestcases;
	cin >> nTestcases;
	for (int t = 1; t <= nTestcases; t++) {
		int N, P;
		cin >> N >> P;

		long double c1 = pow(P / 100.0l, N - 1);
		c1 = pow(c1, 1.0l / N);
		c1 *= 100;
		c1 -= P;

		cout << "Case #" << t << ": " << c1 << '\n';
	}

	return 0;
}
