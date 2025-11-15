#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstring>

using namespace std;

class Solve {
private:
	int N, M;
	int S[500];
	int dp[2][100000];

public:
	Solve () {
	}

	void input() {
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> S[i];
		}

		memset(dp[0], -1, sizeof(int) * M);
	}

	void solve() {
		int sum = 0;
		for (int s : S) {
			sum += s;
		}

		if (sum % M == 0) {
			cout << N << '\n';
			return;
		}

		dp[0][0] = 0;
		int cur, next;
		for (int i = 0; i < N; i++) {
			cur = i % 2;
			next = (i + 1) % 2;

			memset(dp[next], -1, sizeof(int) * M);
			for (int j = 0; j < M; j++) {
				if (dp[cur][j] != -1) {
					int nextj = (j + S[i]) % M;
					dp[next][nextj] = max(dp[cur][nextj], dp[cur][j] + 1);
					dp[next][j] = max(dp[next][j], dp[cur][j]);
				}
			}
		}

		cout << dp[next][0] << '\n';
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

