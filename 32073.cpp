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

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int N;
		string s;

		cin >> N >> s;

		int iFirstOne = -1;
		for (int i = 0; i < N; i++) {
			if (s[i] == '1') {
				iFirstOne = i;
				break;
			}
		}

		if (iFirstOne == -1) {
			cout << "0\n";
			continue;
		}

		string ret;
		ret.reserve(N - iFirstOne);
		int iFirstZero = -1;
		for (int i = iFirstOne; i < N; i++) {
			if (s[i] == '0') {
				iFirstZero = i;
				break;
			}
			ret += '1';
		}

		if (iFirstZero == -1) {
			if (iFirstOne == 0) {
				ret[ret.size() - 1] = '0';
			}
		}
		else {
			int start = iFirstOne;
			for (int i = 0; i < iFirstZero - iFirstOne; i++) {
				if (s[i + iFirstZero] != '0') {
					start = iFirstZero - i;
					break;
				}
			}

			for (int i = iFirstZero; i < N; i++) {
				ret += (s[i] == s[start + i - iFirstZero]) ? '0' : '1';
			}
		}

		cout << ret << '\n';
	}

	return 0;
}
