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
	string X;
	vector<int> V;
	vector<pair<long long int, int>> numbers;

public:
	Solve () {}

	void input() {
		cin >> N >> X;
		V.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> V[i];
			V[i];
		}
	}

	void solve() {
		int M = X.size() - 1;
		numbers.resize(1<<M);

		for (int plus = (1<<M) - 1; plus >= 0; plus--) {
			//0=plus,
			long long int sum = 0;
			long long int num = X[M] - '0';
			long long int ten = 1;
			for (int i = 0; i < M; i++) {
				if (plus & (1<<i)) {
					ten *= 10;
					num += (X[M - i - 1] - '0') * ten;
				}
				else {
					sum += num;
					num = X[M - i - 1] - '0';
					ten = 1;
				}
			}
			sum += num;

			numbers[plus] = make_pair(sum, plus);
		}
		sort(numbers.begin(), numbers.end());

		long long int ws = 0;
		int wp = 0;
		for (int vi : V) {
			vi--;
			ws += numbers[vi].first;
			wp += M - __builtin_popcount(numbers[vi].second);
		}

		cout << ws << ' ' << wp << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
