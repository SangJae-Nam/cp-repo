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

// dmodint
// dmodint<int> b(1000000000);
class dmodint {
private:
	static int m;
	unsigned int mVal;

	static unsigned int umod() {
		return static_cast<unsigned int>(m);
	}

public:
	static void setmod(int mm) {
		m = mm;
	}

	static int mod() {
		return m;
	}

	dmodint (long long int v = 0) {
		mVal = static_cast<unsigned int>(v % umod());
	}

	unsigned int val() const {
		return mVal;
	}

	dmodint& operator++() {
		mVal++;
		if (mVal == umod()) {
			mVal = 0;
		}
		return *this;
	}

	dmodint& operator--() {
		if (mVal == 0) {
			mVal = umod();
		}
		mVal--;
		return *this;
	}

	dmodint operator++(int) {
		dmodint result = *this;
		++*this;
		return result;
	};

	dmodint operator--(int) {
		dmodint result = *this;
		--*this;
		return result;
	}

	dmodint& operator+=(const dmodint& rhs) {
		mVal += rhs.mVal;
		if (mVal >= umod()) {
			mVal -= umod();
		}
		return *this;
	}

	dmodint& operator-=(const dmodint& rhs) {
		mVal -= rhs.mVal;
		if (mVal >= umod()) {
			mVal += umod();
		}
		return *this;
	}

	dmodint& operator*=(const dmodint& rhs) {
		unsigned long long z = mVal;
		z *= rhs.mVal;
		mVal = static_cast<unsigned int>(z % umod());
		return *this;
	}

	dmodint& operator/=(const dmodint& rhs) {
		mVal /= rhs.mVal;
		return *this;
	}

	dmodint operator+() const {
		return *this;
	}

	dmodint operator-() const {
		return dmodint() - *this;
	}

	dmodint operator+(const dmodint& rhs) const {
		return dmodint(*this) += rhs;
	}

	dmodint operator-(const dmodint& rhs) const {
		return dmodint(*this) -= rhs;
	}

	dmodint operator*(const dmodint& rhs) const {
		return dmodint(*this) *= rhs;
	}

	dmodint operator/(const dmodint& rhs) const {
		return dmodint(*this) /= rhs;
	}

	bool operator==(const dmodint& rhs) const {
		return mVal == rhs.mVal;
	}

	bool operator!=(const dmodint& rhs) const {
		return mVal != rhs.mVal;
	}

	friend istream& operator>>(istream &in, dmodint &rhs) {
		in >> rhs.mVal;
		return in;
	}

	friend ostream& operator<<(ostream &out, const dmodint &rhs) {
		out << rhs.mVal;
		return out;
	}

	dmodint pow(long long int n) const {
		assert(0 <= n);
		dmodint x = *this;
		dmodint r = 1;
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
int dmodint::m = -1;

// r < m 일 떄만 작동함
dmodint ncr(long long int n, long long int r, int m)
{
    assert(r < m);

    if (n - r < r) {
        r = n - r;
    }

    // N * (N - 1) * ... * (N - R + 1)
    dmodint n2nr(1);
    // R!
    dmodint factR(1);
    for (long long int i = 0; i < r; i++) {
        n2nr *= (n - i);
        factR *= (i + 1);
    }

    // (R!)^-1 == (R!)^(m - 2)
    dmodint invFactR = factR.pow(m - 2);

    return n2nr * invFactR;
}

// 뤼카의 정리
dmodint ncrLucas(long long int n, long long int r, int m)
{
    if (n - r < r) {
        r = n - r;
    }

	dmodint ret(1);
	while (n > 0 || r > 0) {
		long long int nn = n % m;
		long long int rr = r % m;

		if (nn < rr) {
			return dmodint(0);
		}

		ret *= ncr(nn, rr, m);

		n /= m;
		r /= m;
	}

	return ret;
}


int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long int N, K;
	int M;
	cin >> N >> K >> M;

	dmodint::setmod(M);
	cout << ncrLucas(N, K, M) << '\n';

	return 0;
}
