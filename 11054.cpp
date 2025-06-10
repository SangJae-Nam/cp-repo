#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <array>
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

class LIS {
private:
public:
	vector<int> lengths;

	void make(const vector<int> &input, bool makeLengthArr = false) {
		int size = static_cast<int>(input.size());

		if (makeLengthArr) {
			lengths.resize(size);
		}

		vector<int> lis;
		lis.reserve(size);
		for (int i = 0; i < size; i++) {
			auto it = lower_bound(lis.begin(), lis.end(), input[i]);
			if (it == lis.end()) {
				lis.push_back(input[i]);
				if (makeLengthArr) {
					lengths[i] = static_cast<int>(lis.size());
				}
			}
			else {
				*it = input[i];
				if (makeLengthArr) {
					lengths[i] = static_cast<int>(it - lis.begin()) + 1;
				}
			}
		}
	}
};

class Solve {
private:
	int N;
	vector<int> D;
	vector<int> DRev;

public:
	Solve () {}

	void input() {
		cin >> N;
		D.resize(N);
		DRev.resize(N);

		for (int i = 0; i < N; i++) {
			cin >> D[i];
			DRev[N - 1 - i] = D[i];
		}
	}

	void solve() {
		LIS lis1, lis2;
		lis1.make(D, true);
		lis2.make(DRev, true);

		int maxLen = 0;
		for (int i = 0; i < N; i++) {
			int front = lis1.lengths[i];
			int end = lis2.lengths[N - 1 - i];
			int len = front + end - 1;
			maxLen = max(len, maxLen);
		}
		cout << maxLen << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;
	s.input();
	s.solve();

	return 0;
}
