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

using namespace std;

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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int N, M;
		cin >> N >> M;

		vector<computefraction<long long int>> cats(N);
		int v, a;
		for (int i = 0; i < M; i++) {
			cin >> v;
			for (int j = 0; j < N; j++) {
				cin >> a;
				cats[j] = cats[j] + computefraction<long long int>(a, v);
			}
		}
		sort(cats.begin(), cats.end());
		computefraction<long long int> ret = *cats.rbegin() - *cats.begin();
		ret.print();
	}

	return 0;
}
