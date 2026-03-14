#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;

class Solve {
private:
	int N, M;
	vector<vector<char>> arr;

public:
	Solve () {}

	void input() {
		cin >> N >> M;
		bool rot = false;
		if (N > M) {
			rot = true;
			swap(N, M);
		}
		arr.resize(N, vector<char>(M));

		if (!rot) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					cin >> arr[i][j];
					arr[i][j] -= '0';
				}
			}
		}
		else {
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					cin >> arr[j][i];
					arr[j][i] -= '0';
				}
			}
		}
	}

	void solve() {
		long long int ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				int count[21] = {0, };
				for (int k = 0; k < M; k++) {
					int s = arr[i][k] + arr[j][k];
					count[s]++;
				}

				for (int l = 2; l <= 9; l++) {
					ret += 1ll * count[l] * count[20 - l];
				}
				ret += 1ll * count[10] * (count[10] - 1) / 2;
			}
		}

		cout << ret << '\n';
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
