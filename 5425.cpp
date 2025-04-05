#include <iostream>
#include <vector>
#include <cstring>

// digit dp

using namespace std;

void makeDigits(long long int num, vector<int> &digits)
{
	while (num > 0) {
		digits.push_back(num % 10);
		num /= 10;
	}
}

long long int dp[19][190];
long long int run(int idx, int sum, int limit, const vector<int> &digits)
{
	if (idx < 0) {
		return sum;
	}

	if (!limit && dp[idx][sum] != -1) {
		return dp[idx][sum];
	}

	long long int ret = 0;
	int end = limit ? digits[idx] : 9;
	for (int i = 0; i < end; i++) {
		ret += run(idx - 1, sum + i, 0, digits);
	}
	int newLimit = limit ? 1 : 0;
	ret += run(idx - 1, sum + end, newLimit, digits);

	if (!limit) {
		dp[idx][sum] = ret;
	}
	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	memset(dp, -1, sizeof(dp));

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		vector<int> digitL, digitU;
		long long int L, U;
		cin >> L >> U;

		makeDigits(L - 1, digitL);
		makeDigits(U, digitU);

		long long int s1 = run(digitU.size() - 1, 0, 1, digitU);
		long long int s2 = run(digitL.size() - 1, 0, 1, digitL);

		cout << s1 - s2 << '\n';
	}

	return 0;
}
