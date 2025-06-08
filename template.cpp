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
using pii = pair<int, int>;

class PrefixSum2D {
private:
	int row;
	int col;
	vector<vector<long long int>> arr;

public:
	PrefixSum2D() {}

	//좌표는 1부터 시작
	void init(vector<vector<int>> &input) {
		row = static_cast<int>(input.size());
		col = static_cast<int>(input[0].size());

		arr.resize(row);
		for (int r = 0; r < row; r++) {
			arr[r].resize(col);
			for (int c = 1; c < col; c++) {
				arr[r][c] += arr[r][c - 1] + input[r][c];
			}
		}

		for (int c = 0; c < col; c++) {
			for (int r = 1; r < row; r++) {
				arr[r][c] += arr[r - 1][c];
			}
		}
	}

	long long int sum(int x1, int y1, int x2, int y2) {
		assert(x1 <= x2 && y1 <= y2);

		long long int ret = arr[y2][x2];
		ret -= arr[y2][x1 - 1];
		ret -= arr[y1 - 1][x2];
		ret += arr[y1 - 1][x1 - 1];

		return ret;
	}
};


// Palindrome, 펠린드롬 구하기
// ans[i]는 i번째를 를 중심으로 한 펠린드롬 반지름 길이가 저장됨
template <typename T>
void manacherAlgorithm(const vector<T> &arr, vector<int> &ans)
{
	ans.resize(arr.size());
	int r = -1;
	int p = -1;
	int n = static_cast<int>(arr.size());
	for (int i = 0; i < n; i++) {
		if (i <= r) {
			ans[i] = min(ans[2*p - i], r - i);
		}
		else {
			ans[i] = 0;
		}

		while (i - ans[i] - 1 >= 0 && i + ans[i] + 1 < n &&
				arr[i - ans[i] - 1] == arr[i + ans[i] + 1]) {
			ans[i]++;
		}

		if (i + ans[i] > r) {
			r = i + ans[i];
			p = i;
		}
	}
}

class TopologicalSort2 {  // Queue를 이용한 위상정렬
private:
	vector<vector<int>> &adj;
	vector<int> &indegree; // 진입차수

public:
	TopologicalSort2(vector<vector<int>> &a, vector<int> &i) : adj(a), indegree(i) {
		ts.reserve(a.size());
	}

	void sort() {
		int size = static_cast<int>(adj.size());
		priority_queue<int> q;

		for (int i = 1; i < size; i++) {
			if (indegree[i] == 0) {
				q.push(-i);
			}
		}

		while (!q.empty()) {
			int cur = -q.top();
			q.pop();

			for (int next : adj[cur]) {
				indegree[next]--;
				if (indegree[next] == 0) {
					q.push(-next);
				}
			}

			ts.push_back(cur);
		}
	}

	vector<int> ts; // 순서대로 들어감
};

class TopologicalSort {
private:
	vector<vector<int>> &adj;
	vector<bool> visited;

	void dfs(int cur) {
		visited[cur] = true;

		for (int next : adj[cur]) {
			if (!visited[next]) {
				dfs(next);
			}
		}

		ts.push_back(cur);
	}

public:
	TopologicalSort(vector<vector<int>> &a) : adj(a) {
		visited.resize(a.size());
		ts.reserve(a.size());
	}

	void sort() {
		for (int i = 1; i < static_cast<int>(adj.size()); i++) {
			if (!visited[i]) {
				dfs(i);
			}
		}
	}

	vector<int> ts;  // 역순이 위상정렬
};

// 실시간으로 중간값을 구하는 클래스
// 원소 개수가 짝수면 작은 값 리턴
template <typename T9>
class FindMidVal
{
private:
	priority_queue<T9, vector<T9>, less<T9>> lower;  //top이 높은거
	priority_queue<T9, vector<T9>, greater<T9>> upper;  //top이 낮은거

public:
	FindMidVal() {
		lower.push(numeric_limits<T9>::min());
		upper.push(numeric_limits<T9>::max());
	}

	void push(T9 &val) {
		if (val <= lower.top()) {
			lower.push(val);
		}
		else {
			upper.push(val);
		}

		int diff = static_cast<int>(lower.size()) - static_cast<int>(upper.size());
		if (diff > 1) {
			upper.push(lower.top());
			lower.pop();
		}
		else if (diff < -1) {
			lower.push(upper.top());
			upper.pop();
		}
	}

	T9 getMid() {
		T9 mid = lower.top();
		if (upper.size() > lower.size()) {
			mid = upper.top();
		}
		return mid;
	}
};


/* p1 -> p2 -> p3의 외적을 통해 시계/반시계/직전여부를 구함
   > 0 : 반시계방향
   = 0 : 직선
   < 0 : 시계방향
   */
long long int ccw(const pii &p1, const pii &p2, const pii &p3)
{
	//(x2 - x1)(y3 - y1) - (x3 - x1)(y2 - y1)
	auto &[x1, y1] = p1;
	auto &[x2, y2] = p2;
	auto &[x3, y3] = p3;

	return static_cast<long long int>((x2 - x1)) * (y3 - y1) - (x3- x1) * (y2 - y1);
}

// Andrew's algorithm을 이용한 블록껍질(Convex Hull)을 구함
void getConvexHull(vector<pii> &points, vector<pii> &output)
{
	int psize = static_cast<int>(points.size());
	sort(points.begin(), points.end());
	output.reserve(psize);

	// 위쪽
	output.push_back(points[0]);
	output.push_back(points[1]);
	for (int i = 2; i < psize; i++) {
		size_t os;
		while ((os = output.size()) >= 2) {
			auto dir = ccw(output[os - 2], output[os - 1], points[i]);
			if (dir >= 0) {
				output.pop_back();
			}
			else {
				break;
			}
		}
		output.push_back(points[i]);
	}

	// 아래쪽
	output.push_back(points[psize - 2]);
	size_t upperSize = output.size();
	for (int i = psize - 3; i >= 0; i--) {
		size_t os;
		while ((os = output.size()) >= upperSize) {
			auto dir = ccw(output[os - 2], output[os - 1], points[i]);
			if (dir >= 0) {
				output.pop_back();
			}
			else {
				break;
			}
		}
		output.push_back(points[i]);
	}

	//제일 마지막은 제일 첫번째와 같으므로 삭제
	output.pop_back();
}

class BipartiteMatch {
	public:
		BipartiteMatch(int lSize, int rSize) : leftSize(lSize), rightSize(rSize) {
			adj.resize(lSize, vector<bool>(rSize));
			leftMatch.resize(lSize, -1);
			rightMatch.resize(rSize, -1);
		}

		void addEdge(int left, int right) {
			adj[left][right] = true;
		}

		int bipartiteMatch() {
			int size = 0;
			for (int left = 0; left < leftSize; left++) {
				visited = vector<bool>(leftSize, false);
				if (dfs(left)) {
					size++;
				}
			}

			return size;
		}

		void print() {
			for (int l = 0; l < leftSize; l++) {
				for (int r = 0; r < rightSize; r++) {
					cout << (adj[l][r] ? '1' : '0') << ' ';
				}
				cout << '\n';
			}
		}

	private:
		int leftSize;
		int rightSize;
		vector<vector<bool>> adj;
		vector<int> leftMatch;
		vector<int> rightMatch;
		vector<bool> visited;

		bool dfs(int left) {
			if (visited[left]) {
				return false;
			}
			visited[left] = true;

			for (int right = 0; right < rightSize; right++) {
				if (adj[left][right]) {
					if (rightMatch[right] == -1 || dfs(rightMatch[right])) {
						leftMatch[left] = right;
						rightMatch[right] = left;
						return true;
					}
				}
			}
			return false;
		}
};

// 서로 다른 두 노드 사이에 간선이 2개 이상이면 사용하지 못함
// -> 두 간선을 합치면 됨
class MaxFlowMatrix {
	public:
		MaxFlowMatrix(int s) : size(s) {
			capacity = vector<vector<int>>(s, vector<int>(s));
			flow = vector<vector<int>>(s, vector<int>(s));
		}

		void addEdge(int s, int e, int c) {
			capacity[s][e] = c;
		}

		int calculateFlow(int source, int sink) {
			int totalFlow = 0;

			while (true) {
				int f = bfs(source, sink);
				if (f <= 0) {
					break;
				}
				totalFlow += f;
			}

			return totalFlow;
		}

	private:
		int size;
		vector<vector<int>> capacity;
		vector<vector<int>> flow;

		int bfs(const int source, const int sink) {
			vector<int> parent(size, -1);
			queue<int> q;
			parent[source] = source;
			q.push(source);

			while (!q.empty() && parent[sink] == -1) {
				int here = q.front();
				q.pop();

				for (int there = 0; there < size; there++) {
					if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
						q.push(there);
						parent[there] = here;
					}
				}
			}

			if (parent[sink] == -1) {
				return 0;
			}

			int amount = numeric_limits<int>::max();
			for (int p = sink; p != source; p = parent[p]) {
				amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
			}

			for (int p = sink; p != source; p = parent[p]) {
				flow[parent[p]][p] += amount;
				flow[p][parent[p]] -= amount;
			}

			return amount;
		}
};

long long int exp_mod(long long int a, long long int b, long long int mod) // a^b % mod
{
	assert(b >= 0);
	long long int r = 1;
	while (b) {
		if (b & 1) {
			r = (r * a) % mod;
		}
		a = (a * a) % mod;
		b >>= 1;
	}

	return r;
}

// 분수
template<typename T7>
class computefraction {
private:
	T7 top;
	T7 bot;

public:
	computefraction(T7 t = 0, T7 b = 1) : top(t), bot(b) {
		assert(b != 0);

		T7 reduce = gcd(top, bot);
		top /= reduce;
		bot /= reduce;
	}

	computefraction operator+(const computefraction &rhs) const {
		T7 t = top * rhs.bot + rhs.top * bot;
		T7 b = bot * rhs.bot;

		return computefraction<T7>(t, b);
	}

	computefraction operator-(const computefraction &rhs) const {
		T7 t = top * rhs.bot - rhs.top * bot;
		T7 b = bot * rhs.bot;

		return computefraction<T7>(t, b);
	}

	bool operator<(const computefraction &rhs) const {
		T7 reduce = gcd(bot, rhs.bot);
		T7 lcm = bot * rhs.bot / reduce;

		T7 left = top * (lcm / bot);
		T7 right = rhs.top * (lcm / rhs.bot);

		return left < right;
	}

	void print() {
		if (bot > 1) {
			cout << top << '/' << bot << '\n';
		}
		else {
			cout << top << '\n';
		}
	}
};

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

	modint (long long int v = 0) {
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

	bool operator<(const modint& rhs) const {
		return mVal < rhs.mVal;
	}

	bool operator>(const modint& rhs) const {
		return mVal > rhs.mVal;
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

// 페르마 소정리를 이용한 펙토리얼과 펙토리얼의 역원 계산
template<int m, typename T6>
void getFermatCompute(vector<modint<m, T6>> &facts, vector<modint<m, T6>> &invfacts, int size)
{
	facts.resize(size);
	invfacts.resize(size);

	facts[0] = 1;
	invfacts[0] = 1;

	for (int i = 1; i < size; i++) {
		facts[i] = facts[i - 1] * i;
		invfacts[i] = facts[i].pow(m - 2);
	}
}

// r < m 일 떄만 작동함
template<int m, typename T6>
class binomialCoeffMod
{
public:
	int size;
	vector<modint<m, T6>> facts;
	vector<modint<m, T6>> invfacts;

	binomialCoeffMod(int _size) : size(_size) {
		getFermatCompute(facts, invfacts, size);
	}

	modint<m, T6> ncr(int n, int r) {
		assert(n < size);
		assert(r < m);

		return facts[n] * (invfacts[r] * invfacts[n - r]);
	}
};

// r < m 일 떄만 작동함
template<int m, typename T6>
modint<m, T6> ncr(int n, int r)
{
    assert(r < m);

    if (n - r < r) {
        r = n - r;
    }

    // N * (N - 1) * ... * (N - R + 1)
    modint<m, T6> n2nr = 1;
    // R!
    modint<m, T6> factR = 1;
    for (int i = 0; i < r; i++) {
        n2nr *= (n - i);
        factR *= (i + 1);
    }

    // (R!)^-1 == (R!)^(m - 2)
    modint<m, T6> invFactR = factR.pow(m - 2);

    return n2nr * invFactR;
}

// 뤼카의 정리
template<int m, typename T6>
modint<m, T6> ncrLucas(long long int n, long long int r)
{
    assert(r < m);

    if (n - r < r) {
        r = n - r;
    }

	modint<m, T6> ret = 1;
	while (n > 0 || r > 0) {
		long long int nn = n % m;
		long long int rr = r % m;

		if (nn < rr) {
			return modint<m, T6>(0);
		}

		ret *= ncr<m, T6>(nn, rr);

		n /= m;
		r /= m;
	}

	return ret;
}

// z[i] = str[i]에서 시작하는 부분 문자열이면서 str의 prefix이기도 한 가장 긴 문자열의 길이
void zAlgorithm(const string &str, vector<int> &z)
{
    int len = static_cast<int>(str.size());
    int l = 0;
    int r = 0;

	z.resize(len, 0);

    for (int i = 1; i < len; i++) {
        if (i > r) {
            l = r = i;
            while (r < len && str[r - l] == str[r]) {
                r++;
            }
            z[i] = r - l;
            r--;
        }
        else {
            if (z[i - l] < r - i + 1) {
                z[i] = z[i - l];
            }
            else {
                l = i;
                while (r < len && str[r - l] == str[r]) {
                    r++;
                }
                z[i] = r - l;
                r--;
            }
        }
    }
}

// https://en.wikipedia.org/wiki/Alternating_permutation
// https://www.geeksforgeeks.org/entringer-number/
// https://mathworld.wolfram.com/EntringerNumber.html
class Zigzag {
public:
	Zigzag (int sz) {
		maxSize = sz + 1;
		dp.resize(maxSize, vector<long long int>(maxSize, -1));
	}

	// An -> up/down/up/.... from (1 to n) == E(n, n)
	long long int numberOfZigzag(int n) {
		if (n <= maxSize) {
			return entringerNumber(n, n);
		}
		else {
			return -1;
		}
	}

protected:
	int maxSize;
	vector<vector<long long int>> dp;

	// Return Entringer Number E(n, k)
	long long int entringerNumber(int n, int k) {
		// Base case
		if (k == 0) {
			if (n == 0) {
				return 1;
			}
			else {
				return 0;
			}
		}

		long long int &ret = dp[n][k];
		if (ret != -1) {
			return ret;
		}

		ret = entringerNumber(n, k - 1) + entringerNumber(n - 1, n - k);
		return ret;
	}
};

template <typename T5>
class FenwickTree {
protected:
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

template <typename T5>
class SparseTableMin {
protected:
	vector<T5> &arr;
	vector<vector<int>> spt; //Sparse Table N * logN

	bool op(T5 &a, T5 &b) {
		return a < b;
	}

public:
	SparseTableMin(vector<T5> &_arr) : arr(_arr) {
		int size = static_cast<int>(arr.size());
		int log2size = static_cast<int>(ceil(log(static_cast<double>(size)) / log(2.0))) + 1;
		spt.resize(size, vector<int>(log2size));
		for (size_t i = 0; i < arr.size(); i++) {
			spt[i][0] = i;
		}

		for (int j = 1; (1<<j) <= size; j++) {
			for (int i = 0; i + (1<<j) - 1 < size; i++) {
				if (op(arr[spt[i][j - 1]], arr[spt[i + (1<<(j-1))][j - 1]])) {
					spt[i][j] = spt[i][j - 1];
				}
				else {
					spt[i][j] = spt[i + (1<<(j-1))][j - 1];
				}
			}
		}
	}

	int query(int i, int j) {
		if (i > j) {
			swap(i, j);
		}

		int k = static_cast<int>(floor(log(static_cast<double>(j - i + 1)) / log(2.0)));
		if (op(arr[spt[i][k]], arr[spt[j - (1<<k) + 1][k]])) {
			return spt[i][k];
		}
		else {
			return spt[j - (1<<k) + 1][k];
		}
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


#if __cplusplus >= 201703L

template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
class LazySegtree {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
		"op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
			"e must work as S()");
	static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>,
			"mapping must work as S(F, S)");
	static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
			"composition must work as F(F, F)");
	static_assert(std::is_convertible_v<decltype(id), std::function<F()>>,
			"id must work as F()");

#else

class LazySegtree {

#endif
private:
	int arrSize;
	int bot;
	int logSize;

	vector<S> range;
	vector<F> lz;
	void update(int k) {
		range[k] = op(range[2 * k], range[2 * k + 1]);
	}
	void all_apply(int k, F f) {
		range[k] = mapping(f, range[k]);
		if (k < bot) {
			lz[k] = composition(f, lz[k]);
		}
	}
	void push(int k) {
		all_apply(2 * k, lz[k]);
		all_apply(2 * k + 1, lz[k]);
		lz[k] = id();
	}

public:
	LazySegtree() : LazySegtree(0) {}
	explicit LazySegtree(int n) : LazySegtree(vector<S>(n, e())) {}
	explicit LazySegtree(const vector<S> &v) : arrSize(static_cast<int>(v.size())) {
		bot = bitCeil(arrSize);
		logSize = countRightZero(bot);

		range = vector<S>(2 * bot, e());
		lz = vector<F>(bot, id());

		for (int i = 0; i < arrSize; i++) {
			range[bot + i] = v[i];
		}

		for (int i = bot - 1; i >= 1; i--) {
			update(i);
		}
	}

	void set(int p, S x) {
		assert(0 <= p && p < arrSize);
		p += bot;
		for (int i = logSize; i >= 1; i--) {
			push(p >> i);
		}
		range[p] = x;
		for (int i = 1; i <= logSize; i++) {
			update(p >> i);
		}
	}

	S get(int p) {
		assert(0 <= p && p < arrSize);
		p += bot;
		for (int i = logSize; i >= 1; i--) {
			push(p >> i);
		}
		return range[p];
	}

	S query(int left, int right) {  // [left, right)
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
		if (left == right) {
			return e();
		}

		left += bot;
		right += bot;

		for (int i = logSize; i >= 1; i--) {
			if (((left >> i) << i) != left) {
				push(left >> i);
			}
			if (((right >> i) << i) != right) {
				push((right - 1) >> i);
			}
		}

		S resultRight = e();
		S resultLeft = e();

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

	S allQuery() {
		return range[1];
	}

	void apply(int p, F f) {
		assert(0 <= p && p < arrSize);
		p += bot;
		for (int i = logSize; i >= 1; i--) {
			push(p >> i);
		}
		range[p] = mapping(f, range[p]);
		for (int i = 1; i <= logSize; i++) {
			update(p >> i);
		}
	}
	
	void apply(int left, int right, F f) { //[left, right)
		assert(0 <= left && left <= right  && right <= arrSize);
		if (left == right) {
			return;
		}

		left += bot;
		right += bot;

		for (int i = logSize; i >= 1; i--) {
			if (((left >> i) << i) != left) {
				push(left >> i);
			}
			if (((right >> i) << i) != right) {
				push((right - 1) >> i);
			}
		}

		{
			int l2 = left;
			int r2 = right;
			while (left < right) {
				if (left & 1) {
					all_apply(left++, f);
				}
				if (right & 1) {
					all_apply(--right, f);
				}
				left >>= 1;
				right >>= 1;
			}
			left = l2;
			right = r2;
		}

		for (int i = 1; i <= logSize; i++) {
			if (((left >> i) << i) != left) {
				update(left >> i);
			}
			if (((right >> i) << i) != right) {
				update((right - 1) >> i);
			}
		}
	}
};

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

template <typename T4, const T4 (*op)(const T4 &a, const T4 &b), const T4 (*endFunc)()>
class SegmentTree {
protected:
	int size;
	int bot;
	vector<T4> range;  // start from 1

	const T4& init(const vector<T4> &array, int left, int right, int node) {
		if (left == right) {
			return range[node] = array[left];
		}

		int mid = (left + right) / 2;
		const T4& l = init(array, left, mid, node * 2);
		const T4& r = init(array, mid + 1, right, node * 2 + 1);

		return range[node] = op(l, r);
	}

	const T4 query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 아예 벗어난 경우
		if (right < nodeLeft || nodeRight < left) {
			return endFunc();
		}

		// 완전히 포함 된 경우
		if (left <= nodeLeft && nodeRight <= right) {
			return range[node];
		}

		// 일부만 포함 된 경우 (분할정복)
		int mid = (nodeLeft + nodeRight) / 2;
		return op(query(left, right, node * 2, nodeLeft, mid),
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
				op(update(index, newValue, node * 2, nodeLeft, mid),
				update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}

public:
	SegmentTree(const vector<T4> &array) {
		size = static_cast<int>(array.size());
		bot = bitCeil(size);
		int treeSize = size * 4;
		//int treeSize = static_cast<int>(ceil(log2(size)));
		//treeSize = 2 * static_cast<int>(pow(2, treeSize)) - 1;
		//cout << "Tree size : " << treeSize << endl;
		range.resize(treeSize, endFunc());
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

	T4 get(int index) {
#ifdef __DEBUG__
		if (index < 0 || index >= size) {
			cout << "Index is out of bound " << index << endl;
			assert(false);
		}
#endif
		return range[index + bot];
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

// Least Common Ancester (최소공통조상)
class LCA
{
public:
	LCA(vector<vector<int>> &_adj, int root = 1) : adj(_adj) {
		ettDepth.reserve(adj.size() * 2);
		ettNode.reserve(adj.size() * 2);
		ettIndexTable.resize(adj.size(), -1);
		ettIdx = 0;
		dfs(-1, root, 1);

		sparseTable = new SparseTableMin<int>(ettDepth);
	}

	virtual ~LCA() {
		delete sparseTable;
	}

	int getLCA(int a, int b) {
		int idxA = ettIndexTable[a];
		int idxB = ettIndexTable[b];

		if (idxA > idxB) {
			swap(idxA, idxB);
		}

		int idxLCA = sparseTable->query(idxA, idxB);
		return ettNode[idxLCA];
	}

	void printETT() {
		for (auto n : ettNode) {
			cout << n << ' ';
		}
		cout << endl;
		for (auto n : ettDepth) {
			cout << n << ' ';
		}
		cout << endl;
	}

protected:
	vector<vector<int>> &adj;
	
	//Euler Tour Tree
	vector<int> ettDepth;
	vector<int> ettNode;
	vector<int> ettIndexTable;

	SparseTableMin<int> *sparseTable;

	int ettIdx;
	void dfs(int prev, int cur, int depth) {
		ettDepth.push_back(depth);
		ettNode.push_back(cur);
		if (ettIndexTable[cur] == -1) {
			ettIndexTable[cur] = ettIdx;
		}
		ettIdx++;

		for (int next : adj[cur]) {
			if (next == prev) {
				continue;
			}

			dfs(cur, next, depth + 1);
		
			ettDepth.push_back(depth);
			ettNode.push_back(cur);
			ettIdx++;
		}
	}
};

template <typename T1>
class SquareMatrix {
public:
	static void _mul(const vector<vector<T1>> &op1, const vector<vector<T1>> &op2, vector<vector<T1>> &res) {
		for (size_t i = 0; i < res.size(); i++) {
			for (size_t j = 0; j < res.size(); j++) {
				T1 val = 0;
				for (size_t k = 0; k < res.size(); k++) {
					val += op1[i][k] * op2[k][j];
				}
				res[i][j] = val;
			}
		}
	}

	vector<vector<T1>> mat;
	SquareMatrix(size_t n, bool unitMatrix = false) {
		mat.resize(n, vector<T1>(n, 0));
		if (unitMatrix) {
			for (size_t i = 0; i < n; i++) {
				mat[i][i] = 1;
			}
		}
	}


	void mul(const SquareMatrix &other) {
		_mul(mat, other.mat, mat);
	}

	SquareMatrix operator*(const SquareMatrix& obj) {
		SquareMatrix res(mat.size());
		_mul(mat, obj.mat, res.mat);
		return res;
	}

	SquareMatrix exp(long long int x) {
		SquareMatrix res(mat.size(), true);
		SquareMatrix cur(*this);

		while (x > 0) {
			if (x % 2 == 0) {
				cur = cur * cur;
				x /= 2;
			}
			else {
				res = res * cur;
				x--;
			}
		}

		return res;
	}

	void print() {
		for (size_t i = 0; i < mat.size(); i++) {
			for (size_t j = 0; j < mat.size(); j++) {
				cout << mat[i][j] << ' ';
			}
			cout << '\n';
		}
	}
};

template <typename T2>
T2 fibo(T2 n)
{
	SquareMatrix<T2> fiboMatrix(2);
	fiboMatrix.mat[0][0] = 1;
	fiboMatrix.mat[0][1] = 1;
	fiboMatrix.mat[1][0] = 1;
	fiboMatrix.mat[1][1] = 0;

	SquareMatrix<T2> exp = fiboMatrix.exp(n - 1);
	// Fn+1 Fn
	// Fn   Fn-1
	return exp.mat[0][0];
}

template <typename T>
class simpleQ {
protected:
	vector<T> buf;
	size_t index;

public:
	simpleQ() {
		index = 0;
	}

	T front() {
		assert(!empty());
		return buf[index];
	}

	T top() {
		return front();
	}

	void pop() {
		index++;
	}

	void push(T item) {
		buf.push_back(item);
	}

	size_t size() {
		return buf.size();
	}

	bool empty() {
		return buf.size() <= index;
	}
};

class UnionFind
{
protected:
	vector<int> parent;
	vector<int> size;

public:
	UnionFind(int n) : parent(n + 1), size(n + 1, 1) {
		for (int i = 0; i <= n; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] == x) {
			return x;
		}

		return parent[x] = find(parent[x]);
	}

	bool same(int a, int b) {
		return find(a) == find(b);
	}

	void unite(int a, int b) {
		a = find(a);
		b = find(b);

		if (a == b) {
			return;
		}

		if (size[a] < size[b]) {
			swap(a, b);
		}

		parent[b] = a;
		size[a] += size[b];
	}

	int getSize(int x) {
		assert(x <= static_cast<int>(parent.size()));
		return size[find(x)];
	}
};

class Eratos
{
public:
	int size;
	vector<bool> isPrime;
	vector<int> primes;

	Eratos(int n) {
		size = n + 1;
		init();
	}

	void init() {
		isPrime.resize(size, true);

		/*  만일 n이 1보다 작거나 같으면 함수 종료 */
		if (size <= 1) return;

		/*  2부터 n까지 n-1개를 저장할 수 있는 배열 할당
		배열 참조 번호와 소수와 일치하도록 배열의 크기는
		n+1 길이만큼 할당(인덱스 번호 0과 1은 사용하지 않음)	*/
		/*  배열초기화: 처음엔 모두 소수로 보고 true값을 줌 */
		isPrime[0] = isPrime[1] = false;

		/*  에라토스테네스의 체에 맞게 소수를 구함
			만일, PrimeArray[i]가 true이면 i 이후의 i 배수는 약수로 i를
			가지고 있는 것이 되므로 i 이후의 i 배수에 대해 false값을 준다.
			PrimeArray[i]가 false이면 i는 이미 소수가 아니므로 i의 배수 역시
			소수가 아니게 된다. 그러므로 검사할 필요도 없다.
			또한 i*k (k < i) 까지는 이미 검사되었으므로 j시작 값은 i*2에서 i*i로 개선할 수 있다.
		*/

		for (int i = 2; i * i < size; i++)
		{
			if (isPrime[i]) {
				for (int j = i * i; j < size; j += i) {
					isPrime[j] = false;
				}
			}
		}
	}

	void initPrimes() {
		primes.reserve(size);
		for (int i = 0; i < size; i++) {
			if (isPrime[i]) {
				primes.push_back(i);
			}
		}
	}
};

// n!에서 prime은 몇 제곱을 갖고 있는지 구함
int primeExpInFact(int n, int prime)
{
	int exp = 0;
	while (n > 0) {
		n /= prime;
		exp += n;
	}
	return exp;
}

// nCr을 소수의 몇 제곱으로 구성됐는지 구함
map<int, int> ncrPrimes(int n, int r, const vector<int> &primes)
{
	map<int, int> ret;
	for (int p : primes) {
		if (p > n) {
			break;
		}

		int exp = primeExpInFact(n, p) - primeExpInFact(r, p) - primeExpInFact(n - r, p);
		assert(exp >= 0);
		if (exp > 0) {
			ret[p] = exp;
		}
	}
	return ret;
}

class Solve {
private:
public:
	Solve () {}

	void input() {
	}

	void solve() {
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
	}

	return 0;
}
