#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include <sstream>
#include <cassert>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<pair<int, int>> BA(N);
	for (int i = 0; i < N; i++) {
		cin >> BA[i].second;
	}

	long long int ret = 0;
	priority_queue<long long int> A;
	for (int i = 0; i < N; i++) {
		cin >> BA[i].first;

		if (BA[i].first > BA[i].second) {
			int diff = (BA[i].first - BA[i].second);
			int mul = diff / 30;
			if (diff % 30 != 0) {
				mul += 1;
			}
			BA[i].second += mul * 30;
			ret += mul;
		}

		A.push(-BA[i].second);
	}
	sort(BA.begin(), BA.end());

	for (int i = 0; i < N; i++) {
		int &curA = BA[i].second;

		while (true) {
			long long int qt = -A.top();
			A.pop();
			if (curA > qt) {
				A.push(-qt - 30);
				ret++;
			}
			else {
				break;
			}
		}
	}

	cout << ret << '\n';

	return 0;
}
