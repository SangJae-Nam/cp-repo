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

long long int exp_mod(long long int a, long long int b, long long int mod) // a^b % mod
{
	assert(b >= 0);
	long long int r = 1;
	while (b) {
		if (b & 1) {
			r = (r * a) % mod;
		}
		a = (a * a) % mod;
		b >>= 1;
	}

	return r;
}

class Solve {
private:
	int N;
	long long int K;
	vector<int> P;

	void cal(vector<int> &group, unordered_map<int, int> &groupIdx, vector<int> &answer)
	{
		int size = static_cast<int>(group.size());
		int step = exp_mod(2, K, size);
		for (auto p : group) {
			int idx = groupIdx[p];
			int nextIdx = (idx + step) % size;
			answer[p] = group[nextIdx];
		}
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
		vector<int> answer(N);

		vector<bool> visited(N);
		for (int i = 0; i < N; i++) {
			if (visited[i]) {
				continue;
			}

			vector<int> group;
			unordered_map<int, int> groupIdx;
			int cur = i;
			do {
				visited[cur] = true;
				group.push_back(cur);
				groupIdx[cur] = static_cast<int>(group.size()) - 1;
				cur = P[cur];
			} while (cur != i);

			cal(group, groupIdx, answer);
		}

		for (int n : answer) {
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
