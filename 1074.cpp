#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

#define POW2(N)	(1<<(N))

static int arr[2][2] = {{0, 1}, {2, 3}};

int solve(int n, int r, int c)
{
	if (n == 1) {
		return arr[r][c];
	}

	if (r < POW2(n - 1) && c < POW2(n - 1)) {
		return solve(n - 1, r, c);
	}
	else if (r < POW2(n - 1) && c >= POW2(n - 1)) {
		return POW2(n - 1) * POW2(n - 1) + solve(n - 1, r, c - POW2(n - 1));
	}
	else if (r >= POW2(n - 1) && c < POW2(n - 1)) {
		return POW2(n - 1) * POW2(n - 1) * 2 + solve(n - 1, r - POW2(n - 1), c);
	}
	else {
		return POW2(n - 1) * POW2(n - 1) * 3 + solve(n - 1, r - POW2(n - 1), c - POW2(n - 1));
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	int r;
	int c;

	cin >> N >> r >> c;
	cout << solve(N, r, c) << endl;

	return 0;
}
