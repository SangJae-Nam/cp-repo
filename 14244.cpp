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

	int n, m;
	cin >> n >> m;

	int leafs = (n - 1 == m) ? m : m - 1;
	for (int i = 0; i < leafs; i++) {
		cout << leafs << ' ' << i << '\n';
	}

	for (int i = leafs; i < n - 1; i++) {
		cout << i << ' ' << i + 1 << '\n';
	}

	return 0;
}
