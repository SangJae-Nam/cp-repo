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
#include <cstring>

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
const T5 _sum(const T5 &a, const T5 &b)
{
	return  a + b;
}

template <typename T5>
const T5 _sumEnd()
{
	return 0;
}

template <typename T5>
class SegmentTreeRangeSum : public SegmentTree2<T5, _sum<T5>, _sumEnd<T5>> {
	public:
		SegmentTreeRangeSum (const int size) : SegmentTree2<T5, _sum, _sumEnd>(size) {}

		void update(int index, const T5 &diff) {
			rangeUpdate(index, index + 1, diff);
		}

		void rangeUpdate(int startIdx, int endIdx, const T5 &diff) {  //[startIdx, endIdx)
			SegmentTree2<T5, _sum<T5>, _sumEnd<T5>>::update(startIdx, SegmentTree2<T5, _sum<T5>, _sumEnd<T5>>::get(startIdx) + diff);
			if (endIdx < this->size) {
				SegmentTree2<T5, _sum<T5>, _sumEnd<T5>>::update(endIdx, SegmentTree2<T5, _sum<T5>, _sumEnd<T5>>::get(endIdx) - diff);
			}
		}

		const T5 get(int index) {
			return this->query(0, index + 1);
		}
};

class Solve
{
private:
	int N, M;
	vector<vector<int>> adj;
	vector<int> ett;
	vector<pair<int, int>> ettIndex;

	void dfs(int cur)
	{
		ett.push_back(cur);
		ettIndex[cur].first = ett.size() - 1;

		for (int next : adj[cur]) {
			dfs(next);
		}

		ett.push_back(cur);
		ettIndex[cur].second = ett.size() - 1;
	}

public:
	Solve() {}
	void input() {
		cin >> N >> M;
		adj.resize(N + 1);
		ett.reserve(2 * (N + 1));
		ettIndex.resize(N + 1);

		for (int i = 1; i <= N; i++) {
			int p;
			cin >> p;

			if (p != -1) {
				adj[p].push_back(i);
			}
		}
	}

	void solve() {
		dfs(1);
		SegmentTreeRangeSum<int> segTree(ett.size());

		for (int q = 0; q < M; q++) {
			int s;
			cin >> s;

			if (s == 1) {
				int idx, w;
				cin >> idx >> w;

				segTree.rangeUpdate(ettIndex[idx].first, ettIndex[idx].second + 1, w);
			}
			else if (s == 2) {
				int idx;
				cin >> idx;
				cout << segTree.get(ettIndex[idx].first) << '\n';
			}
		}
	}
};



int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;
	s.input();
	s.solve();

	return 0;
}