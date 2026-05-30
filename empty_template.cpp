#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstring>
#include <bitset>
#include <queue>
#include <limits>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#ifdef __INPUT_AS_FILE_
#include <cstdio>
#endif


using namespace std;

class Solve {
private:
public:
	Solve () {}

	void input() {
	}

	void solve() {
	}
};

int main(int argc, char *argv[])
{
#ifndef __INPUT_AS_FILE_
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#else
	if (freopen("input_large.txt", "r", stdin) == NULL) {
		perror("freopen");
		exit(1);
	}
#endif

	Solve s;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
