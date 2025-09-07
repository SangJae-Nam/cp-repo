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

int run(long long int num, const long long int target)
{
	if (num == target) {
		return 0;
	}
	else if (num > target) {
		return -1;
	}

	int ret1 = run(num * 2, target);
	int ret2 = run(num * 10 + 1, target);
	if (ret1 == -1 && ret2 == -1) {
		return -1;
	}
	else if (ret1 == -1) {
		return ret2 + 1;
	}
	else if (ret2 == -1) {
		return ret1 + 1;
	}
	else {
		return min(ret1, ret2) + 1;
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int A, B;
	cin >> A >> B;

	int ret = run(A, B);
	if (ret == -1) {
		cout << "-1\n";
	}
	else {
		cout << ret + 1 << '\n';
	}

	return 0;
}
