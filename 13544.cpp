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

int bitCeil(int n)
{
	int ret = 1;
	while (ret < n) {
		ret <<= 1;
	}
	return ret;
}

int countRightZero(unsigned int n)
{
#ifdef _MSC_VER
	unsigned long index;
	_BitScanForward(&index, n);
	return index;
#else
	// LSB부터 왼쪽으로 이동하여 1이 나오기 직전까지의 0의 개수를 반환
	// LSB 포함
	// 00000000 00000000 00000000 00010000 : 4
	return __builtin_ctz(n);
#endif
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

const vector<int> merge(const vector<int> &a, const vector<int> &b)
{
	vector<int> ret(a.size() + b.size());
	merge(a.begin(), a.end(), b.begin(), b.end(), ret.begin());
	return ret;
}

const vector<int> empty()
{
	return vector<int>();
}

class SegmentTree2_13544 : public SegmentTree2<vector<int>, merge, empty> {
public:
	SegmentTree2_13544(const vector<vector<int>> &v) : SegmentTree2<vector<int>, merge, empty>(v) {}

	const int query2(int left, int right, int k) {  // [left, right)
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
		int ret = 0;
		left += bot;
		right += bot;

		while (left < right) {
			if (left & 1) {
				auto &v = range[left++];
				auto it = upper_bound(v.begin(), v.end(), k);
				ret += static_cast<int>(v.end() - it);
			}
			if (right & 1) {
				auto &v = range[--right];
				auto it = upper_bound(v.begin(), v.end(), k);
				ret += static_cast<int>(v.end() - it);
			}

			left >>= 1;
			right >>= 1;
		}

		return ret;
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;
	vector<vector<int>> A(N);
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		A[i].push_back(a);
	}
	SegmentTree2_13544 segTree(A);

	int M;
	cin >> M;
	int lastAns = 0;
	for (int ii = 0; ii < M; ii++) {
		int a, b, c;
		cin >> a >> b >> c;

		int i = a ^ lastAns;
		int j = b ^ lastAns;
		int k = c ^ lastAns;

		lastAns = segTree.query2(i - 1, j, k);
		cout << lastAns << '\n';
	}

	return 0;
}
