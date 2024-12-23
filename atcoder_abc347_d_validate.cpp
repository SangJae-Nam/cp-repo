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

	int a, b;
	unsigned long long int c;
	cin >> a >> b >> c;

	int xorbits = __builtin_popcountll(c);
	int commonNumBits = -1;

	for (int i = 0; i <= xorbits; i++) {
		int aremain = a - i;
		int bremain = b - (xorbits - i);
		if (aremain < 0 || bremain < 0) {
			continue;
		}

		if (aremain == bremain) {
			commonNumBits = aremain;
			break;
		}
	}

	if (commonNumBits == -1) {
		cout << "-1\n";
	}
	else {
		unsigned long long int reta = 0;
		unsigned long long int retb = 0;

		int abits = a - commonNumBits;
		int bbits = b - commonNumBits;

		for (int i = 0; xorbits > 0; i++) {
			if ((c & (1ull<<i)) != 0) {
				if (abits > 0) {
					reta |= (1ull<<i);
					abits--;
				}
				else {
					retb |= (1ull<<i);
					bbits--;
				}
				xorbits--;
			}
		}

		for (int i = 62; commonNumBits > 0; i--) {
			if ((c & (1ull<<i)) == 0) {
				reta |= (1ull<<i);
				retb |= (1ull<<i);
				commonNumBits--;
			}
		}

		cout << reta << ' ' << retb << '\n';
	}

	return 0;
}
