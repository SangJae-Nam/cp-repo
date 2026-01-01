#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <bitset>
#include <limits>
#include <cmath>

using namespace std;

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

	bool operator<(const modint& rhs) const {
		return mVal < rhs.mVal;
	}

	bool operator>(const modint& rhs) const {
		return mVal > rhs.mVal;
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

using mint = modint<1000000007, int>;

class Solve {
private:
	int R, C, N;
	vector<string> cake;
	string fruits;

	int dp[101][101][11];

	mint run(int sr, int sc, int fidx) {
		if (dp[sr][sc][fidx] != -1) {
			return dp[sr][sc][fidx];
		}

		if (fidx == N - 1) {
			for (int r = sr; r < R; r++) {
				for (int c = sc; c < C; c++) {
					if (cake[r][c] == fruits[fidx]) {
						dp[sr][sc][fidx] = 1;
						return 1;
					}
				}
			}
			dp[sr][sc][fidx] = 0;
			return 0;
		}

		if ((R - 1 - sr) + (C - 1 - sc) < N - 1 - fidx) {
			return 0;
		}

		mint ret = 0;
		bool found = false;
		for (int r = sr; r < R - 1; r++) {
			if (!found) {
				for (int c = sc; c < C; c++) {
					if (cake[r][c] == fruits[fidx]) {
						found = true;
						break;
					}
				}
			}
			
			if (found) {
				ret += run(r + 1, sc, fidx + 1);
			}
		}

		found = false;
		for (int c = sc; c < C - 1; c++) {
			if (!found) {
				for (int r = sr; r < R; r++) {
					if (cake[r][c] == fruits[fidx]) {
						found = true;
						break;
					}
				}
			}

			if (found) {
				ret += run(sr, c + 1, fidx + 1);
			}
		}

		dp[sr][sc][fidx] = static_cast<int>(ret.val());
		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> R >> C >> N;
		cake.resize(R);
		for (int i = 0; i < R; i++) {
			cin >> cake[i];
		}
		cin >> fruits;
	}

	void solve() {
		memset(dp, -1, sizeof(dp));
		cout << run(0, 0, 0) << '\n';
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
		s.input();
		s.solve();
	}

	return 0;
}
