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
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	constexpr int MOD = 1000003;
	binomialCoeffMod<MOD, int> bc(2000001);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int R, C, N;
		cin >> R >> C >> N;

		vector<pair<int, int>> cookies(N);
		for (int i = 0; i < N; i++) {
			cin >> cookies[i].first >> cookies[i].second;
		}
		sort(cookies.begin(), cookies.end());

		vector<modint<MOD, int>> ways(N);
		vector<int> numCookies(N);

		for (int i = 0; i < N; i++) {
			int &ix = cookies[i].second;
			int &iy = cookies[i].first;
			//cout << ix << ", " << iy << endl;
			
			int maxCookies = 0;
			modint<MOD, int> w = 0;
			for (int j = 0; j < i; j++) {
				int &jx = cookies[j].second;
				int &jy = cookies[j].first;

				if (jx <= ix && jy <= iy) {
					if (numCookies[j] > maxCookies) {
						w = ways[j] * bc.ncr(ix - jx + iy - jy, iy - jy);
						maxCookies = numCookies[j];
					}
					else if (numCookies[j] == maxCookies) {
						w += ways[j] * bc.ncr(ix - jx + iy - jy, iy - jy);
					}
				}
			}

			numCookies[i] = maxCookies + 1;
			if (w == 0) {
				ways[i] = bc.ncr(ix - 1 + iy - 1, iy - 1);
			}
			else {
				ways[i] = w;
			}
			//cout << "WAYS" << i <<": " << ways[i] << endl;
			//cout << "COOKIES" << i << ": " << numCookies[i] << endl;
		}

		int maxCookies = 0;
		modint<MOD, int> w = 0;
		for (int i = N - 1; i >= 0; i--) {
			int &ix = cookies[i].second;
			int &iy = cookies[i].first;
			//cout << ix << ", " << iy << endl;
			//cout << "COOKIES" << i << ": " << numCookies[i] << endl;

			if (numCookies[i] > maxCookies) {
				w = ways[i] * bc.ncr(C - ix + R - iy, R - iy);
				maxCookies = numCookies[i];
			}
			else if (numCookies[i] == maxCookies) {
				w += ways[i] * bc.ncr(C - ix + R - iy, R - iy);
			}
			//cout << w << endl;
		}

		cout << w << '\n';
	}

	return 0;
}
