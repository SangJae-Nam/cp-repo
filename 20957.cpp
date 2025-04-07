#include <algorithm>
#include <iostream>
#include <utility>
#include <cassert>
#include <cstring>

using namespace std;

// digit dp

// modint
// modint<1000000007, int> b(1000000000);
template<int m, typename T6>
class modint {
protected:
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
	};

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

class Solve {
private:
	int dp[10000][2][7][2];
	modint<1000000007, int> dfs(int idx, int front, int sumMod, int mulSeven) {
		if (idx < 0) {
			if (sumMod % 7 == 0 && mulSeven == 1) {
				return 1;
			}
			else {
				return 0;
			}
		}

		if (dp[idx][front][sumMod][mulSeven] != -1) {
			return dp[idx][front][sumMod][mulSeven];
		}

		modint<1000000007, int> ret = 0;
		int start = front ? 1 : 0;
		for (int i = start; i <= 9; i++) {
			int newMulSeven = mulSeven;
			if (newMulSeven || i % 7 == 0) {
				newMulSeven = 1;
			}
			ret += dfs(idx - 1, 0, (sumMod + i) % 7, newMulSeven);
		}

		dp[idx][front][sumMod][mulSeven] = static_cast<int>(ret.val());
		return ret;
	}

public:
	Solve () {
		memset(dp, -1, sizeof(dp));
	}

	void solve() {
		int n;
		cin >> n;
		cout << dfs(n -1, 1, 0, 0) << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;
	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.solve();
	}

	return 0;
}
