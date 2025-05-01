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
	unordered_map<string, bool> palindrome;

public:
	Solve () {
		for (int i = 0; i < 32; i++) {
			bitset<5> b(i);
			string s = b.to_string();
			string t(s.rbegin(), s.rend());
			if (s == t) {
				palindrome[s] = true;
			}
			else {
				palindrome[s] = false;
			}
		}
		for (int i = 0; i < 64; i++) {
			bitset<6> b(i);
			string s = b.to_string();
			string t(s.rbegin(), s.rend());
			if (s == t) {
				palindrome[s] = true;
			}
			else {
				palindrome[s] = false;
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

		queue<string> q[2];
		q[0].push(string());

		for (int i = 0; i < N; i++) {
			queue<string> &curq = q[i%2];
			queue<string> &nextq = q[(i+1) % 2];
			if (curq.empty()) {
				return false;
			}

			while (!curq.empty()) {
				string pre = curq.front();
				curq.pop();

				if (pre.size() < 4) {
					if (S[i] == '0' || S[i] == '?') {
						nextq.push(pre + "0");
					}
					if (S[i] == '1' || S[i] == '?') {
						nextq.push(pre + "1");
					}
				}
				else {
					if (pre.size() == 4) {
						if (S[i] == '0' || S[i] == '?') {
							if (!palindrome[pre + "0"]) {
								nextq.push(pre + "0");
							}
						}
						if (S[i] == '1' || S[i] == '?') {
							if (!palindrome[pre + "1"]) {
								nextq.push(pre + "1");
							}
						}
					}
					else {
						if (S[i] == '0' || S[i] == '?') {
							if (!palindrome[pre.substr(1) + "0"] && !palindrome[pre + "0"]) {
								nextq.push(pre.substr(1) + "0");
							}
						}
						if (S[i] == '1' || S[i] == '?') {
							if (!palindrome[pre.substr(1) + "1"] && !palindrome[pre + "1"]) {
								nextq.push(pre.substr(1) + "1");
							}
						}
					}
				}
			}
		}

		return !q[N % 2].empty();
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

