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
	vector<vector<int>> adj;
	string name;
	int root;
	int goodPathCount;
	int goodPathLength;

	void _updateResult(int len, int count) {
		if (len == goodPathLength) {
			goodPathCount += count;
		}
		else if (len > goodPathLength) {
			goodPathLength = len;
			goodPathCount = count;
		}
	}

	pair<int, int> _solve(int node) {
		int sonsLen = static_cast<int>(adj[node].size());

		vector<pair<int, int>> sonLengths;
		sonLengths.reserve(sonsLen);
		vector<int> &sons = adj[node];
		for (int i = 0; i < sonsLen; i++) {
			sonLengths.push_back(_solve(sons[i]));
		}

		// return value : 자신까지의 최대 길이, 개수
		int length = 1; // 자기자신
		int count = 1;
		_updateResult(length, count);
		for (int i = 0; i < sonsLen; i++) {
			int &sonLength = sonLengths[i].first;
			int &sonCount = sonLengths[i].second;
			if (name[sons[i]] != name[node]) {
				if (sonLength + 1 > length) {
					length = sonLength + 1;
					count = sonCount;
				}
				else if (sonLength + 1 == length) {
					count += sonCount;
				}
				_updateResult(length, count);

				for (int j = i + 1; j < sonsLen; j++) {
					if (name[sons[j]] != name[node]) {
						int l = sonLength + 1 + sonLengths[j].first;
						int c = sonCount * sonLengths[j].second;
						_updateResult(l, c);
					}
				}
			}
		}

		return make_pair(length, count);
	}

public:
	void input() {
		int n;
		cin >> n >> name;

		adj.resize(n);
		for (auto &son : adj) {
			son.clear();
		}

		for (int i = 0; i < n; i++) {
			int p;
			cin >> p;
			p--;

			if (p != -1) {
				adj[p].push_back(i);
			}
			else {
				root = i;
			}
		}
	}

	void solve() {
		goodPathCount = 0;
		goodPathLength = 0;
		_solve(root);

		cout << goodPathLength << ' ' << goodPathCount << '\n';
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
