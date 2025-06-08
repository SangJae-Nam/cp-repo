#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <array>
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

// n!에서 prime은 몇 제곱을 갖고 있는지 구함
int primeExpInFact(int n, int prime)
{
	int exp = 0;
	while (n > 0) {
		n /= prime;
		exp += n;
	}
	return exp;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;

	int exp2 = primeExpInFact(n, 2) - primeExpInFact(m, 2) - primeExpInFact(n - m, 2);
	int exp5 = primeExpInFact(n, 5) - primeExpInFact(m, 5) - primeExpInFact(n - m, 5);

	cout << min(exp2, exp5) << '\n';

	return 0;
}
