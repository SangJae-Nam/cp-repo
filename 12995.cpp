#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <numeric>
#include <cassert>
#include <cstring>

using namespace std;

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

using mint = modint<1000000007, int>;

class Solve {
private:
	int N, K;
	vector<vector<int>> adj;
	vector<vector<int>> tree;
	int dp[50][51][50];

	void makeTree(int cur, int prev) {
		for (int next : adj[cur]) {
			if (next != prev) {
				tree[cur].push_back(next);
				makeTree(next, cur);
			}
		}
	}

	int dfs(int cur, int num, int startSon) {
		if (num <= 1) {
			return 1;
		}

		if (startSon == tree[cur].size()) {
			return 0;
		}

		int &ans = dp[cur][num][startSon];
		if (ans != -1) {
			return ans;
		}

		mint ret = 0;
		for (int i = 0; i < num; i++) {
			mint t1 = dfs(tree[cur][startSon], i, 0);
			mint t2 = dfs(cur, num - i, startSon + 1);
			ret += t1 * t2;
		}

		ans = static_cast<int>(ret.val());
		return ans;
	}

public:
	Solve () {}

	void input() {
		cin >> N >> K;
		adj.resize(N);
		tree.resize(N);
		for (int i = 0; i < N - 1; i++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}

	void solve() {
		memset(dp, -1, sizeof(dp));
		makeTree(0, -1);
		mint ret = 0;
		for (int i = 0; i < N; i++) {
			ret += dfs(i, K, 0);
		}
		cout << ret << '\n';
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
