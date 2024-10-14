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

// r < m 일 떄만 작동함
template<int m, typename T6>
class binomialCoeffMod
{
private:
	vector<modint<m, T6>> facts;
	vector<modint<m, T6>> invfacts;
	int size;

public:
	binomialCoeffMod(int _size) : size(_size) {
		getFermatCompute(facts, invfacts, size);
	}

	modint<m, T6> ncr(int n, int r) {
		assert(n < size);
		assert(r < m);

		return facts[n] * (invfacts[r] * invfacts[n - r]);
	}

	modint<m, T6> factorial(int n) {
		assert(n < size);
		return facts[n];
	}
};

using mint = modint<1000000007, int>;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	vector<int> A(N), B(M);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < M; i++) {
		cin >> B[i];
	}

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	int minVal = 2000000001;
	int mnMN = min(N, M);
	for (int i = 0, j = M - 1; i < mnMN; i++, j--) {
		minVal = min(minVal, A[i] + B[j]);
	}
	if (N > M) {
		for (int i = M; i < N; i++) {
			minVal = min(minVal, A[i]);
		}
	}

	mint ret(1);

	int i;
	for (i = 0; i < N; i++) {
		if (A[i] >= minVal) {
			break;
		}

		int b = minVal - A[i];
		auto bit = lower_bound(B.begin(), B.end(), b);
		int bnum = M - static_cast<int>(bit - B.begin());

		int bcase = bnum - i;
		if (bcase > 0) {
			ret *= bcase;
		}
		else {
			break;
		}
	}

	mint remainCase(1);
	int aremain = N - i;
	int bremain = M - i;
	int mxMatch = min(aremain, bremain);
	if (mxMatch > 0) {
		binomialCoeffMod<1000000007, int> bc(200001);

		for (int match = 1; match <= mxMatch; match++) {
			auto c = bc.ncr(aremain, match) * bc.ncr(bremain, match) * bc.factorial(match);
			remainCase += c;
		}
	}
	ret *= remainCase;

	cout << ret << '\n';

	return 0;
}
