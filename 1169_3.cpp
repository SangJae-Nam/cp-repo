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

template <typename T1>
class SquareMatrix {
public:
	static void _mul(const vector<vector<T1>> &op1, const vector<vector<T1>> &op2, vector<vector<T1>> &res) {
		for (size_t i = 0; i < res.size(); i++) {
			for (size_t j = 0; j < res.size(); j++) {
				T1 val = 0;
				for (size_t k = 0; k < res.size(); k++) {
					val += op1[i][k] * op2[k][j];
				}
				res[i][j] = val;
			}
		}
	}

	vector<vector<T1>> mat;
	SquareMatrix(size_t n, bool unitMatrix = false) {
		mat.resize(n, vector<T1>(n, 0));
		if (unitMatrix) {
			for (size_t i = 0; i < n; i++) {
				mat[i][i] = 1;
			}
		}
	}


	void mul(const SquareMatrix &other) {
		_mul(mat, other.mat, mat);
	}

	SquareMatrix operator*(const SquareMatrix& obj) {
		SquareMatrix res(mat.size());
		_mul(mat, obj.mat, res.mat);
		return res;
	}

	SquareMatrix exp(long long int x) {
		SquareMatrix res(mat.size(), true);
		SquareMatrix cur(*this);

		while (x > 0) {
			if (x % 2 == 0) {
				cur = cur * cur;
				x /= 2;
			}
			else {
				res = res * cur;
				x--;
			}
		}

		return res;
	}

	void print() {
		for (size_t i = 0; i < mat.size(); i++) {
			for (size_t j = 0; j < mat.size(); j++) {
				cout << mat[i][j] << ' ';
			}
			cout << '\n';
		}
	}
};

template <typename T2>
T2 fibo(T2 n)
{
	SquareMatrix<T2> fiboMatrix(2);
	fiboMatrix.mat[0][0] = 1;
	fiboMatrix.mat[0][1] = 1;
	fiboMatrix.mat[1][0] = 1;
	fiboMatrix.mat[1][1] = 0;

	SquareMatrix<T2> exp = fiboMatrix.exp(n - 1);
	// Fn+1 Fn
	// Fn   Fn-1
	return exp.mat[0][0];
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T, N, D;
	cin >> T >> N >> D;

	vector<SquareMatrix<modint<1000000007, int>>> bloodMap(T, SquareMatrix<modint<1000000007, int>>(N));
	for (int i = 0; i < T; i++) {
		int M;
		cin >> M;
		for (int j = 0; j < M; j++) {
			int a, b, c;
			cin >> a >> b >> c;
			bloodMap[i].mat[a - 1][b - 1] = c;
		}
	}

	SquareMatrix<modint<1000000007, int>> ans(N, true);
	if (D >= T) {
		SquareMatrix<modint<1000000007, int>> a(N, true);
		for (int i = 0; i < T; i++) {
			a = a * bloodMap[i];
		}

		ans = a.exp(D / T);
	}

	int remain = D % T;
	SquareMatrix<modint<1000000007, int>> b(N, true);
	for (int i = 0; i < remain; i++) {
		b = b * bloodMap[i];
	}
	ans = ans * b;

	ans.print();

	return 0;
}
