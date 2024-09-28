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

	int N, Q;
	cin >> N >> Q;

	deque<pair<int, int>> dragons(N);
	for (int i = 0; i < N; i++) {
		dragons[i].first = i + 1;
		dragons[i].second = 0;
	}

	for (int i = 0; i < Q; i++) {
		int q1;
		cin >> q1;

		if (q1 == 1) {
			char q2;
			cin >> q2;

			int newX = dragons[0].first;
			int newY = dragons[0].second;

			switch (q2) {
				case 'R':
					newX++;
					break;

				case 'L':
					newX--;
					break;

				case 'U':
					newY++;
					break;

				case 'D':
					newY--;
					break;
			}

			dragons.push_front(make_pair(newX, newY));
			dragons.pop_back();
		}
		else {
			int q2;
			cin >> q2;

			cout << dragons[q2 - 1].first << ' ' << dragons[q2 - 1].second << '\n';
		}
	}

	return 0;
}
