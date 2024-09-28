#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstring>
#include <bitset>
#include <queue>
#include <limits>
#include <cmath>
#include <map>

using namespace std;

#define __DEBUG__

template <typename T5>
class FenwickTree {
private:
	int arraySize;
	int treeSize;

public:
#ifdef __DEBUG__
	vector<T5> array;
#endif
	vector<T5> tree;

	FenwickTree(int size) {
		arraySize = size;
		treeSize = size + 1; // Start from 1
#ifdef __DEBUG__
		array.resize(size + 1);
#endif
		tree.resize(size + 1);
	}

	void clear() {
#ifdef __DEBUG__
		memset(array.data(), 0, array.size() * sizeof(T5));
#endif
		memset(tree.data(), 0, tree.size() * sizeof(T5));
	}

	void update(int i, const T5 &diff) {
#ifdef __DEBUG__
		array[i] += diff;
		if (i < 0 || i >= treeSize - 1) {
			cout << "Index is out of bound " << i << endl;
			assert(false);
		}
#endif
		i++; // Start from 1
		while (i < tree.size()) {
			tree[i] += diff;
			i += (i & -i);
		}
	}

	T5 sum(int i) {
#ifdef __DEBUG__
		if (i < 0 || i >= treeSize - 1) {
			cout << "Index is out of bound " << i << endl;
			assert(false);
		}
#endif
		i++; // Start from 1
		T5 ret = 0;
		while (i > 0) {
			ret += tree[i];
			i -= (i & -i);
		}

		return ret;
	}

	T5 rangeSum(int i, int j) { // i ~ j
		if (i > j) {
			swap(i, j);
		}
#ifdef __DEBUG__
		if (i < 0 || i >= treeSize - 1) {
			cout << "Index i is out of bound " << i << endl;
			assert(false);
		}
		if (j < 0 || j >= treeSize - 1) {
			cout << "Index j is out of bound " << j << endl;
			assert(false);
		}
#endif

		if (i > 0) {
			return sum(j) - sum(i - 1);
		}
		else {
			return sum(j);
		}
	}

	int findIndexFront(T5 target) {
		int start = 0;
		int end = arraySize - 1;

		while (start < end) {
			int mid = (start + end) / 2;
			if (rangeSum(0, mid) >= target) {
				end = mid;
			}
			else {
				start = mid + 1;
			}
		}

		return start;
    }

	int findIndexBack(T5 target) {
	    int start = 0;
	    int end = arraySize;

	    while (start < end) {
    	    int mid = (start + end) / 2;
			if (rangeSum(mid, arraySize - 1) >= target) {
            	start = mid + 1;
	        } else {
    	        end = mid;
        	}
	    }

    	return start - 1;
	}
};

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

	const T4& updateDiff(int index, const T4 &diffValue, int node, int nodeLeft, int nodeRight) {
		// 아예 벗어난 경우
		if (index < nodeLeft || nodeRight < index) {
			return range[node];
		}

		if (nodeLeft == nodeRight) {
			return range[node] += diffValue;
		}

		int mid = (nodeLeft + nodeRight) / 2;
		return range[node] =
				updateDiff(index, diffValue, node * 2, nodeLeft, mid) +
				updateDiff(index, diffValue, node * 2 + 1, mid + 1, nodeRight);

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

	const T4& updateDiff(int index, const T4 &diffValue) {
#ifdef __DEBUG__
		if (index < 0 || index >= size) {
			cout << "Index is out of bound " << index << endl;
			assert(false);
		}
#endif
		return updateDiff(index, diffValue, 1, 0, size - 1);
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

constexpr int MAX_VALUE = 500000;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int size = MAX_VALUE * 2 + 1;
	FenwickTree<int> indexes(size);
	FenwickTree<long long int> values(size);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		indexes.clear();
		values.clear();

		int N, M;
		cin >> N >> M;

		for (int i = 0; i < N; i++) {
			int v;
			cin >> v;
			indexes.update(v + MAX_VALUE, 1);
			values.update(v + MAX_VALUE, v);
		}

		vector<pair<int, int>> qw(M);
		for (int m = 0; m < M; m++) {
			cin >> qw[m].first >> qw[m].second;
		}

		long long int q2w = 0;
		vector<long long int> answer;
		answer.reserve(500000);
		for (int m = 0; m < M; m++) {
			int q = qw[m].first;
			int w = qw[m].second;

			switch (q) {
				case 1:
				{
					int idx = w + MAX_VALUE;
					w -= q2w;
					idx -= q2w;
					indexes.update(idx, 1);
					values.update(idx, w);
					break;
				}

				case 2:
					q2w += w;
					break;

				case 3:
				{
					int index = indexes.findIndexBack(w);
					long long int overflow = indexes.rangeSum(index, size - 1) - w;

					long long int sum = values.rangeSum(index, size - 1);
					sum -= overflow * (index - MAX_VALUE);
					sum += q2w * w;
					answer.push_back(sum);
					break;
				}

				case 4:
				{
					int index = indexes.findIndexFront(w);
					long long int overflow = indexes.rangeSum(0, index) - w;

					long long int sum = values.rangeSum(0, index);
					sum -= overflow * (index - MAX_VALUE);
					sum += q2w * w;
					answer.push_back(sum);
					break;
				}

				default:
					assert(false);
					break;
			}
		}
		
		for (auto a : answer) {
			cout << a << ' ';
		}
		cout << '\n';
	}

	return 0;
}

