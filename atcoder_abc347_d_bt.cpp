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

	for (unsigned long long int x = 0; x < 1000; x++) {
		for (unsigned long long int y = 0; y < 1000; y++) {
			int xbits = __builtin_popcountll(x);
			int ybits = __builtin_popcountll(y);

			if (xbits == a && ybits == b && (x ^ y) == c) {
				cout << x << ' ' << y << '\n';
				return 0;
			}
		}
	}

	cout << "-1\n";
	return 0;
}
