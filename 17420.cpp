#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include <sstream>
#include <cassert>

using namespace std;

template <typename T4>
class RMQ {
private:
	int size;
	vector<T4> range;  // start from 1

	const T4& init(const vector<T4> &array, int left, int right, int node) {
		if (left == right) {
			return range[node] = array[left];
		}

		int mid = (left + right) / 2;
		const T4& leftMin = init(array, left, mid, node * 2);
		const T4& rightMin = init(array, mid + 1, right, node * 2 + 1);

		return range[node] = min(leftMin, rightMin);
	}

	const T4 query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 아예 벗어난 경우
		if (right < nodeLeft || nodeRight < left) {
			return make_pair(1<<30, 1<<30);
		}

		// 완전히 포함 된 경우
		if (left <= nodeLeft && nodeRight <= right) {
			return range[node];
		}

		// 일부만 포함 된 경우 (분할정복)
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),	query(left, right, node * 2 + 1, mid + 1, nodeRight));
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
				min(update(index, newValue, node * 2, nodeLeft, mid),
				update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}

public:
	RMQ(const vector<T4> &array) {
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

	void print() {
		cout << "SEGTREE:" << endl;
		for (size_t i = 0; i < range.size(); i++) {
			cout << range[i] << ' ';
		}
		cout << endl;
	}
};

int calMul(int cur, int target)
{
	int diff = target - cur;
	int mul = diff / 30;
	if (diff % 30 != 0) {
		mul += 1;
	}

	//cout << cur << ", " << target << " = " << mul << endl;
	return mul;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<pair<int, int>> BA(N);
	for (int i = 0; i < N; i++) {
		cin >> BA[i].second;
	}

	long long int ret = 0;
	for (int i = 0; i < N; i++) {
		cin >> BA[i].first;

		auto &a = BA[i].second;
		auto &b = BA[i].first;
		if (b > a) {
			int mul = calMul(a, b);
			a += mul * 30;
			ret += mul;
		}
	}
	sort(BA.begin(), BA.end());

	vector<pair<int, int>> A(N);
	for (int i = 0; i < N; i++) {
		A[i] = make_pair(BA[i].second, i);
	}
	RMQ<pair<int, int>> rmq(A);

	for (int i = 0; i < N; i++) {
		auto &a = BA[i].second;
		auto &b = BA[i].first;

		//cout << a << ", " << b << endl;

		auto start = lower_bound(BA.begin() + i + 1, BA.end(), make_pair(b + 1, -1));
		if (start != BA.end()) {
			int s = start - BA.begin();
			pair<int, int> minA = rmq.query(s, N - 1);
			while (minA.first < a) {
				//cout << minA.first << ": " << a << endl;
				int mul = calMul(minA.first, a);
				rmq.update(minA.second, make_pair(minA.first + mul * 30, minA.second));
				BA[minA.second].second += mul * 30;
				ret += mul;

				minA = rmq.query(s, N - 1);
			}
		}
	}

	cout << ret << '\n';

	return 0;
}
