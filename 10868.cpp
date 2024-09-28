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

template <typename T5, const T5& (*op)(const T5 &a, const T5 &b), const T5 (*endFunc)()>
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
const T5 _minEnd()
{
	return numeric_limits<T5>::max();
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	SegmentTree2<long long int, std::min, _minEnd<long long int>> segMin(N + 1);
	for (int i = 1; i <= N; i++) {
		long long int n;
		cin >> n;
		segMin.update(i, n);
	}

	for (int i = 0; i < M; i++) {
		int s, e;
		cin >> s >> e;

		cout << segMin.query(s, e + 1) << '\n';
	}

	return 0;
}
