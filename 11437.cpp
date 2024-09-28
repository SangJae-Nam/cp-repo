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

// Least Common Ancester (최소공통조상)
class LCA
{
public:
	LCA(vector<vector<int>> &_adj, int root = 1) : adj(_adj) {
		ettDepth.reserve(adj.size() * 2);
		ettNode.reserve(adj.size() * 2);
		ettIndexTable.resize(adj.size(), -1);
		ettIdx = 0;
		dfs(-1, root, 1);

		sparseTable = new SparseTableMin<int>(ettDepth);
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
	vector<vector<int>> &adj;
	
	//Euler Tour Tree
	vector<int> ettDepth;
	vector<int> ettNode;
	vector<int> ettIndexTable;

	SparseTableMin<int> *sparseTable;

	int ettIdx;
	void dfs(int prev, int cur, int depth) {
		ettDepth.push_back(depth);
		ettNode.push_back(cur);
		if (ettIndexTable[cur] == -1) {
			ettIndexTable[cur] = ettIdx;
		}
		ettIdx++;

		for (int next : adj[cur]) {
			if (next == prev) {
				continue;
			}

			dfs(cur, next, depth + 1);
		
			ettDepth.push_back(depth);
			ettNode.push_back(cur);
			ettIdx++;
		}
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<vector<int>> adj;
	int N;
	cin >> N;
	adj.resize(N + 1);

	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	LCA lca(adj);

	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;

		cout << lca.getLCA(a, b) << '\n';
	}

	return 0;
}
