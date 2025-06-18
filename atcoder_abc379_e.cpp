#include <algorithm>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	string S;
	cin >> N >> S;

	string ret;
	ret.reserve(N);

	long long int sum = 0;
	long long int up = 0;
	for (long long int j = N; j > 0; j--) {
		sum += (S[j - 1] - '0') * j;
	}
	ret.push_back('0' + sum % 10);
	up = sum / 10;

	for (long long int i = 1; i < N; i++) {
		sum -= (S[N - i] - '0') * (N - i + 1);

		ret.push_back('0' + (up + sum) % 10);
		up = (up + sum) / 10;
	}

	while (up > 0) {
		ret.push_back('0' + up % 10);
		up /= 10;
	}

	reverse(ret.begin(), ret.end());
	cout << ret << '\n';

	return 0;
}

