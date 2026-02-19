#include <algorithm>
#include <iostream>
#include <utility>
#include <cassert>

using namespace std;
using ll = long long int;

class Solve {
private:
	ll A, B, C;

public:
	Solve () {}

	void input() {
		cin >> A >> B >> C;
	}

	void solve() {
		ll cc = 0;
		ll prevcc = 0;
		ll previi = 0;
		ll i, digits;
		for (i = 1, digits = 1; i < 1000000000000000000ll; i *= 10, digits++) {
			if (i * 10 < A) {
				continue;
			}

			ll ii = (i * 10 - A) / B + 1;
			if ((i * 10 - A) % B > 0) {
				ii++;
			}

			if (ii > 1) {
				prevcc = cc;
				cc += (ii - 1 - previi) * digits;
				if (cc >= C) {
					break;
				}
				previi = ii - 1;
			}
			
		}

		ll remainc = C - prevcc;
		ll steps = remainc / digits;
		ll mod = remainc % digits;
		if (mod > 0) {
			steps++;
		}
		mod = (mod - 1 + digits) % digits;

		ll finali = previi + steps;
		ll finalnum = A + B * (finali - 1);
		ll finalint;
		for (ll iii = i, iiii = 0; iiii <= mod; iii /= 10, iiii++) {
			finalint = finalnum / iii;
			finalnum %= iii;
		}

        assert(finalint < 10);
		cout << finalint << '\n';
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
