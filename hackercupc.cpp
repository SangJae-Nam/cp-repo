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

	int nTestcases;
	cin >> nTestcases;
	for (int t = 1; t <= nTestcases; t++) {
		int N;
		cin >> N;

		int totalApples = 2 * N - 1;
		vector<int> A(totalApples);
		for (int i = 0; i < totalApples; i++) {
			cin >> A[i];
		}

		if (N > 1) {
			sort(A.begin(), A.end());
			int pairSum = *A.begin() + *A.rbegin();
			for (int i = 1; i < totalApples / 2; i++) {
				if (pairSum != A[i] + A[totalApples - 1 - i]) {
					cout << A[i] << ", " << A[totalApples - 1 - i] << "/ " << pairSum << endl;
					pairSum = -1;
					break;
				}
			}

			if (pairSum != -1) {
				cout << "Case #" << t << ": " << pairSum - A[totalApples / 2] << "\n";
			}
			else {
				cout << "Case #" << t << ": -1\n";
			}
		}
		else {
			cout << "Case #" << t << ": 1\n";
		}
	}

	return 0;
}
