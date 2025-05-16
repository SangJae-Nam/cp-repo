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
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());

void printTree(int nNumbers, int startNode, int rootNode = -1, char delim = ' ')
{
	uniform_int_distribution<int> disNode(0, nNumbers - 1);

	int rootIdx;
	vector<bool> used(nNumbers);
	if (rootNode == -1) {
		rootIdx = disNode(gen);
		rootNode = rootIdx + startNode;
	}
	else {
		rootIdx = rootNode - startNode;
	}

	queue<pair<int, int>> q; //cur, prev
	q.push(make_pair(rootIdx, -1));
	used[rootIdx] = true;
	int numUsed = 1;

	while (!q.empty()) {
		auto c = q.front();
		q.pop();
		int &cur = c.first;
		int &prev = c.second;

		if (prev != -1) {
			cout << cur + startNode << delim << prev + startNode << '\n';
		}

		if (numUsed < nNumbers) {
			int numChildren = uniform_int_distribution<int>(1, nNumbers - numUsed)(gen);
			if (numChildren > 5) {
				numChildren /= 5;
			}
			for (int i = 0; i < numChildren; i++) {
				int next = disNode(gen);
				while (used[next]) {
					next = disNode(gen);
				}

				used[next] = true;
				numUsed++;
				q.push(make_pair(next, cur));
			}
		}
	}
}

void printRandomNumbers(int nNumbers, int min, int max, char delim = ' ')
{
	uniform_int_distribution<int> dis(min, max);
	for (int i = 0; i < nNumbers; i++) {
		cout << dis(gen) << delim;
	}
	cout << '\n';
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases = 1;
	//cout << nTestcases << endl;
	while (nTestcases--) {
		uniform_int_distribution<int> dis(2, 20);
		int N = dis(gen);
		uniform_int_distribution<int> dis2(1, N - 1);
		int M = dis2(gen);
		uniform_int_distribution<int> dis3(1, N);
		int P = dis3(gen);

		cout << N << ' ' << M << ' ' << P << endl;
		printTree(N, 1, P);
	}

	return 0;
}
