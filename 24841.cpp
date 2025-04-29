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

class Solve {
private:
	int N;
	string S;
	map<string, int> palindrome;

	bool dfs(int idx) {
		if (idx >= N) {
			return true;
		}

		if (S[idx] == '?') {
			S[idx] = '0';
			if (dfs(idx)) {
				return true;
			}
			S[idx] = '1';
			if (dfs(idx)) {
				return true;
			}
            S[idx] = '?';
			return false;
		}

		if (idx < 4) {
			return dfs(idx + 1);
		}

		string s5 = S.substr(idx - 4, 5);
		if (palindrome[s5]) {
			return false;
		}
		
		if (idx > 4) {
			string s6 = S.substr(idx - 5, 6);
			if (palindrome[s6]) {
				return false;
			}
		}

		return dfs(idx + 1);
	}

public:
	Solve () {
		for (int i = 0; i < 32; i++) {
			bitset<5> b(i);
			string s = b.to_string();
			string t(s.rbegin(), s.rend());
			if (s == t) {
				palindrome[s] = 1;
			}
			else {
				palindrome[s] = 0;
			}
		}
		for (int i = 0; i < 64; i++) {
			bitset<6> b(i);
			string s = b.to_string();
			string t(s.rbegin(), s.rend());
			if (s == t) {
				palindrome[s] = 1;
			}
			else {
				palindrome[s] = 0;
			}
		}
	}

	void input() {
		cin >> N >> S;
	}

	bool solve() {
		if (N <= 4) {
			return true;
		}
		return dfs(0);
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;

	int nTestcases;
	cin >> nTestcases;
	for (int t = 1; t <= nTestcases; t++) {
		s.input();
		if (s.solve()) {
			cout << "Case #" << t << ": POSSIBLE\n";
		}
		else {
			cout << "Case #" << t << ": IMPOSSIBLE\n";
		}
	}

	return 0;
}

