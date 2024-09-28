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

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<int> A(N), B(N);

	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	long long int sum = 0;
	for (int i = 0; i < N; i++) {
		int b;
		cin >> b;

		if (A[i] < b) {
			int delta = b - A[i];
			if (delta % 30 == 0) {
				sum += delta / 30;
			}
			else {
				sum += delta / 30 + 1;
			}

		}
	}

	cout << sum << '\n';

	return 0;
}
