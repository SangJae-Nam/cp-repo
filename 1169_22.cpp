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

#if 0
//그래프에서 줄 : 양끝 차수가 1만 있고, 차수가 2인게 0개이상
//그래프에서 원 : 차수가 2인것만 존재할 때
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

using namespace std;

constexpr int CIRCLE = 10000000;
constexpr int LINE = 10000000;
int N, M;
vector<vector<pair<int, int>>> adj;
vector<bool> visited;

int dfs(int cur, int prev, int first, int length, bool &adjIsTwo, map<int, int> &adjCnt)
{
	int maxLength = length;
	visited[cur] = true;
	adjIsTwo = adjIsTwo && (adj[cur].size() == 2);
	adjCnt[adj[cur].size()]++;

	for (auto &next : adj[cur]) {
		if (!visited[next.first]) {
			int len = dfs(next.first, cur, first, length + 1, adjIsTwo, adjCnt);
			if (len == CIRCLE && adjIsTwo) {
				return CIRCLE;
			}
			else {
				maxLength = max(maxLength, len);
			}
		}
		else {
			if (next.first != prev && next.first == first && adjIsTwo) {
				return CIRCLE;
			}
		}
	}

	return maxLength;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;
	adj.resize(N + 1);
	visited.resize(N + 1);

	for (int i = 0; i < M; i++) {
		int x, y, w;
		cin >> x >> y >> w;

		adj[x].push_back(make_pair(y, w));
		adj[y].push_back(make_pair(x, w));
	}

	int numOfLines = 0;
	int numOfCircles = 0;
	for (int i = 1; i <= N; i++) {
		if (!visited[i]) {
			map<int, int> adjCnt;
			bool adjIsTwo = true;
			int len = dfs(i, 0, i, 0, adjIsTwo, adjCnt);

			if (len == CIRCLE && adjIsTwo) {
				numOfCircles++;
			}
			else if (adjCnt.size() == 1) {
				if (adjCnt.count(1) && adjCnt[1] == 2) {
					numOfLines++;
				}
			}
			else if (adjCnt.size() == 2) {
				if (adjCnt.count(1) && adjCnt[1] == 2 && adjCnt.count(2)) {
					numOfLines++;
				}
			}
		}
	}

	cout << 1 << ' ' << abs(numOfCircles - numOfLines) << '\n';

	return 0;
}
#endif

// modint
// modint<1000000007, int> b(1000000000);
template<int m, typename T6>
class modint {
private:
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

private:
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

// https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
int binomialCoeff(int n, int r)
{
	if (r > n)
		return 0;
	long long int m = 1000000007;
	long long int inv[r + 1] = { 0 };
	inv[0] = 1;
	if(r+1>=2)
		inv[1] = 1;

	// Getting the modular inversion
	// for all the numbers
	// from 2 to r with respect to m
	// here m = 1000000007
	for (int i = 2; i <= r; i++) {
		inv[i] = m - (m / i) * inv[m % i] % m;
	}

	int ans = 1;

	// for 1/(r!) part
	for (int i = 2; i <= r; i++) {
		ans = ((ans % m) * (inv[i] % m)) % m;
	}

	// for (n)*(n-1)*(n-2)*...*(n-r+1) part
	for (int i = n; i >= (n - r + 1); i--) {
		ans = ((ans % m) * (i % m)) % m;
	}
	return ans;
}

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
private:
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
private:
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
};

void Eratos(int n, vector<unsigned char> &isPrime)
{
    /*  만일 n이 1보다 작거나 같으면 함수 종료 */
    if (n <= 1) return;

    /*  2부터 n까지 n-1개를 저장할 수 있는 배열 할당
    배열 참조 번호와 소수와 일치하도록 배열의 크기는
    n+1 길이만큼 할당(인덱스 번호 0과 1은 사용하지 않음)    */
    /*  배열초기화: 처음엔 모두 소수로 보고 true값을 줌 */
	isPrime.clear();
	isPrime.resize(n + 1, 1);
	isPrime[0] = isPrime[1] = 0;

    /*  에라토스테네스의 체에 맞게 소수를 구함
        만일, PrimeArray[i]가 true이면 i 이후의 i 배수는 약수로 i를
        가지고 있는 것이 되므로 i 이후의 i 배수에 대해 false값을 준다.
        PrimeArray[i]가 false이면 i는 이미 소수가 아니므로 i의 배수 역시
        소수가 아니게 된다. 그러므로 검사할 필요도 없다.
또한 i*k (k < i) 까지는 이미 검사되었으므로 j시작 값은 i*2에서 i*i로 개선할 수 있다.
    */

	int sqrtn = int(sqrt(n));
    for (int i = 2; i <= sqrtn; i++)
    {
		if (isPrime[i])
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = 0;
    }
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	priority_queue<pair<int, int>> A;
	vector<pair<int, int>> B;

	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		A.push(make_pair(-a, i));
	}
	for (int i = 0; i < N; i++) {
		cin >> B[i].first;
		B[i].second = i;
	}
	sort(B.begin(), B.end());

	long long int ret = 0;
	for (int i = 0; i < N; i++) {
		int day = B[i].first;
		int ai = B[i].second;

		while(!A.empty()) {
			auto a = A.top();
			A.pop();

			a.first = -a.first;
			if (a.second != ai) {
				int delta = 
			}
		}
	}

	return 0;
}
