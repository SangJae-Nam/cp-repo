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
class RangeMinimumQuery {
private:
	int size;
	vector<T4> rangeMin;  // start from 1
	const T4 MAX_VALUE;

	const T4& init(const vector<T4> &array, int left, int right, int node) {
		if (left == right) {
			return rangeMin[node] = array[left];
		}

		int mid = (left + right) / 2;
		const T4& leftMin = init(array, left, mid, node * 2);
		const T4& rightMin = init(array, mid + 1, right, node * 2 + 1);

		return rangeMin[node] = min(leftMin, rightMin);
	}

	const T4& query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 아예 벗어난 경우
		if (right < nodeLeft || nodeRight < left) {
			return MAX_VALUE;
		}

		// 완전히 포함 된 경우
		if (left <= nodeLeft && nodeRight <= right) {
			return rangeMin[node];
		}

		// 일부만 포함 된 경우 (분할정복)
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
				query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	const T4& update(int index, const T4 &newValue, int node, int nodeLeft, int nodeRight) {
		// 아예 벗어난 경우
		if (index < nodeLeft || nodeRight < index) {
			return rangeMin[node];
		}

		if (nodeLeft == nodeRight) {
			return rangeMin[node] = newValue;
		}

		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(
				update(index, newValue, node * 2, nodeLeft, mid),
				update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}

public:
	RangeMinimumQuery(const vector<T4> &array, const T4 maxValue) : MAX_VALUE(maxValue) {
		size = static_cast<int>(array.size());
		//int treeSize = size * 4;
		int treeSize = static_cast<int>(ceil(log2(size)));
		treeSize = 2 * static_cast<int>(pow(2, treeSize)) - 1;
		rangeMin.resize(treeSize);
		init(array, 0, size - 1, 1);
	}

	const T4& query(int left, int right) {
		return query(left, right, 1, 0, size - 1);
	}

	const T4& update(int index, const T4 &newValue) {
		return update(index, newValue, 1, 0, size - 1);
	}

#if 0
	void print() {
		for (size_t i = 0; i < rangeMin.size(); i++) {
			cout << rangeMin[i].first << endl;
		}
	}
#endif
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int n, m;
		cin >> n >> m;

		vector<pair<long long int, int>> P(n);
		for (int i = 0; i < n; i++) {
			cin >> P[i].first;
			P[i].second = i;
		}

		sort(P.begin(), P.end());
		vector<pair<int, int>> boatIndexes(n);
		for (int i = 0; i < n; i++) {
			boatIndexes[i].first = P[i].second;
			boatIndexes[i].second = i;
		}

		auto MAX_VAL = pair<int, int>(numeric_limits<int>::max(), 0);
		RangeMinimumQuery<pair<int, int>> rmq(boatIndexes, MAX_VAL);

		long long int ret = 0;
		for (long long int i = 1; i <= m; i++) {
			long long int b;
			cin >> b;
			auto it = lower_bound(P.begin(), P.end(), make_pair(b, 0));
			if (it != P.end()) {
				int boatIndex = it - P.begin();
				auto firstBoat = rmq.query(boatIndex, n - 1);

				if (firstBoat != MAX_VAL) {
					ret += (firstBoat.first + 1) * i;
					rmq.update(firstBoat.second, MAX_VAL);
				}
			}
		}

		cout << ret << '\n';
	}

	return 0;
}

