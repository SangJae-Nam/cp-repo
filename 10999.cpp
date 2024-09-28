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

S op(S l, S r)
{
	return S{l.a + r.a, l.size + r.size};
}

S e()
{
	return S{0, 0};
}

S mapping(F l, S r)
{
	return S{r.a + l.a * r.size, r.size};
}

F composition(F l, F r)
{
	return F{l.a + r.a};
}

F id()
{
	return F{0};
}

int main(int argc, char *argv[])
{
	int N, M, K;
	cin >> N >> M >> K;

	vector<S> A(N);
	for (int i = 0; i < N; i++) {
		long long int x;
		cin >> x;
		A[i] = S{x, 1};
	}

	LazySegtree<S, op, e, F, mapping, composition, id> seg(A);

	for (int i = 0; i < (M + K); i++) {
		int k;
		cin >> k;
		if (k == 1) {
			int l, r;
			long long int b;
			cin >> l >> r >> b;
			l--; r--;
			seg.apply(l, r + 1, F{b});
		}
		else {
			int l, r;
			cin >> l >> r;
			l--; r--;
			cout << seg.query(l, r + 1).a << '\n';
		}
	}

	return 0;
}
