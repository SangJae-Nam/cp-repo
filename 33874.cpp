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

// r < m 일 떄만 작동함
template<int m, typename T6>
class binomialCoeffMod
{
public:
	vector<modint<m, T6>> facts;
	vector<modint<m, T6>> invfacts;
	int size;

	binomialCoeffMod(int _size) : size(_size) {
		getFermatCompute(facts, invfacts, size);
	}

	modint<m, T6> ncr(int n, int r) {
		assert(n < size);
		assert(r < m);

		return facts[n] * (invfacts[r] * invfacts[n - r]);
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

constexpr int MOD = 1000000007;
using mint = modint<MOD, int>;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;
	binomialCoeffMod<MOD, int> bc(N + 1);

	if (N <= 7) {
		vector<vector<mint>> pascal(N, vector<mint>(N));
		for (int r = 0; r < N; r++) {
			for (int c = 0; c <= r; c++) {
				pascal[r][c] = bc.ncr(r, c);
			}
		}

		int ret = -1;
		int count = 0;

		for (int r = 0; r < N; r++) {
			for (int c = 0; c <= r; c++) {
				int dr[] = {0, 1, 1};
				int dc[] = {1, 0, 1};

				for (int d = 0; d < 3; d++) {
					int nr = r + dr[d];
					int nc = c + dc[d];
					if (nr >= 0 && nr < N && nc >= 0 && ((nr == r && nc <= r) || (nr > r && nc <= r + 1))) {
						int diff = abs((int)pascal[r][c].val() - (int)pascal[nr][nc].val());

						if (diff > ret) {
							ret = diff;
							count = 1;
						}
						else if (diff == ret) {
							count++;
						}
					}
				}
			}
		}

		cout << ret << ' ' << count << '\n';
	}
	else {
		if (N % 2 == 0) {
			cout << bc.ncr(N - 2, (N - 1) / 2) << " 2\n";
		}
		else {
			cout << bc.ncr(N - 2, (N - 1) / 2) << " 4\n";
		}
	}

	return 0;
}
