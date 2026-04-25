#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <cstring>
#include <bitset>

using namespace std;
using ll = long long int;

constexpr int TL = 0;
constexpr int TR = 1;
constexpr int BL = 2;
constexpr int BR = 3;

constexpr int A = 0;
constexpr int B = 1;
constexpr int C = 2;
constexpr int D = 3;

class Solve {
private:
	int K;
	ll va, vb, vc, vd;

	ll dp2[31][4][4];
	void makeDP2() {
		memset(dp2, 0, sizeof(dp2));

		dp2[1][TL][D] = 1;
		dp2[1][TR][C] = 1;
		dp2[1][BL][B] = 1;
		dp2[1][BR][A] = 1;

		for (int i = 2; i <= 30; i++) {
			for (int j = 0; j < 4; j++) {
				dp2[i][TL][j] = dp2[i - 1][TL][j] * 2 + dp2[i - 1][TR][j] + dp2[i - 1][BL][j];
				dp2[i][TR][j] = dp2[i - 1][TR][j] * 2 + dp2[i - 1][TL][j] + dp2[i - 1][BR][j];
				dp2[i][BL][j] = dp2[i - 1][BL][j] * 2 + dp2[i - 1][TL][j] + dp2[i - 1][BR][j];
				dp2[i][BR][j] = dp2[i - 1][BR][j] * 2 + dp2[i - 1][TR][j] + dp2[i - 1][BL][j];
			}
			dp2[i][TL][D]++;
			dp2[i][TR][C]++;
			dp2[i][BL][B]++;
			dp2[i][BR][A]++;
		}
	}

	pair<ll, ll> run2(int k, ll a, ll b, ll c, ll d) {
		//cout << k << ", " << a << ", " << b << ", " << c << ", " << d << endl;
		ll aa = (1ll<<(2*k)) - 1;
		if (aa % 3 != 0) {
			return make_pair(-1, -1);
		}
		if (aa / 3 != a + b + c + d) {
			return make_pair(-1, -1);
		}

		if (k == 1) {
			if (a == 1) {
				return make_pair(1, 1);
			}
			else if (b == 1) {
				return make_pair(1, 0);
			}
			else if (c == 1) {
				return make_pair(0, 1);
			}
			else if (d == 1) {
				return make_pair(0, 0);
			}
			assert(false);
		}

		pair<ll, int> order[4];
		order[0] = make_pair(a, A);
		order[1] = make_pair(b, B);
		order[2] = make_pair(c, C);
		order[3] = make_pair(d, D);
		sort(order, order + 4);

		int i = -1;
		for (int l = 3; l >= 0; l--) {
			if (l < 3 && order[l].first < order[3].first) {
				break;
			}

			switch (order[l].second) {
				case A:
					if (d == order[0].first) {
						i = D;
					}
					break;
				case B:
					if (c == order[0].first) {
						i = C;
					}
					break;
				case C:
					if (b == order[0].first) {
						i = B;
					}
					break;
				case D:
					if (a == order[0].first) {
						i = A;
					}
					break;
			}
		}
		if (i == -1) {
			return make_pair(-1, -1);
		}

		ll prime[4] = {a, b, c, d};
		switch (i) {
			case A:
			{
				auto &r2 = dp2[k - 1][BL];
				auto &r3 = dp2[k - 1][TR];
				auto &r4 = dp2[k - 1][TL];
				for (int j = 0; j < 4; j++) {
					prime[j] -= r2[j];
					prime[j] -= r3[j];
					prime[j] -= r4[j];
				}
				prime[D]--;
				bool failed = false;
				for (int j = 0; j < 4; j++) {
					if (prime[j] < 0) {
						failed = true;
						break;
					}
				}
				if (failed) {
					return make_pair(-1, -1);
				}
				auto ret = run2(k - 1, prime[0], prime[1], prime[2], prime[3]);
				if (ret.first != -1 && ret.second != -1) {
					return ret;
				}
				break;
			}
			case B:
			{
				auto &r1 = dp2[k - 1][BR];
				auto &r3 = dp2[k - 1][TR];
				auto &r4 = dp2[k - 1][TL];
				for (int j = 0; j < 4; j++) {
					prime[j] -= r1[j];
					prime[j] -= r3[j];
					prime[j] -= r4[j];
				}
				prime[C]--;
				bool failed = false;
				for (int j = 0; j < 4; j++) {
					if (prime[j] < 0) {
						failed = true;
						break;
					}
				}
				if (failed) {
					return make_pair(-1, -1);
				}
				auto ret = run2(k - 1, prime[0], prime[1], prime[2], prime[3]);
				if (ret.first != -1 && ret.second != -1) {
					ret.second += (1 << (k-1));
					return ret;
				}
				break;
			}
			case C:
			{
				auto &r1 = dp2[k - 1][BR];
				auto &r2 = dp2[k - 1][BL];
				auto &r4 = dp2[k - 1][TL];
				for (int j = 0; j < 4; j++) {
					prime[j] -= r1[j];
					prime[j] -= r2[j];
					prime[j] -= r4[j];
				}
				prime[B]--;
				bool failed = false;
				for (int j = 0; j < 4; j++) {
					if (prime[j] < 0) {
						failed = true;
						break;
					}
				}
				if (failed) {
					return make_pair(-1, -1);
				}
				auto ret = run2(k - 1, prime[0], prime[1], prime[2], prime[3]);
				if (ret.first != -1 && ret.second != -1) {
					ret.first += (1 << (k-1));
					return ret;
				}
				break;
			}
			case D:
			{
				auto &r1 = dp2[k - 1][BR];
				auto &r2 = dp2[k - 1][BL];
				auto &r3 = dp2[k - 1][TR];
				for (int j = 0; j < 4; j++) {
					prime[j] -= r1[j];
					prime[j] -= r2[j];
					prime[j] -= r3[j];
				}
				prime[A]--;
				bool failed = false;
				for (int j = 0; j < 4; j++) {
					if (prime[j] < 0) {
						failed = true;
						break;
					}
				}
				if (failed) {
					return make_pair(-1, -1);
				}
				auto ret = run2(k - 1, prime[0], prime[1], prime[2], prime[3]);
				if (ret.first != -1 && ret.second != -1) {
					ret.first += (1 << (k-1));
					ret.second += (1 << (k-1));
					return ret;
				}
				break;
			}
			default:
				assert(false);
		}
		return make_pair(-1, -1);
	}

public:
	Solve () {
		makeDP2();
	}

	void input() {
		cin >> K >> va >> vb >> vc >> vd;
	}

	void solve() {
		auto ret = run2(K, va, vb, vc, vd);
		cout << ret.first << ' ' << ret.second << '\n';
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

