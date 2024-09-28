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

constexpr int CIRCLE = 11;
constexpr int LINE = 22;

class UnionFind1139 : public UnionFind
{
protected:
	vector<int> degrees;
	vector<int> vertexes;
	vector<bool> degreeUnder2;
	vector<char> shapes;

	int numCircles;
	int numLines;

public:
	UnionFind1139(int n) : UnionFind(n), degrees(n + 1), vertexes(n + 1), degreeUnder2(n + 1, true), shapes(n + 1), numCircles(0), numLines(0) {
	}

	void addVertex(int a, int b) {
		degrees[a]++;
		degrees[b]++;

		if (degrees[a] > 2) {
			degreeUnder2[a] = false;
			degreeUnder2[find(a)] = false;
		}

		if (degrees[b] > 2) {
			degreeUnder2[b] = false;
			degreeUnder2[find(b)] = false;
		}
		bool newDegreeUnder2 = degreeUnder2[find(a)] && degreeUnder2[find(b)];

		if (shapes[find(a)] == CIRCLE) {
			shapes[find(a)] = 0;
			numCircles--;
		}
		else if (shapes[find(a)] == LINE) {
			shapes[find(a)] = 0;
			numLines--;
		}

		int beforeVertexes = vertexes[find(a)];
		if (!same(a, b)) {
			beforeVertexes += vertexes[find(b)];
			if (shapes[find(b)] == CIRCLE) {
				shapes[find(b)] = 0;
				numCircles--;
			}
			else if (shapes[find(b)] == LINE) {
				shapes[find(b)] = 0;
				numLines--;
			}
		}

		unite(a, b);

		int newA = find(a);
		vertexes[newA] = beforeVertexes + 1;
		degreeUnder2[newA] = newDegreeUnder2;

		if (degreeUnder2[newA]) {
			if (vertexes[newA] + 1 == size[newA]) {
				shapes[newA] = LINE;
				numLines++;
			}
			else if (vertexes[newA] == size[newA]) {
				shapes[newA] = CIRCLE;
				numCircles++;
			}
		}
	}

	int getDiff() {
		return abs(numCircles - numLines);
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	vector<pair<int, pair<int, int>>> vertexes(M);

	for (int i = 0; i < M; i++) {
		int X, Y, W;
		cin >> X >> Y >> W;

		vertexes[i].first = W;
		vertexes[i].second.first = X;
		vertexes[i].second.second = Y;
	}
	sort(vertexes.begin(), vertexes.end());

	int K = -1;
	int minK = vertexes[M - 1].first;
	int minDiff = 1 << 30;
	UnionFind1139 starSet(N);
	for (int i = M - 1; i >= 0; i--) {
		int &w = vertexes[i].first;
		if (K != -1 && K != w) {
			int diff = starSet.getDiff();
			if (diff <= minDiff) {
				minK = K;
				minDiff = diff;
			}
		}

		int &x = vertexes[i].second.first;
		int &y = vertexes[i].second.second;
		starSet.addVertex(x, y);
		K = w;
	}

	int diff = starSet.getDiff();
	if (diff <= minDiff) {
		minK = K;
		minDiff = diff;
	}

	cout << minK << ' ' << minDiff << '\n';

	return 0;
}

