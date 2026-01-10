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

// r < m 일 떄만 작동함
template<int m, typename T6>
modint<m, T6> ncr(int n, int r)
{
    assert(r < m);

    if (n - r < r) {
        r = n - r;
    }

    // N * (N - 1) * ... * (N - R + 1)
    modint<m, T6> n2nr = 1;
    // R!
    modint<m, T6> factR = 1;
    for (int i = 0; i < r; i++) {
        n2nr *= (n - i);
        factR *= (i + 1);
    }

    // (R!)^-1 == (R!)^(m - 2)
    modint<m, T6> invFactR = factR.pow(m - 2);

    return n2nr * invFactR;
}

// 뤼카의 정리
template<int m, typename T6>
modint<m, T6> ncrLucas(long long int n, long long int r)
{
    assert(r < m);

    if (n - r < r) {
        r = n - r;
    }

	modint<m, T6> ret = 1;
	while (n > 0 || r > 0) {
		long long int nn = n % m;
		long long int rr = r % m;

		if (nn < rr) {
			return modint<m, T6>(0);
		}

		ret *= ncr<m, T6>(nn, rr);

		n /= m;
		r /= m;
	}

	return ret;
}

using mint = modint<1000000007, int>;

class Solve {
private:
	int N, K;
	string A;

public:
	Solve () {}

	void input() {
		cin >> N >> K;
		cin >> A;
	}

	void solve() {
		if (K == 1) {
			cout << "1\n";
			return;
		}

		vector<int> oneIndexes;
		oneIndexes.reserve(N);
		for (int i = 0; i < N; i++) {
			if (A[i] == '1') {
				oneIndexes.push_back(i);
			}
		}

		if (oneIndexes.size() % K != 0) {
			cout << "0\n";
			return;
		}

		if (oneIndexes.size() > 0) {
			mint ret = 1;
			int step = static_cast<int>(oneIndexes.size() / K);
			for (int i = step; i < oneIndexes.size(); i += step) {
				ret *= oneIndexes[i] - oneIndexes[i - 1];
			}
			cout << ret << '\n';
		}
		else {
			cout << ncrLucas<1000000007, int>(N - 1, K - 1) << '\n';
		}
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
