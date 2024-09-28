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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int N, M;
		cin >> N >> M;

		vector<int> D(N - 1);
		for (int i = 0; i < N - 1; i++) {
			cin >> D[i];
		}

		long long int start = 0;
		long long int end = numeric_limits<long long int>::max();

		while (start != end) {
			long long int mid = (start + end) / 2;

			int groups = 1;
			long long int count = 0;
			long long int prevEnergy = 0;
			long long int currEnergy = 0;
			
			for (int num : D) {
				count++;
				prevEnergy += num * count;
				currEnergy += prevEnergy;

				if (currEnergy > mid) { //Cut
					groups++;
					count = 0;
					prevEnergy = 0;
					currEnergy = 0;
				}
			}

			if (groups <= M) {
				end = mid;
			}
			else {
				start = mid + 1;
			}
		}

		cout << end << '\n';
	}

	return 0;
}
