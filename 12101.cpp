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

static int dp[12];
inline int f(int n)
{
	if (n >= 0) {
		return dp[n];
	}
	else {
		return 0;
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 4;
	for (int i = 4; i < 12; i++) {
		dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
	}

	int n, k;
	cin >> n >> k;

	vector<int> ret;
	while (n > 0 && k > 0) {
		if (k > f(n - 1) + f(n - 2) + f(n - 3)) {
			break;
		}
		else if (k > f(n - 1) + f(n - 2)) {
			ret.push_back(3);
			k -= f(n - 1) + f(n - 2);
			n -= 3;
		}
		else if (k > f(n - 1)) {
			ret.push_back(2);
			k -= f(n - 1);
			n -= 2;
		}
		else {
			ret.push_back(1);
			n--;
		}
	}

	if (ret.empty()) {
		cout << "-1\n";
	}
	else {
		for (int i = 0; i < ret.size() - 1; i++) {
			cout << ret[i] << '+';
		}
		cout << *ret.rbegin() << '\n';
	}
	
	return 0;
}
