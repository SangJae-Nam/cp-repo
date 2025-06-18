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

long long int check(long long int len, vector<int> &cables)
{
	long long int ret = 0;
	for (int c : cables) {
		ret += c / len;
	}
	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int K, N;
	cin >> K >> N;
	vector<int> cables(K);
	for (int i = 0; i < K; i++) {
		cin >> cables[i];
	}

	long long int lo = 1;
	long long int hi = 0x80000000;

	while (lo + 1 < hi) {
		long long int mid = (lo + hi) / 2;
		if (check(mid, cables) >= N) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}

	cout << lo << '\n';

	return 0;
}
