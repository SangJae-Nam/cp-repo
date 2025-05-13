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

int bitCeil(int n)
{
	int ret = 1;
	while (ret < n) {
		ret <<= 1;
	}
	return ret;
}

template <typename T5, const T5 (*op)(const T5 &a, const T5 &b), const T5 (*endFunc)()>
class SegmentTree2 {
protected:
	int size;
	int bot;
	vector<T5> range;  // start from 1

public:
	SegmentTree2(const vector<T5> &array) {
		size = static_cast<int>(array.size());
		bot = bitCeil(size);
		int treeSize = bot * 2;
		range.resize(treeSize, endFunc());

		for (int i = 0; i < size; i++) {
			range[i + bot] = array[i];
		}
		for (int i = bot - 1; i >= 1; i--) {
			range[i] = op(range[i * 2], range[i * 2 + 1]);
		}
	}

	SegmentTree2(const int size) : SegmentTree2(vector<T5> (size, endFunc())) {
	}

	const T5 query(int left, int right) {  // [left, right)
#ifdef __DEBUG__
		if (left < 0 || left >= size) {
			cout << "Left is out of bound " << left << endl;
			assert(false);
		}
		if (right < 0 || right >= size) {
			cout << "Right is out of bound " << left << endl;
			assert(false);
		}
#endif
		T5 resultRight = endFunc();
		T5 resultLeft = endFunc();
		left += bot;
		right += bot;

		while (left < right) {
			if (left & 1) {
				resultLeft = op(resultLeft, range[left++]);
			}
			if (right & 1) {
				resultRight = op(range[--right], resultRight);
			}

			left >>= 1;
			right >>= 1;
		}

		return op(resultLeft, resultRight);
	}

	const T5 allQuery() {
		return range[1];
	}

	void update(int index, const T5 &value) {
#ifdef __DEBUG__
		if (index < 0 || index >= size) {
			cout << "Index is out of bound " << index << endl;
			assert(false);
		}
#endif
		index += bot;
		range[index] = value;
		index >>= 1;
		for (; index >= 1; index >>= 1) {
			range[index] = op(range[index * 2], range[index * 2 + 1]);
		}
	}

	T5 get(int index) {
#ifdef __DEBUG__
		if (index < 0 || index >= size) {
			cout << "Index is out of bound " << index << endl;
			assert(false);
		}
#endif
		return range[index + bot];
	}

	template <class F> int maxRight(int l, F f) const {
		if (l == size) {
			return size;
		}

		l += bot;
		T5 sm = endFunc();
		do {
			while (l % 2 == 0) {
				l >>= 1;
			}

			if (!f(op(sm, range[l]))) {
				while (l < bot) {
					l = (2 * l);
					if (f(op(sm, range[l]))) {
						sm = op(sm, range[l]);
						l++;
					}
				}
				return l - bot;
			}
			sm = op(sm, range[l]);
			l++;
		} while ((l & -l) != l);

		return size;
	}

	template <class F> int minLeft(int r, F f) const {
		if (r == 0) {
			return 0;
		}

		r += bot;
		T5 sm = endFunc();
		do {
			r--;
			while (r > 1 && (r % 2)) {
				r >>= 1;
			}

			if (!f(op(range[r], sm))) {
				while (r < bot) {
					r = (2 * r + 1);
					if (f(op(range[r], sm))) {
						sm = op(range[r], sm);
						r--;
					}
				}
				return r + 1 - bot;
			}
			sm = op(range[r], sm);
		} while((r & -r) != r);

		return 0;
	}

	int findIndexFront(const T5 target) {
		int start = 0;
		int end = size - 1;

		while (start < end) {
			int mid = start + (end - start) / 2;
			const T5 val = query(0, mid + 1);
			if (val >= target) {
				end = mid;
			}
			else {
				start = mid + 1;
			}
		}

		return start;
	}

	//query(start, size-1) >= target 중 가장 큰 값을 찾음
	int findIndexBack(const T5 target) {
		const T5 total = query(0, size);
		T5 newTarget = total - target;
#ifdef __DEBUG__
		if (total < target) {
			cout << "Target - total " << target << " - " << total << endl;
			assert(false);
		}
#endif

		int start = -1;
		int end = size;

		while (start + 1 < end) {
			int mid = start + (end - start) / 2;
			const T5 val = query(0, mid + 1);
			if (val <= newTarget) {
				start = mid;
			}
			else {
				end = mid;
			}
		}

		return end < size ? end : size - 1;
	}

	void print() {
		cout << "SEGTREE:" << endl;
		for (size_t i = 0; i < range.size(); i++) {
			cout << range[i] << ' ';
		}
		cout << endl;
	}
};


template <typename T5>
class SparseTableMin {
protected:
	vector<T5> &arr;
	vector<vector<int>> spt; //Sparse Table N * logN

	bool op(T5 &a, T5 &b) {
		return a < b;
	}

public:
	SparseTableMin(vector<T5> &_arr) : arr(_arr) {
		int size = static_cast<int>(arr.size());
		int log2size = static_cast<int>(ceil(log(static_cast<double>(size)) / log(2.0))) + 1;
		spt.resize(size, vector<int>(log2size));
		for (size_t i = 0; i < arr.size(); i++) {
			spt[i][0] = i;
		}

		for (int j = 1; (1<<j) <= size; j++) {
			for (int i = 0; i + (1<<j) - 1 < size; i++) {
				if (op(arr[spt[i][j - 1]], arr[spt[i + (1<<(j-1))][j - 1]])) {
					spt[i][j] = spt[i][j - 1];
				}
				else {
					spt[i][j] = spt[i + (1<<(j-1))][j - 1];
				}
			}
		}
	}

	int query(int i, int j) {
		if (i > j) {
			swap(i, j);
		}

		int k = static_cast<int>(floor(log(static_cast<double>(j - i + 1)) / log(2.0)));
		if (op(arr[spt[i][k]], arr[spt[j - (1<<k) + 1][k]])) {
			return spt[i][k];
		}
		else {
			return spt[j - (1<<k) + 1][k];
		}
	}
};

template <typename T5>
class SparseTableMax {
protected:
	vector<T5> &arr;
	vector<vector<int>> spt; //Sparse Table N * logN

	bool op(T5 &a, T5 &b) {
		return a > b;
	}

public:
	SparseTableMax(vector<T5> &_arr) : arr(_arr) {
		int size = static_cast<int>(arr.size());
		int log2size = static_cast<int>(ceil(log(static_cast<double>(size)) / log(2.0))) + 1;
		spt.resize(size, vector<int>(log2size));
		for (size_t i = 0; i < arr.size(); i++) {
			spt[i][0] = i;
		}

		for (int j = 1; (1<<j) <= size; j++) {
			for (int i = 0; i + (1<<j) - 1 < size; i++) {
				if (op(arr[spt[i][j - 1]], arr[spt[i + (1<<(j-1))][j - 1]])) {
					spt[i][j] = spt[i][j - 1];
				}
				else {
					spt[i][j] = spt[i + (1<<(j-1))][j - 1];
				}
			}
		}
	}

	int query(int i, int j) {
		if (i > j) {
			swap(i, j);
		}

		int k = static_cast<int>(floor(log(static_cast<double>(j - i + 1)) / log(2.0)));
		if (op(arr[spt[i][k]], arr[spt[j - (1<<k) + 1][k]])) {
			return spt[i][k];
		}
		else {
			return spt[j - (1<<k) + 1][k];
		}
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int t, n;
	cin >> t >> n;
	vector<int> m(n);
	for (int i = 0; i < n; i++) {
		cin >> m[i];
	}

	SparseTableMin<int> sptmin(m);
	SparseTableMax<int> sptmax(m);

	int left = 0;
	int maxValue = m[0];
	int minValue = m[0];
	int maxLen = 1;

	for (int right = 2; right < n; right++) {
		if (maxValue <= m[right]) {
			maxValue = m[right];
		}
		if (minValue >= m[right]) {
			minValue = m[right];
		}

		while ((left < right) && (maxValue - minValue > t)) {
			left++;
			maxValue = sptmax.query(left, right);
			minValue = sptmin.query(left, right);
		}
		maxLen = max(maxLen, right - left + 1);
	}

	cout << maxLen << '\n';

	return 0;
}
