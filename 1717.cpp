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
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;

	UnionFind uf(n);
	for (int i = 0; i < m; i++) {
		int o, a, b;
		cin >> o >> a >> b;
		if (o == 0) {
			uf.unite(a, b);
		}
		else if (o == 1) {
			if (uf.same(a, b)) {
				cout << "YES\n";
			}
			else {
				cout << "NO\n";
			}
		}
	}

	return 0;
}
