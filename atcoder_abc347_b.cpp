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

	string S;
	cin >> S;

	set<string> ss;
	for (int len = 1; len <= static_cast<int>(S.size()); len++) {
		for (int j = 0; j <= static_cast<int>(S.size()) - len; j++) {
			ss.insert(S.substr(j, len));
		}
	}

	cout << ss.size() << '\n';

	return 0;
}
