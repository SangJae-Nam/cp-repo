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
#include <stack>
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

using mint = modint<1000000007, int>;

class Solve {
private:
	int N;
	vector<int> H;
	vector<vector<int>> adj;
	vector<mint> sum;

	int dfs(int cur) {
		int count = 1;

		for (int next : adj[cur]) {
			int subcount = dfs(next);
			mint d = subcount;
			d *= (N - subcount);
			d *= (H[cur] - H[next]);
			d *= (H[cur] - H[next]);
			sum[cur] += d;

			count += subcount;
		}

		return count;
	}

public:
	Solve () {}

	void input() {
		cin >> N;
		H.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> H[i];
		}
	}

	void solve() {
		adj.resize(N);

		int root = H[0];
		int rootIdx = 0;
		stack<int>> stk;
		for (int i = 0; i < N; i++) {
			if (root < H[i]) {
				root = H[i];
				rootIdx = i;
			}

			int last = -1;
			while (!stk.empty() && H[stk.top()] < H[i]) {
				auto t = stk.top();
				stk.pop();

				if (last != -1) {
					adj[t].push_back(last);
				}

				last = t;
			}

			if (last != -1) {
				adj[i].push_back(last);
			}

			stk.push(i);
		}

		if (!stk.empty()) {
			int last = -1;
			while (!stk.empty()) {
				auto t = stk.top();
				stk.pop();

				if (last != -1) {
					adj[t].push_back(last);
				}
				last = t;
			}
		}

		sum.resize(N);
		dfs(rootIdx);

		mint ret = 0;
		for (auto n : sum) {
			ret += n;
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
