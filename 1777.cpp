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
class SegmentTreeSum {
private:
	int size;
	vector<T4> range;  // start from 1

	const T4& init(const vector<T4> &array, int left, int right, int node) {
		if (left == right) {
			return range[node] = array[left];
		}

		int mid = (left + right) / 2;
		const T4& leftSum = init(array, left, mid, node * 2);
		const T4& rightSum = init(array, mid + 1, right, node * 2 + 1);

		return range[node] = leftSum + rightSum;
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
		return query(left, right, node * 2, nodeLeft, mid) +
				query(left, right, node * 2 + 1, mid + 1, nodeRight);
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
				update(index, newValue, node * 2, nodeLeft, mid) +
				update(index, newValue, node * 2 + 1, mid + 1, nodeRight);
	}

public:
	SegmentTreeSum(const vector<T4> &array) {
		size = static_cast<int>(array.size());
		int treeSize = size * 4;
		//int treeSize = static_cast<int>(ceil(log2(size)));
		//treeSize = 2 * static_cast<int>(pow(2, treeSize)) - 1;
		//cout << "Tree size : " << treeSize << endl;
		range.resize(treeSize);
		init(array, 0, size - 1, 1);
	}

	const T4 query(int left, int right) {
		return query(left, right, 1, 0, size - 1);
	}

	const T4& update(int index, const T4 &newValue) {
		return update(index, newValue, 1, 0, size - 1);
	}

	void print() {
		cout << "SEGTREE:" << endl;
		for (size_t i = 0; i < range.size(); i++) {
			cout << range[i] << ' ';
		}
		cout << endl;
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;
	vector<int> invSeq(N);
	for (int i = 0; i < N; i++) {
		cin >> invSeq[i];
	}

	vector<int> emptySlot(N, 1);
	SegmentTreeSum<int> segTree(emptySlot);

	vector<int> output(N, 0);
	for (int i = N - 1; i >= 0; i--) {
		int &targetEmpty = invSeq[i];

		int low = 0;
		int high = N;
		while (low < high) {
			int mid = low + (high - low) / 2;

			int queryVal = segTree.query(mid, N - 1);
			if (targetEmpty >= queryVal) {
				high = mid;
			}
			else {
				low = mid + 1;
			}
		}

		if (low < N && segTree.query(low, N - 1) < targetEmpty) {
			low++;
		}

		output[low - 1] = i + 1;
		segTree.update(low - 1, 0);
	}

	for (int i = 0; i < N; i++) {
		cout << output[i] << ' ';
	}
	cout << '\n';

	return 0;
}
