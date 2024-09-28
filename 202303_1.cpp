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

pair<long long int, long long int> solve(int N, int PA, int PB, const vector<int> &houses)
{
	if (PA > PB) {
		swap(PA, PB);
	}

	long long int sumA = 0;
	long long int sumB = 0;
	for (int i = 0; i < N; i++) {
		sumA += houses[i] - PA;
	}

	long long int minLength = sumA;
	long long int minDiff = sumA;

	for (int i = N - 1; i >= 0; i--) {
		sumA -= (houses[i] - PA);
		sumB += (PB - houses[i]);

		long long int totalLength = sumA + sumB;
		long long int diff = abs(sumA - sumB);
		if (minLength > totalLength) {
			minLength = totalLength;
			minDiff = diff;
		}
		else if (minLength == totalLength && minDiff > diff) {
			minDiff = diff;
		}
	}

	return make_pair(minLength * 2, minDiff * 2);
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int N, PA, PB;
		cin >> N >> PA >> PB;

		vector<int> houses(N);
		for (int i = 0; i < N; i++) {
			cin >> houses[i];
		}

		sort(houses.begin(), houses.end());
		auto answer = solve(N, PA, PB, houses);
		cout << answer.first << ' ' << answer.second << '\n';
	}

	return 0;
}
