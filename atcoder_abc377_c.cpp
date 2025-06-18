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
public:
	Solve () {}

	void input() {
	}

	void solve() {
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long int N;
	int M;
	cin >> N >> M;
	vector<int> A(M), B(M);
	for (int i = 0; i < M; i++) {
		cin >> A[i] >> B[i];
	}

	set<pair<int, int>> points;
	for (int i = 0; i < M; i++) {
		int dc[] = {-2, -1, 1, 2, 2, 1, -1, -2};
		int dr[] = {-1, -2, -2, -1, 1, 2, 2, 1};
		int &cr = A[i];
		int &cc = B[i];
		points.insert(make_pair(cr, cc));
		for (int j = 0; j < 8; j++) {
			int nr = cr + dr[j];
			int nc = cc + dc[j];

			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
				points.insert(make_pair(nr, nc));
			}
		}
	}

	cout << N * N - points.size() << '\n';

	return 0;
}
