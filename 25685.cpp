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
#include <cstring>

using namespace std;

using Node = pair<int, vector<int>>;
vector<Node> nodes;
long long int dp[100000 + 1][2];

long long int solve(int idx, int selected)
{
	long long int &ret = dp[idx][selected];
	if (ret != -1) {
		return ret;
	}
	ret = 0;

	if (selected) {
		ret += nodes[idx].first;
		for (int son : nodes[idx].second) {
			ret += solve(son, 0);
		}
	}
	else {
		bool subSelected = false;
		long long int subRet;
		long long int subRetNotSel;
		long long int maxRet = numeric_limits<long long int>::min();
		for (int son : nodes[idx].second) {
			subRet = solve(son, 1);
			subRetNotSel = solve(son, 0);

			if (subRet >= subRetNotSel) {
				ret += subRet;
				subSelected = true;
			}
			else {
				ret += subRetNotSel;
				maxRet = max(maxRet, subRet - subRetNotSel);
			}
		}

		if (!subSelected && nodes[idx].second.size() > 0) {
			ret += maxRet;
		}
	}

	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int n;
		cin >> n;
		nodes.resize(n + 1);

		for (int i = 1; i <= n; i++) {
			cin >> nodes[i].first;
			nodes[i].second.clear();
		}

		int root;
		for (int i = 1; i <= n; i++) {
			int p;
			cin >> p;
			nodes[p].second.push_back(i);
			if (p == 0) {
				root = i;
			}
		}

		memset(dp, -1, sizeof(dp));
		cout << max(solve(root, 0), solve(root, 1)) << '\n';
	}

	return 0;
}
