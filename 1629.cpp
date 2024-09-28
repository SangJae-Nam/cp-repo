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

long long int exp_mod(long long int a, long long int b, long long int mod) // a^b % mod
{
	assert(b >= 0);
	long long int r = 1;
	while (b) {
		if (b & 1) {
			r = (r * a) % mod;
		}
		a = (a * a) % mod;
		b >>= 1;
	}

	return r;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int A, B, C;
	cin >> A >> B >> C;

	cout << exp_mod(A, B, C) << '\n';

	return 0;
}
