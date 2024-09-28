#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
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

	vector<pair<double, int>> jobs(N);
	for (int i = 0; i < N; i++) {
		int T, S;
		cin >> T >> S;

		jobs[i].first = static_cast<double>(T) / S;
		jobs[i].second = i + 1;
	}
	sort(jobs.begin(), jobs.end());

	for (int i = 0; i < N; i++) {
		cout << jobs[i].second << ' ';
	}
	cout << '\n';

	return 0;
}
