#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	vector<vector<pair<int, int>>> queries(N + 1);// R, (SEQ, X)
	for (int i = 0; i < Q; i++) {
		int R, X;
		cin >> R >> X;

		queries[R - 1].push_back(make_pair(i, X));
	}
	vector<int> ans(Q);

	vector<int> lis;
	lis.reserve(A.size());
	for (size_t i = 0; i < A.size(); i++) {
		auto it = lower_bound(lis.begin(), lis.end(), A[i]);
		if (it == lis.end()) {
			lis.push_back(A[i]);
		}
		else {
			*it = A[i];
		}

		for (auto &n : queries[i]) {
			int &q = n.first;
			int &x = n.second;
			auto it2 = lower_bound(lis.begin(), lis.end(), x);

			if (it2 == lis.end()) {
				ans[q] = static_cast<int>(lis.size());
			}
			else if (*it2 == x) {
				ans[q] = static_cast<int>(it2 - lis.begin()) + 1;
			}
			else {
				ans[q] = static_cast<int>(it2 - lis.begin());
			}
		}
	}

	for (int a : ans) {
		cout << a << '\n';
	}

	return 0;
}
