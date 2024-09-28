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

bool comp(const string &a, const string &b)
{
	size_t len = min(a.size(), b.size());
	for (size_t i = 0; i < len; i++) {
		if (a[i] != b[i]) {
			if (a[i] == '-') {
				return false;
			}
			else if (b[i] == '-') {
				return true;
			}
			else if (tolower(a[i]) == tolower(b[i])) {
				return a[i] < b[i];
			}
			else {
				return tolower(a[i]) < tolower(b[i]);
			}
		}
	}

	return a.size() < b.size();
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	vector<string> strings;

	while (nTestcases--) {
		int n;
		cin >> n;
		strings.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> strings[i];
		}
		sort(strings.begin(), strings.end(), comp);
		for (auto &s : strings) {
			cout << s << '\n';
		}
	}

	return 0;
}
