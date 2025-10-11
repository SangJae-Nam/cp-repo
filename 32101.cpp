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

// modint<1000000007, int> b(1000000000);
using mint = modint<1000000007, int>;

class Solve {
private:
	int NA, MA, NB, MB;
	vector<bool> S[2];
	vector<vector<int>> adj[2];

	static constexpr int AFTER = 1;
	static constexpr int BEFORE = 2;

	int dfs(int cur, int prev, int tree, int status) {
		if (status == AFTER) {
			if (S[tree][cur]) {
				return 0;
			}
			else {
				int ret = 1;  // self
				for (int next : adj[tree][cur]) {
					if (next == prev) {
						continue;
					}
					ret += dfs(next, cur, tree, status);
				}
				return ret;
			}
		}
		else {
			int newStatus = S[tree][cur] ? AFTER : BEFORE;
			int ret = 0;
			for (int next : adj[tree][cur]) {
				if (next == prev) {
					continue;
				}
				ret += dfs(next, cur, tree, newStatus);
			}
			if (newStatus == AFTER) {
				ret++;  // self
			}
			return ret;
		}
	}

public:
	Solve () {}

	void input() {
		cin >> NA >> MA;
		S[0].clear();
		S[0].resize(NA);
		for (int i = 0; i < MA; i++) {
			int s;
			cin >> s;
			s--;
			S[0][s] = true;
		}
		adj[0].clear();
		adj[0].resize(NA);
		for (int i = 0; i < NA - 1; i++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			adj[0][a].push_back(b);
			adj[0][b].push_back(a);
		}

		cin >> NB >> MB;
		S[1].clear();
		S[1].resize(NB);
		for (int i = 0; i < MB; i++) {
			int s;
			cin >> s;
			s--;
			S[1][s] = true;
		}
		adj[1].clear();
		adj[1].resize(NB);
		for (int i = 0; i < NB - 1; i++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			adj[1][a].push_back(b);
			adj[1][b].push_back(a);
		}
	}

	void solve() {
		vector<mint> b(NB);

		mint ret = 0;
		for (int na = 0; na < NA; na++) {
			mint sa = dfs(na, -1, 0, BEFORE);
			for (int nb = 0; nb < NB; nb++) {
				mint sb;
				if (na == 0) {
					sb = dfs(nb, -1, 1, BEFORE);
					b[nb] = sb;
				}
				else {
					sb = b[nb];
				}
				mint sab = sa * sb;
				ret += sab * (na+1 + nb+1);
			}
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

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}
