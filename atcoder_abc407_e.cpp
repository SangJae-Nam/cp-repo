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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<int> A;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int N;
		cin >> N;
		A.resize(2 * N);
		for (int i = 0; i < N * 2; i++) {
			cin >> A[i];
		}

		priority_queue<int> q;
		long long int ret = 0;
		for (int i = 0; i < N; i++) {
			if (i > 0) {
				q.push(A[i * 2]);
				q.push(A[i * 2 - 1]);
			}
			else {
				q.push(A[i]);
			}

			int t = q.top();
			q.pop();
			ret += t;
		}

		cout << ret << '\n';
	}

	return 0;
}
