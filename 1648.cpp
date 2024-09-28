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

using mint = modint<9901, unsigned short>;

static unsigned short N, M;
vector<vector<mint>> dp;

mint solve(int idx, int line)
{
	if (idx == N * M && line == 0) {
		return mint(1);
	}
	else if (idx >= N * M) {
		return mint(0);
	}

    mint &ret = dp[idx][line];
    if (ret != -1) {
        return ret;
    }

	if ((line & 1) == 1) {
		return solve(idx + 1, line >> 1);
	}
	else {
		ret = 0;
		int col = idx % M;

		if (((line & 3) == 0) && (col < M - 1)) {
			ret += solve(idx + 2, line >> 2);
		}
		ret += solve(idx + 1, (line >> 1) | (1 << (M-1)));

    	return ret;
	}
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    if (N % 2 == 1 && M % 2 == 1) {
        cout << 0 << '\n';
    }
    else {
        dp.resize((N+1) * (M+1), vector<mint>(1<<M, -1));
        cout << solve(0, 0).val() << '\n';
    }

    return 0;
}

