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
		while (static_cast<size_t>(i) < tree.size()) {
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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, K;
	cin >> N >> M >> K;

	vector<long long int> arr(N);
	FenwickTree<long long int> fenwickTree(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		fenwickTree.update(i, arr[i]);
	}

	for (int i = 0; i < M + K; i++) {
		int a, b;
		long long int c;
		cin >> a >> b >> c;
		switch (a) {
			case 1:
				fenwickTree.update(b - 1, c - arr[b - 1]);
				arr[b - 1] = c;
				break;

			case 2:
				cout << fenwickTree.rangeSum(b - 1, c - 1) << '\n';
				break;

			default:
				assert(false);
		}
	}

	return 0;
}