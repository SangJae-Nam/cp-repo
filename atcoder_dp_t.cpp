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
// modint
// modint<1000000007, int> b(1000000000);
template<int m, typename T6>
class modint {
private:
	unsigned int mVal;

	static constexpr unsigned int umod() {
		return m;
	}

public:
	static constexpr int mod() {
		return m;
	}

	modint (T6 v = 0) {
		mVal = static_cast<unsigned int>(v % umod());
	}

	unsigned int val() const {
		return mVal;
	}

	modint& operator++() {
		mVal++;
		if (mVal == umod()) {
			mVal = 0;
		}
		return *this;
	}

	modint& operator--() {
		if (mVal == 0) {
			mVal = umod();
		}
		mVal--;
		return *this;
	}

	modint operator++(int) {
		modint result = *this;
		++*this;
		return result;
	}

	modint operator--(int) {
		modint result = *this;
		--*this;
		return result;
	}

	modint& operator+=(const modint& rhs) {
		mVal += rhs.mVal;
		if (mVal >= umod()) {
			mVal -= umod();
		}
		return *this;
	}

	modint& operator-=(const modint& rhs) {
		mVal -= rhs.mVal;
		if (mVal >= umod()) {
			mVal += umod();
		}
		return *this;
	}

	modint& operator*=(const modint& rhs) {
		unsigned long long z = mVal;
		z *= rhs.mVal;
		mVal = static_cast<unsigned int>(z % umod());
		return *this;
	}

	modint& operator/=(const modint& rhs) {
		mVal /= rhs.mVal;
		return *this;
	}

	modint operator+() const {
		return *this;
	}

	modint operator-() const {
		return modint() - *this;
	}

	modint operator+(const modint& rhs) const {
		return modint(*this) += rhs;
	}

	modint operator-(const modint& rhs) const {
		return modint(*this) -= rhs;
	}

	modint operator*(const modint& rhs) const {
		return modint(*this) *= rhs;
	}

	modint operator/(const modint& rhs) const {
		return modint(*this) /= rhs;
	}

	bool operator==(const modint& rhs) const {
		return mVal == rhs.mVal;
	}

	bool operator!=(const modint& rhs) const {
		return mVal != rhs.mVal;
	}

	friend istream& operator>>(istream &in, modint &rhs) {
		in >> rhs.mVal;
		return in;
	}

	friend ostream& operator<<(ostream &out, const modint &rhs) {
		out << rhs.mVal;
		return out;
	}

	modint pow(long long int n) const {
		assert(0 <= n);
		modint x = *this;
		modint r = 1;
		while (n) {
			if (n & 1) {
				r *= x;
			}
			x *= x;
			n >>= 1;
		}

		return r;
	}
};


int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string s;
	int N;
	cin >> N >> s;

	vector<vector<modint<1000000007, int>>> dp(N + 1, vector<modint<1000000007, int>>(N + 2));

	dp[1][1] = 1;
	for (int i = 1; i <= N - 1; i++) {
		if (s[i - 1] == '>') {
			for (int j = i + 1; j >= 1; j--) {
				/*
				for (int nj = 1; nj <= i + 1; nj++) {
					if (j >= nj) {
						dp[i + 1][nj] += dp[i][j];
					}
				}
				*/
				dp[i + 1][j] += dp[i + 1][j + 1] + dp[i][j];
			}
		}
		else {
			for (int j = 1; j <= i + 1; j++) {
				/*
				for (int nj = 1; nj <= i + 1; nj++) {
					if (j < nj) {
						dp[i + 1][nj] += dp[i][j];
					}
				}
				*/
				dp[i + 1][j] += dp[i + 1][j - 1] + dp[i][j - 1];
			}
		}
	}

	modint<1000000007, int> ret = 0;
	for (int i = 1; i <= N; i++) {
		ret += dp[N][i];
	}

	cout << ret << '\n';

	return 0;
}
