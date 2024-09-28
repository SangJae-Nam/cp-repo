#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <cassert>

using namespace std;

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
				val %= 1000000007;
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

	long long int n;
	cin >> n;
	cout << fibo<long long int>(n) << '\n';

	return 0;
}
