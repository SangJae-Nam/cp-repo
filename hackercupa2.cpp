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
		long long int A, B, C;
		cin >> A >> B >> C;

		long long int maxK = 0;
		if (B <= A) {
			maxK = (C / B) * 2 - 1;
			maxK = (maxK >= 0) ? maxK : 0;
		}
		else {
			long long int b;
			for (long long int a = 0, i = 0; a * A <= C && i <= 10000; a++, i++) {
				b = (C - a*A) / B;
				if (C - (a*A + b*B) >= min(A, B)) {
					a = (C - b*B) / A;
					a--;
					continue;
				}

				long long int nb = a * 2 + b * 2;
				long long int np = a + b * 2;

				long long int m = (nb >= np + 1) ? np : nb - 1;
				maxK = max(maxK, m);
				//cout << a << ", " << b << ": " << m << endl;
			}
		}
		cout << "Case #" << t << ": " << maxK << '\n';
	}

	return 0;
}
