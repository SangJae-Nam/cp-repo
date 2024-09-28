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

template <typename T4>
class SegmentTreeMax {
private:
	int size;
	vector<T4> range;  // start from 1

	const T4& init(const vector<T4> &array, int left, int right, int node) {
		if (left == right) {
			return range[node] = array[left];
		}

		int mid = (left + right) / 2;
		const T4& leftMax = init(array, left, mid, node * 2);
		const T4& rightMax = init(array, mid + 1, right, node * 2 + 1);

		return range[node] = max(leftMax, rightMax);
	}

	const T4 query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 아예 벗어난 경우
		if (right < nodeLeft || nodeRight < left) {
			return 0;
		}

		// 완전히 포함 된 경우
		if (left <= nodeLeft && nodeRight <= right) {
			return range[node];
		}

		// 일부만 포함 된 경우 (분할정복)
		int mid = (nodeLeft + nodeRight) / 2;
		return max(query(left, right, node * 2, nodeLeft, mid),
				query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	const T4& update(int index, const T4 &newValue, int node, int nodeLeft, int nodeRight) {
		// 아예 벗어난 경우
		if (index < nodeLeft || nodeRight < index) {
			return range[node];
		}

		if (nodeLeft == nodeRight) {
			return range[node] = newValue;
		}

		int mid = (nodeLeft + nodeRight) / 2;
		return range[node] =
				max(update(index, newValue, node * 2, nodeLeft, mid),
				update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}

public:
	SegmentTreeMax(const vector<T4> &array) {
		size = static_cast<int>(array.size());
		int treeSize = size * 4;
		//int treeSize = static_cast<int>(ceil(log2(size)));
		//treeSize = 2 * static_cast<int>(pow(2, treeSize)) - 1;
		//cout << "Tree size : " << treeSize << endl;
		range.resize(treeSize);
		init(array, 0, size - 1, 1);
	}

	const T4 query(int left, int right) {
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
		return query(left, right, 1, 0, size - 1);
	}

	const T4& update(int index, const T4 &newValue) {
#ifdef __DEBUG__
		if (index < 0 || index >= size) {
			cout << "Index is out of bound " << index << endl;
			assert(false);
		}
#endif
		return update(index, newValue, 1, 0, size - 1);
	}

	int findIndexFront(const T4 target) {
		int start = 0;
		int end = size - 1;

		while (start < end) {
			int mid = start + (end - start) / 2;
			const T4 val = query(0, mid);
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
	int findIndexBack(const T4 target) {
		const T4 total = query(0, size - 1);
		T4 newTarget = total - target;
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
			const T4 val = query(0, mid);
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

class Solve {
private:
	int N;
	vector<int> h;
	vector<int> a;
	long long int maxA;

public:
	Solve() {}
	void input() {
		cin >> N;
		h.resize(N);
		a.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> h[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> a[i];
		}
	}

	long long int solve() {
		constexpr int MAX_H = 200001;
		maxA = 0;
		vector<long long int> dp(MAX_H);
		SegmentTreeMax<long long int> dpTree(dp);

		for (int i = 0; i < N; i++) {
			long long int val = dpTree.query(0, h[i]) + a[i];
			dpTree.update(h[i], val);
			maxA = max(maxA, val);
		}

		return maxA;
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;
	s.input();
	cout << s.solve() << '\n';

	return 0;
}
