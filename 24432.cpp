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

int k;
void getSums(int idx, int count, int sum, const vector<int> &seq, vector<int> &ret)
{
	if (count >= k) {
		ret.push_back(sum);
		return;
	}
	if (idx >= static_cast<int>(seq.size())) {
		return;
	}

	for (size_t i = idx; i < seq.size(); i++) {
		getSums(i + 1, count + 1, sum + seq[i], seq, ret);
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<int> bob, alice;
	int n, m;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		cin >> n >> m >> k;
		bob.resize(n);
		alice.resize(m);

		for (int i = 0; i < n; i++) {
			cin >> bob[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> alice[i];
		}

		vector<int> B, A;
		getSums(0, 0, 0, bob, B);
		getSums(0, 0, 0, alice, A);

		sort(B.begin(), B.end());
		sort(A.begin(), A.end());

		int mx = max(abs(*B.begin() - *A.rbegin()), abs(*B.rbegin() - *A.begin()));

		int ia = 0;
		int ib = 0;
		int mn = numeric_limits<int>::max();

		while (ia < static_cast<int>(A.size()) && ib < static_cast<int>(B.size())) {
			mn = min(mn, abs(B[ib] - A[ia]));
			if (mn == 0) {
				break;
			}
			if (B[ib] > A[ia]) {
				ia++;
			}
			else {
				ib++;
			}
		}

		cout << mn << ' ' << mx << '\n';
	}

	return 0;
}
