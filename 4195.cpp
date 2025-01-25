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

class UnionFind
{
protected:
	vector<int> parent;
	vector<int> size;

public:
	UnionFind(int n) : parent(n + 1), size(n + 1, 1) {
		for (int i = 0; i <= n; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] == x) {
			return x;
		}

		return parent[x] = find(parent[x]);
	}

	bool same(int a, int b) {
		return find(a) == find(b);
	}

	void unite(int a, int b) {
		a = find(a);
		b = find(b);

		if (a == b) {
			return;
		}

		if (size[a] < size[b]) {
			swap(a, b);
		}

		parent[b] = a;
		size[a] += size[b];
	}

	int getSize(int x) {
		assert(x <= static_cast<int>(parent.size()));
		return size[find(x)];
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
		int F;
		cin >> F;

		UnionFind uf(F * 2);
		int iFriend = 0;
		unordered_map<string, int> friendIndex;

		for (int i = 0; i < F; i++) {
			string s1, s2;
			cin >> s1 >> s2;

			if (friendIndex.find(s1) == friendIndex.end()) {
				friendIndex[s1] = iFriend++;
			}
			if (friendIndex.find(s2) == friendIndex.end()) {
				friendIndex[s2] = iFriend++;
			}

			int &f1 = friendIndex[s1];
			int &f2 = friendIndex[s2];
			uf.unite(f1, f2);
			cout << uf.getSize(f1) << '\n';

		}
	}

	return 0;
}
