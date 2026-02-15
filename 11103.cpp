#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <deque>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, L;
	cin >> N >> L;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	deque<pair<int, int>> maxq;
	for (int i = 0; i < N; i++) {
		while (!maxq.empty() && maxq.front().second + L - 1 < i) {
			maxq.pop_front();
		}
		while (!maxq.empty() && maxq.back().first > A[i]) {
			maxq.pop_back();
		}
		maxq.push_back(make_pair(A[i], i));

		cout << maxq.front().first << ' ';
	}
	cout << '\n';

	return 0;
}
