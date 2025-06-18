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
	const int size;
	int N;
	string S;
	string T;

	vector<int> adj;

public:
	Solve () : size(26) {}

	void input() {
		cin >> N;
		cin >> S;
		cin >> T;
	}

	void solve() {
		adj.resize(size, -1);
		bool allSame = true;
		for (int i = 0; i < N; i++) {
			int s = S[i] - 'a';
			int t = T[i] - 'a';

			if (s != t) {
				allSame = false;
			}

			if (adj[s] == -1) {
				adj[s] = t;
			}
			else if (adj[s] != t) {
				cout << "-1\n";
				return;
			}
		}

		if (allSame) {
			cout << "0\n";
			return;
		}

		bool allUsed = true;
		vector<int> tmp(adj);
		sort(tmp.begin(), tmp.end());
		for (int i = 0; i < size; i++) {
			if (tmp[i] != i) {
				allUsed = false;
				break;
			}
		}
		if (allUsed) {
			cout << "-1\n";
			return;
		}

		int ret = 0;
		UnionFind uf(size);
		vector<int> indegree(size);
		for (int i = 0; i < size; i++) {
			if (adj[i] != -1) {
				if (adj[i] != i) {
					ret++;
					uf.unite(i, adj[i]);
					indegree[adj[i]]++;
				}
			}
		}

		map<int, vector<int>> groups;
		for (int i = 0; i < size; i++) {
			groups[uf.find(i)].push_back(i);
		}

		for (auto it = groups.begin(); it != groups.end(); it++) {
			if (it->second.size() > 1) {
				bool cycle = true;
				for (int n : it->second) {
					if (indegree[n] != 1) {
						cycle = false;
						break;
					}
				}

				if (cycle) {
					ret++;
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
	s.input();
	s.solve();

	return 0;
}
