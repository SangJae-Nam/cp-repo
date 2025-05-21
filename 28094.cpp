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
#include <cstring>

using namespace std;

class Solve {
private:
	int N, M;
	int scoreMap[9][9];

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		memset(scoreMap, 0, sizeof(scoreMap));
		for (int i = 0; i < M; i++) {
			int a, b, v;
			cin >> v >> a >> b;
			a--;
			b--;

			scoreMap[a][b] += v;
		}
	}

	void solve() {
		int assigned[9];
		for (int i = 0; i < N; i++) {
			assigned[i] = i;
		}
		int maxScore = -1;
		int numMaxScore = 0;

		do {
			int score = 0;
			for (int a = 0; a < N; a++) {
				for (int b = 0; b < N; b++) {
					if (scoreMap[a][b] == 0) {
						continue;
					}

					if (assigned[a] < assigned[b]) {
						score += scoreMap[a][b];
					}
				}
			}

			if (score > maxScore) {
				maxScore = score;
				numMaxScore = 1;
			}
			else if (score == maxScore) {
				numMaxScore++;
			}
		} while (next_permutation(assigned, assigned + N));

		cout << maxScore << ' ' << numMaxScore << '\n';
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

