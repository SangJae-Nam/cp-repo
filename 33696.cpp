#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <array>
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

// 페르마 소정리를 이용한 펙토리얼과 펙토리얼의 역원 계산
template<int m, typename T6>
void getFermatCompute(vector<modint<m, T6>> &facts, vector<modint<m, T6>> &invfacts, int size)
{
	facts.resize(size);
	invfacts.resize(size);

	facts[0] = 1;
	invfacts[0] = 1;

	for (int i = 1; i < size; i++) {
		facts[i] = facts[i - 1] * i;
		invfacts[i] = facts[i].pow(m - 2);
	}
}

constexpr int MOD = 1000000007;
using mint = modint<MOD, int>;

class Solve {
private:
	int N;
	vector<mint> facts;
	vector<mint> invfacts;
	vector<mint> dp;

	mint T(int n) {  // 길이 3n의 UDP 문자열 개수
		mint ret = facts[3 * n];
		ret *= invfacts[n] * invfacts[n] * invfacts[n];
		return ret;
	}

	mint F(int n) {  // 완전 UDP 문자열 개수
		if (n == 1) {
			return 6;
		}

		mint &ret = dp[n];
		if (ret != -1) {
			return ret;
		}

		ret = T(n);
		for (int i = 1; i < n; i++) {
			ret -= F(i) * T(n - i);
		}
		return ret;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		getFermatCompute(facts, invfacts, 3*N + 1);
		dp.resize(N + 1, -1);
	}

	void solve() {
		cout << F(N) << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;
	s.input();
	s.solve();

	return 0;
}
