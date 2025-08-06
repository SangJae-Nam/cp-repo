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

void run(int N, int M, int idx, vector<int> &sel)
{
	if (static_cast<int>(sel.size()) == M) {
		for (int n : sel) {
			cout << n << ' ';
		}
		cout << '\n';
		return;
	}
	if (N - idx + 1 + static_cast<int>(sel.size()) < M) {
		return;
	}
	if (idx > N) {
		return;
	}

	for (int i = idx; i <= N; i++) {
		sel.push_back(i);
		run(N, M, i + 1, sel);
		sel.pop_back();
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;
	vector<int> sel;
	sel.reserve(M);
	run(N, M, 1, sel);

	return 0;
}
