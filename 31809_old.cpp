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

using pii = pair<int, int>;

// modint
// modint<1000000007, int> b(1000000000);
template<int m, typename T6>
class modint {
protected:
	unsigned int mVal;

	static constexpr unsigned int umod() {
		return m;
	}

public:
	static constexpr int mod() {
		return m;
	}

	modint (T6 v = 0) {
		mVal = static_cast<unsigned int>(v % umod());
	}

	unsigned int val() const {
		return mVal;
	}

	modint& operator++() {
		mVal++;
		if (mVal == umod()) {
			mVal = 0;
		}
		return *this;
	}

	modint& operator--() {
		if (mVal == 0) {
			mVal = umod();
		}
		mVal--;
		return *this;
	}

	modint operator++(int) {
		modint result = *this;
		++*this;
		return result;
	};

	modint operator--(int) {
		modint result = *this;
		--*this;
		return result;
	}

	modint& operator+=(const modint& rhs) {
		mVal += rhs.mVal;
		if (mVal >= umod()) {
			mVal -= umod();
		}
		return *this;
	}

	modint& operator-=(const modint& rhs) {
		mVal -= rhs.mVal;
		if (mVal >= umod()) {
			mVal += umod();
		}
		return *this;
	}

	modint& operator*=(const modint& rhs) {
		unsigned long long z = mVal;
		z *= rhs.mVal;
		mVal = static_cast<unsigned int>(z % umod());
		return *this;
	}

	modint& operator/=(const modint& rhs) {
		mVal /= rhs.mVal;
		return *this;
	}

	modint operator+() const {
		return *this;
	}

	modint operator-() const {
		return modint() - *this;
	}

	modint operator+(const modint& rhs) const {
		return modint(*this) += rhs;
	}

	modint operator-(const modint& rhs) const {
		return modint(*this) -= rhs;
	}

	modint operator*(const modint& rhs) const {
		return modint(*this) *= rhs;
	}

	modint operator/(const modint& rhs) const {
		return modint(*this) /= rhs;
	}

	bool operator==(const modint& rhs) const {
		return mVal == rhs.mVal;
	}

	bool operator!=(const modint& rhs) const {
		return mVal != rhs.mVal;
	}

	friend istream& operator>>(istream &in, modint &rhs) {
		in >> rhs.mVal;
		return in;
	}

	friend ostream& operator<<(ostream &out, const modint &rhs) {
		out << rhs.mVal;
		return out;
	}

	modint pow(long long int n) const {
		assert(0 <= n);
		modint x = *this;
		modint r = 1;
		while (n) {
			if (n & 1) {
				r *= x;
			}
			x *= x;
			n >>= 1;
		}

		return r;
	}
};

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

const pii _min(const pii &a, const pii &b)
{
	return min(a, b);
}

const pii _minEnd()
{
	return pii(numeric_limits<int>::max(), numeric_limits<int>::max());
}

class Solve {
private:
	int N, M, P;
	long long int K;

	vector<int> C;
	vector<int> timeToNode;
	vector<vector<int>> adj;
	SegmentTree2<pii, _min, _minEnd> *radj;
	int remainNodes;

	pair<int, int> nextVaccine(int curDate) {
		auto next = radj->query(curDate, P + 1);
		if (next.first != 0) {
			return make_pair(numeric_limits<int>::max(), -1);
		}
		else {
			return make_pair(next.second, timeToNode[next.second]);
		}
	}

	void removeNode(int i) {
		remainNodes--;

		for (auto next : adj[i]) {
			int nextTime = C[next];
			auto cur = radj->get(nextTime);
			cur.first--;
			radj->update(nextTime, cur);
		}
		adj[i].clear();
		radj->update(C[i], _minEnd());
	}

public:
	Solve() : radj(nullptr) {}
	~Solve() {
		if (radj != nullptr) {
			delete radj;
		}
	}

	void input() {
		cin >> N >> M >> P >> K;

		C.resize(N + 1);
		timeToNode.resize(P + 1);
		for (int i = 1; i <= N; i++) {
			cin >> C[i];
			timeToNode[C[i]] = i;
		}

		adj.resize(N + 1);
		radj = new SegmentTree2<pii, _min, _minEnd>(P + 1);
		for (int i = 0; i <= P; i++) {
			if (timeToNode[i] != 0) {
				radj->update(i, make_pair(0, i));
			}
		}

		for (int i = 0; i < M; i++) {
			int s, e;
			cin >> s >> e;

			adj[s].push_back(e);
			auto cur = radj->get(C[e]);
			cur.first++;
			radj->update(C[e], cur);
		}
		remainNodes = N;
	}

	unsigned int solve() {
		modint<1000000007, int> ret;
		for (long long int i = 1; i <= K;) {
			if (remainNodes == 0) {
				break;
			}

			int cur = static_cast<int>(i % P);
			if (cur == 0) {
				cur = P;
			}

			pair<int, int> upcoming;
			int nextDate;
			int nextNode;
			if (cur == 1) {
				upcoming = nextVaccine(0);
				nextDate = upcoming.first;
				nextNode = upcoming.second;
				if (nextDate == 1) {
					removeNode(nextNode);
				}
				else if (nextNode == -1) {
					ret += (remainNodes * (K - i + 1)) % 1000000007;
					break;
				}
			}
			upcoming = nextVaccine(cur);
			nextDate = upcoming.first;
			nextNode = upcoming.second;

			int duration;
			if (nextNode != -1) {
				duration = nextDate - cur;
			}
			else {
				duration = P - cur + 1;
			}

			if (i + duration > K) {
				duration -= (i + duration - K - 1);
			}
			ret += remainNodes * duration;

			if (nextNode != -1) {
				removeNode(nextNode);
			}
			i += duration;
		}

		return ret.val();
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		Solve s;
		s.input();
		cout << s.solve() << '\n';
	}

	return 0;
}

