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

using mint = modint<1000000007, int>;

class Solve {
private:
	int N, M;
	vector<vector<int>> adj;

	void dfs(int cur, int val, vector<mint> &dp, vector<bool> &visited) {
		visited[cur] = true;
		for (int next : adj[cur]) {
			if (!visited[next]) {
				dp[next] += val;
				dfs(next, val, dp, visited);
			}
		}
	}

public:
	Solve() {}

	void input() {
		cin >> N >> M;
		adj.resize(N + 1);

		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
		}
	}

	void solve() {
		TopologicalSort ts(adj);
		ts.sort();

		vector<mint> dp(N + 1, 1);
		for (int i = static_cast<int>(ts.ts.size()) - 1; i >= 0; i--) {
			int cur = ts.ts[i];
			vector<bool> visited(N + 1);
			dfs(cur, static_cast<int>(dp[cur].val()), dp, visited);
		}

		mint ret = 0;
		for (int i = 1; i <= N; i++) {
			ret += dp[i];
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
