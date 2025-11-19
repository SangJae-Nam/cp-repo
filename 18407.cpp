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

int bitCeil(int n)
{
	int ret = 1;
	while (ret < n) {
		ret <<= 1;
	}
	return ret;
}

int countRightZero(unsigned int n)
{
#ifdef _MSC_VER
	unsigned long index;
	_BitScanForward(&index, n);
	return index;
#else
	// LSB부터 왼쪽으로 이동하여 1이 나오기 직전까지의 0의 개수를 반환
	// LSB 포함
	// 00000000 00000000 00000000 00010000 : 4
	return __builtin_ctz(n);
#endif
}


#if __cplusplus >= 201703L

template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
class LazySegtree {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
		"op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
			"e must work as S()");
	static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>,
			"mapping must work as S(F, S)");
	static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
			"composition must work as F(F, F)");
	static_assert(std::is_convertible_v<decltype(id), std::function<F()>>,
			"id must work as F()");

#else

class LazySegtree {

#endif
private:
	int arrSize;
	int bot;
	int logSize;

	vector<S> range;
	vector<F> lz;
	void update(int k) {
		range[k] = op(range[2 * k], range[2 * k + 1]);
	}
	void all_apply(int k, F f) {
		range[k] = mapping(f, range[k]);
		if (k < bot) {
			lz[k] = composition(f, lz[k]);
		}
	}
	void push(int k) {
		all_apply(2 * k, lz[k]);
		all_apply(2 * k + 1, lz[k]);
		lz[k] = id();
	}

public:
	LazySegtree() : LazySegtree(0) {}
	explicit LazySegtree(int n) : LazySegtree(vector<S>(n, e())) {}
	explicit LazySegtree(const vector<S> &v) : arrSize(static_cast<int>(v.size())) {
		bot = bitCeil(arrSize);
		logSize = countRightZero(bot);

		range = vector<S>(2 * bot, e());
		lz = vector<F>(bot, id());

		for (int i = 0; i < arrSize; i++) {
			range[bot + i] = v[i];
		}

		for (int i = bot - 1; i >= 1; i--) {
			update(i);
		}
	}

	void set(int p, S x) {
		assert(0 <= p && p < arrSize);
		p += bot;
		for (int i = logSize; i >= 1; i--) {
			push(p >> i);
		}
		range[p] = x;
		for (int i = 1; i <= logSize; i++) {
			update(p >> i);
		}
	}

	S get(int p) {
		assert(0 <= p && p < arrSize);
		p += bot;
		for (int i = logSize; i >= 1; i--) {
			push(p >> i);
		}
		return range[p];
	}

	S query(int left, int right) {  // [left, right)
#ifdef __DEBUG__
		if (left < 0 || left >= size) {
			cout << "Left is out of bound " << left << endl;
			assert(false);
		}
		if (right < 0 || right >= size) {
			cout << "Right is out of bound " << left << endl;
			assert(false);
		}
#endif
		if (left == right) {
			return e();
		}

		left += bot;
		right += bot;

		for (int i = logSize; i >= 1; i--) {
			if (((left >> i) << i) != left) {
				push(left >> i);
			}
			if (((right >> i) << i) != right) {
				push((right - 1) >> i);
			}
		}

		S resultRight = e();
		S resultLeft = e();

		while (left < right) {
			if (left & 1) {
				resultLeft = op(resultLeft, range[left++]);
			}
			if (right & 1) {
				resultRight = op(range[--right], resultRight);
			}

			left >>= 1;
			right >>= 1;
		}

		return op(resultLeft, resultRight);
	}

	S allQuery() {
		return range[1];
	}

	void apply(int p, F f) {
		assert(0 <= p && p < arrSize);
		p += bot;
		for (int i = logSize; i >= 1; i--) {
			push(p >> i);
		}
		range[p] = mapping(f, range[p]);
		for (int i = 1; i <= logSize; i++) {
			update(p >> i);
		}
	}
	
	void apply(int left, int right, F f) { //[left, right)
		assert(0 <= left && left <= right  && right <= arrSize);
		if (left == right) {
			return;
		}

		left += bot;
		right += bot;

		for (int i = logSize; i >= 1; i--) {
			if (((left >> i) << i) != left) {
				push(left >> i);
			}
			if (((right >> i) << i) != right) {
				push((right - 1) >> i);
			}
		}

		{
			int l2 = left;
			int r2 = right;
			while (left < right) {
				if (left & 1) {
					all_apply(left++, f);
				}
				if (right & 1) {
					all_apply(--right, f);
				}
				left >>= 1;
				right >>= 1;
			}
			left = l2;
			right = r2;
		}

		for (int i = 1; i <= logSize; i++) {
			if (((left >> i) << i) != left) {
				update(left >> i);
			}
			if (((right >> i) << i) != right) {
				update((right - 1) >> i);
			}
		}
	}
};

struct S {
	int a;
};

struct F {
	int a;
};

S op(S l, S r)
{
	return S{max(l.a, r.a)};
}

S e()
{
	return S{0};
}

S mapping(F l, S r)
{
	return S{max(r.a, l.a)};
}

F composition(F l, F r)
{
	return F{max(l.a, r.a)};
}

F id()
{
	return F{0};
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<int> W(N), D(N);
	vector<int> points;
	points.reserve(N * 2);

	for (int i = 0; i < N; i++) {
		cin >> W[i] >> D[i];

		points.push_back(D[i]);
		points.push_back(D[i] + W[i]);
	}
	sort(points.begin(), points.end());
	unordered_map<int, int> conv;
	int convlen = static_cast<int>(points.size());
	for (int i = 0; i < convlen; i++) {
		if (conv.count(points[i]) > 0) {
			continue;
		}
		conv[points[i]] = i;
	}

	LazySegtree<S, op, e, F, mapping, composition, id> seg(convlen);
	for (int i = 0; i < N; i++) {
		int start = conv[D[i]];
		int end = conv[D[i] + W[i]];
		int h = seg.query(start, end).a;
		seg.apply(start, end, F{h + 1});
	}
	cout << seg.query(0, convlen).a << '\n';

	return 0;
}
