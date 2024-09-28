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
class Matrix {
private:
	size_t row;
	size_t col;

public:
	vector<vector<T1>> mat;
	Matrix(size_t row, size_t col) {
		this->row = row;
		this->col = col;
		mat.resize(row, vector<T1>(col, 0)); 
	}

	Matrix operator*(Matrix const& obj) const {
		int newRow = row;
		int newCol = obj.col;
		Matrix res(newRow, newCol);

		for (int i = 0; i < newRow; i++) {
			for (int j = 0; j < newCol; j++) {
				for (int k = 0; k < col; k++) {
					res.mat[i][j] += mat[i][k] * obj.mat[k][j];
				}
			}
		}

		return res;
	}

	void setUnitMatrix() {
		assert(row == col);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == j) {
					mat[i][j] = 1;
				}
				else {
					mat[i][j] = 0;
				}
			}
		}
	}

	Matrix exp(long long int x) {
		assert(row == col);
		Matrix res(row, col);
		res.setUnitMatrix();

		while (x > 0) {
			if (x % 2 == 0) {

			}
		}
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
	}

	return 0;
}
