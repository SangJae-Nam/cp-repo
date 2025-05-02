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

using mint = modint<1000000007, int>;

class Solve {
private:
	int N, M, P;
	long long int K;

	vector<int> C;
	vector<vector<int>> adj;
	vector<int> indegree;

public:
	Solve () {}

	void input() {
		cin >> N >> M >> P >> K;

		C.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> C[i];
			C[i]--;
		}

		adj.resize(N);
		indegree.resize(N);
		for (int i = 0; i < M; i++) {
			int x, y;
			cin >> x >> y;
			x--;
			y--;

			adj[x].push_back(y);
			indegree[y]++;
		}
	}

	void solve() {
		//Topological Sort
		set<pair<int, int>> q;
		for (int i = 0; i < N; i++) {
			if (indegree[i] == 0) {
				q.insert(make_pair(C[i], i));
			}
		}

		int s = N;
		mint ret = 0;
		long long int seq = 0;
		while (seq != K) {
			assert(seq < K);
			if (q.empty()) {
				ret += ((K - seq) * s) % 1000000007;
				break;
			}

			int pos = seq % P;
			auto it = q.lower_bound(make_pair(pos, 0));
			int len;
			int cur;
			if (it != q.end()) {
				cur = it->second;
				len = it->first - pos;
			}
			else {
				it = q.begin();
				cur = it->second;
				len = P - pos + it->first;
			}
			q.erase(it);

			ret += len * s;
			seq += len;
			if (seq > K) {
				ret -= ((seq - K) * s) % 1000000007;
				break;
			}
			s--;

			for (int next : adj[cur]) {
				indegree[next]--;
				if (indegree[next] == 0) {
					q.insert(make_pair(C[next], next));
				}
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

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		Solve s;
		s.input();
		s.solve();
	}

	return 0;
}
