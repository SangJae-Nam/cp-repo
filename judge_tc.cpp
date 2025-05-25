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

	// Input
	int N, M;
	cin >> N >> M;
	vector<pair<pair<int, int>, int>> LR(N);

	for (int i = 0; i < N; i++) {
		cin >> LR[i].first.first >> LR[i].first.second;
		LR[i].second = i;
	}

	// Output
	vector<pair<pair<int, int>, int>> ans(N);//section, level
	for (int i = 0; i < N; i++) {
		cin >> ans[i].first.second >> ans[i].first.first;
		ans[i].second = i;
	}
	sort(ans.begin(), ans.end());

	int m = ans[0].first.first;
	int l = ans[0].first.second;
	if (m != 1) {
		cout << "Section is not 1 at the begin" << endl;
		return -1;
	}
		if (!(ans[0].first.second >= LR[ans[0].second].first.first && 
		    ans[0].first.second <= LR[ans[0].second].first.second)) {
			cout << "Level is invalid2" << endl;
			return -1;
		}

	for (int i = 1; i < N; i++) {
		if (ans[i - 1].first.first != ans[i].first.first) {
			if (ans[i - 1].first.second >= ans[i].first.second) {
				cout << "Level is invalid" << endl;
				return -1;
			}
		}

		if (!(ans[i].first.second >= LR[ans[i].second].first.first && 
		    ans[i].first.second <= LR[ans[i].second].first.second)) {
			cout << "Level is invalid2" << endl;
			return -1;
		}
	}

	if (ans[N - 1].first.first != M) {
		cout << "Last section is invalid\n";
		return -1;
	}

	return 0;
}
