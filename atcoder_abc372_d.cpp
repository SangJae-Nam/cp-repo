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
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solve {
private:
	int N;
	vector<int> H;

public:
	Solve () {}

	void input() {
		cin >> N;
		H.resize(N);

		for (int i = 0; i < N; i++) {
			cin >> H[i];
		}
	}

	void solve() {
		vector<int> ans(N);
		stack<int> s;
		for (int i = N - 1; i >= 0; i--) {
			ans[i] = s.size();
			while (!s.empty() && s.top() < H[i]) {
				s.pop();
			}
			s.push(H[i]);
		}

		for (int a : ans) {
			cout << a << ' ';
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
