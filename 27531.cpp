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

class Solve {
private:
	int N;
	vector<tuple<int, int, int>> abp;

	int sum(vector<int> &indexes, int idx, bitset<200000> &used, int presum) {
		if (idx >= static_cast<int>(indexes.size())) {
			return presum;
		}

		if (static_cast<int>(indexes.size()) / 2 * 2 <= used.count()) {
			return presum;
		}

		auto [a, b, p] = abp[indexes[idx]];
		if (used[a] || used[b]) {
			return sum(indexes, idx + 1, used, presum);
		}

		int ret = sum(indexes, idx + 1, used, presum);

		used[a] = true;
		used[b] = true;
		ret = max(ret, sum(indexes, idx + 1, used, presum + p));
		used[a] = false;
		used[b] = false;

		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		abp.reserve(N);

		for (int i = 0; i < N; i++) {
			int a, b, p;
			cin >> a >> b >> p;
			abp.emplace_back(make_tuple(a-1, b-1, p));
		}
	}

	void solve() {
		UnionFind uf(N);
		int ret = 0;
		vector<int> aidx(N);
		vector<int> bidx(N);
		for (int i = 0; i < N; i++) {
			auto &[a, b, p] = abp[i];

			uf.unite(a, b);
			ret += p;
			aidx[a] = i;
			bidx[b] = i;
		}

		set<int> group[N];
		for (int i = 0; i < N; i++) {
			if (aidx[i] != bidx[i]) {
				int parent = uf.find(i);
				group[parent].insert(aidx[i]);
				group[parent].insert(bidx[i]);
			}
		}

		for (int k = 0; k < N; k++) {
			if (!group[k].size()) {
				continue;
			}
			vector<int> indexes(group[k].begin(), group[k].end());
			bitset<200000> usednum;
			ret -= sum(indexes, 0, usednum, 0);
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
	s.input();
	s.solve();

	return 0;
}

