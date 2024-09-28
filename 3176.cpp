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

template <typename T5>
class SparseTableMin {
protected:
	vector<T5> &arr;
	vector<vector<int>> spt; //Sparse Table N * logN

	bool op(T5 &a, T5 &b) {
		return a < b;
	}

public:
	SparseTableMin(vector<T5> &_arr) : arr(_arr) {
		int size = static_cast<int>(arr.size());
		int log2size = static_cast<int>(ceil(log(static_cast<double>(size)) / log(2.0))) + 1;
		spt.resize(size, vector<int>(log2size));
		for (size_t i = 0; i < arr.size(); i++) {
			spt[i][0] = i;
		}

		for (int j = 1; (1<<j) <= size; j++) {
			for (int i = 0; i + (1<<j) - 1 < size; i++) {
				if (op(arr[spt[i][j - 1]], arr[spt[i + (1<<(j-1))][j - 1]])) {
					spt[i][j] = spt[i][j - 1];
				}
				else {
					spt[i][j] = spt[i + (1<<(j-1))][j - 1];
				}
			}
		}
	}

	int query(int i, int j) {
		if (i > j) {
			swap(i, j);
		}

		int k = static_cast<int>(floor(log(static_cast<double>(j - i + 1)) / log(2.0)));
		if (op(arr[spt[i][k]], arr[spt[j - (1<<k) + 1][k]])) {
			return spt[i][k];
		}
		else {
			return spt[j - (1<<k) + 1][k];
		}
	}
};

template <typename T5>
class SparseTableMax : public SparseTableMin<T5> {
protected:
	bool op(T5 &a, T5 &b) {
		return a > b;
	}

public:
	SparseTableMax(vector<T5> &_arr) : SparseTableMin<T5>(_arr) {}
};

// Least Common Ancester (최소공통조상)
class LCA
{
public:
	LCA(vector<vector<pair<int, int>>> &_adj, int root = 1) : adj(_adj) {
		ettDepth.reserve(adj.size() * 2);
		ettNode.reserve(adj.size() * 2);
		ettIndexTable.resize(adj.size(), -1);
		
		int size = static_cast<int>(adj.size());
		int log2Size = static_cast<int>(ceil(log(static_cast<double>(size)) / log(2.0))) + 1;
		parentTable.resize(size, vector<int>(log2Size, -1));
		minTable.resize(size, vector<int>(log2Size));
		maxTable.resize(size, vector<int>(log2Size));
		
		ettIdx = 0;
		dfs(-1, root, 1, 0);

		sparseTable = new SparseTableMin<int>(ettDepth);

		for (int i = 1; i < log2Size; i++) {
			for (int j = 0; j < size; j++) {
				if (parentTable[j][i - 1] == -1) {
					continue;
				}

				parentTable[j][i] = parentTable[parentTable[j][i - 1]][i - 1];
			}
		}

		for (int i = 1; i < log2Size; i++) {
			for (int j = 0; j < size; j++) {
				if (parentTable[j][i - 1] == -1) {
					continue;
				}

				minTable[j][i] = min(minTable[j][i - 1], minTable[parentTable[j][i - 1]][i -1]);
				maxTable[j][i] = max(maxTable[j][i - 1], maxTable[parentTable[j][i - 1]][i -1]);
			}
		}

	}

	virtual ~LCA() {
		delete sparseTable;
	}

	int getLCA(int a, int b) {
		int idxA = ettIndexTable[a];
		int idxB = ettIndexTable[b];

		if (idxA > idxB) {
			swap(idxA, idxB);
		}

		int idxLCA = sparseTable->query(idxA, idxB);
		return ettNode[idxLCA];
	}

	pair<int, int> getMinMax(int a, int b) {
		if (a == b) {
			return make_pair(0, 0);
		}

		int parent = getLCA(a, b);
		auto left = _getMinMax(parent, a);
		auto right = _getMinMax(parent, b);

		return make_pair(min(left.first, right.first), max(left.second, right.second));
	}

	void printETT() {
		for (auto n : ettNode) {
			cout << n << ' ';
		}
		cout << endl;
		for (auto n : ettDepth) {
			cout << n << ' ';
		}
		cout << endl;
	}

protected:
	vector<vector<pair<int, int>>> &adj;
	
	//Euler Tour Tree
	vector<int> ettDepth;
	vector<int> ettNode;
	vector<int> ettIndexTable;
	SparseTableMin<int> *sparseTable;

	vector<vector<int>> parentTable;
	vector<vector<int>> maxTable;
	vector<vector<int>> minTable;

	int ettIdx;
	void dfs(int prev, int cur, int depth, int length) {
		ettDepth.push_back(depth);
		ettNode.push_back(cur);
		if (ettIndexTable[cur] == -1) {
			ettIndexTable[cur] = ettIdx;
		}
		ettIdx++;

		parentTable[cur][0] = prev;
		minTable[cur][0] = length;
		maxTable[cur][0] = length;

		for (auto &n : adj[cur]) {
			int &next = n.first;
			int &nextLength = n.second;
			if (next == prev) {
				continue;
			}

			dfs(cur, next, depth + 1, nextLength);
		
			ettDepth.push_back(depth);
			ettNode.push_back(cur);
			ettIdx++;
		}
	}

	pair<int, int> _getMinMax(int a, int b) {
		// depth a < b
		if (a == b) {
			return make_pair(999999999, -1);
		}

		int depthA = ettDepth[ettIndexTable[a]];
		int depthB = ettDepth[ettIndexTable[b]];
		int depthDiff = depthB - depthA;

		int cur = b;
		int mx = -1;
		int mn = 999999999;;
		while (depthDiff) {
			int n = 0;
			for (; n < 32; n++) {
				if ((1<<n) > depthDiff) {
					break;
				}
			}
			n--;

			mn = min(mn, minTable[cur][n]);
			mx = max(mx, maxTable[cur][n]);

			depthDiff -= (1<<n);
			cur = parentTable[cur][n];
		}

		return make_pair(mn, mx);
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<vector<pair<int, int>>> adj(N + 1);

	for (int i = 0; i < N - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		adj[a].push_back(make_pair(b, c));
		adj[b].push_back(make_pair(a, c));
	}

	LCA lca(adj);

	int K;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int d, e;
		cin >> d >> e;

		auto minmax = lca.getMinMax(d, e);
		cout << minmax.first << ' ' << minmax.second << '\n';
	}

	return 0;
}
