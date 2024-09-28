#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

pair<int, int> solve(const int x, const long long int sum)
{
	int low = -1;
	int hi = 10000;

	// find low
	while (low + 1 < hi) {
		int mid = (low + hi) / 2;

		long long int total = (mid + 100) * sum;
		long long int rounddown = total / 100;
		long long int roundup = (total % 100 != 0) ? rounddown + 1 : rounddown;

		cout << low << ", " << mid << ", " << hi << " TOTAL " << total / 100 << endl;

		if ((static_cast<long long int>(roundup / 100) == x) || (static_cast<long long int>(rounddown / 100) >= x)) {
			hi = mid;
		}
		else {
			low = mid;
		}
	}

	int min = hi;
	cout << min << endl;

	low = 0;
	hi = 10001;

	// find hi
	while (low + 1 < hi) {
		int mid = (low + hi) / 2;

		long long int total = (mid + 100) * sum;
		long long int rounddown = total / 100;
		long long int roundup = (total % 100 != 0) ? rounddown + 1 : rounddown;

		if ((static_cast<long long int>(roundup / 100) <= x) || (static_cast<long long int>(rounddown / 100) == x)) {
			low = mid;
		}
		else {
			hi = mid;
		}
	}

	int max = low;

	return make_pair(min, max);
}

int main(int argc, char *argv[])
{
	int nTestcases;

	cin >> nTestcases;
	while (nTestcases--) {
		int n;
		int x;
		double pi;
		long long int sum = 0;

		int *a = 0;
		*a = 100;

		cin >> n >> x;
		for (int i = 0; i < n; i++) {
			cin >> pi;
			sum += static_cast<long long int>(pi * 100);
		}

		auto answer = solve(x, sum);
		cout << answer.first << ' ' << answer.second << endl;
	}

	return 0;
}
