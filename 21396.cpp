#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solve {
private:
	int N, X;
	unordered_map<int, int> V;

public:
	Solve () {}

	void input() {
		V.clear();
		cin >> N >> X;
		for (int i = 0; i < N; i++) {
			int n;
			cin >> n;
			V[n]++;
		}
	}

	void solve() {
		long long int ret = 0;
		unordered_set<int> used;
		for (auto it = V.begin(); it != V.end(); it++) {
			const int &key = it->first;
			const int &value = it->second;

			if (used.find(key) != used.end()) {
				continue;
			}

			used.insert(key);
			int target = key ^ X;
			if (target == key) {
				ret += 1ll * value * (value - 1) / 2;
			}
			else {
				if (V.find(target) != V.end()) {
					ret += 1ll * value * V[target];
					used.insert(target);
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

	Solve s;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
