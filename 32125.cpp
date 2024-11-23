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

class Solve
{
private:
	int N, K;
	vector<int> C;
	vector<int> W;

	map<int, vector<long long int>> candidates;

public:
	Solve() {}
	void input() {
		cin >> N >> K;

		C.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> C[i];
		}
		W.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> W[i];
		}
	}
	void solve() {
		int prefixC = 0;
		long long int prefixW = 0;
		candidates[0].push_back(0);
		for (int i = 1; i <= N; i++) {
			prefixC += (C[i - 1] == 2) ? -1 : 1;
			prefixW += (C[i - 1] == 2) ? -W[i - 1] : W[i - 1];

			candidates[prefixC].push_back(prefixW);
		}

		long long int ret = 0;
		for (auto &x : candidates) {
			auto &key = x.first;
			auto &value = x.second;
			if (value.size() >= 2) {
				sort(value.begin(), value.end());
				for (int left = 0; left < static_cast<int>(value.size()) - 1; left++) {
					auto rit = upper_bound(value.begin() + left + 1, value.end(), K + value[left]);
					int right;
					if (rit != value.end()) {
						right = static_cast<int>(rit - value.begin()) - 1;
					}
					else {
						right = static_cast<int>(value.size()) - 1;
					}
					ret += (right - left);
				}
			}
		}

		cout << ret << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		Solve s;
		s.input();
		s.solve();
	}

	return 0;
}

