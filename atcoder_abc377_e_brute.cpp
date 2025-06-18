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

class Solve {
private:
	int N;
	long long int K;
	vector<int> P;

	vector<int> permutation(const vector<int> &arr, long long int count)
	{
		vector<int> after(arr);
		vector<int> before(arr.size());
		for (int i = 0; i < count; i++) {
			swap(before, after);
			for (int j = 0; j < static_cast<int>(arr.size()); j++) {
				after[j] = before[before[j]];
			}
		}
		return after;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> K;
		P.resize(N);

		for (int i = 0; i < N; i++) {
			cin >> P[i];
			P[i]--;
		}
	}

	void solve() {
		auto s = permutation(P, K);
		for (int n : s) {
			cout << n + 1 << ' ';
		}
		cout << '\n';
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

