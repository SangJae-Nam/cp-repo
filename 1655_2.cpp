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

// 실시간으로 중간값을 구하는 클래스
// 원소 개수가 짝수면 작은 값 리턴
template <typename T9>
class FindMidVal
{
private:
	priority_queue<T9, vector<T9>, less<T9>> lower;  //top이 높은거
	priority_queue<T9, vector<T9>, greater<T9>> upper;  //top이 낮은거

public:
	FindMidVal() {
		lower.push(numeric_limits<T9>::min());
		upper.push(numeric_limits<T9>::max());
	}

	void push(T9 &val) {
		if (val <= lower.top()) {
			lower.push(val);
		}
		else {
			upper.push(val);
		}

		int diff = static_cast<int>(lower.size()) - static_cast<int>(upper.size());
		if (diff > 1) {
			upper.push(lower.top());
			lower.pop();
		}
		else if (diff < -1) {
			lower.push(upper.top());
			upper.pop();
		}
	}

	T9 getMid() {
		T9 mid = lower.top();
		if (upper.size() > lower.size()) {
			mid = upper.top();
		}
		return mid;
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	FindMidVal<short> fmd;
	for (int i = 0; i < N; i++) {
		short n;
		cin >> n;

		fmd.push(n);
		cout << fmd.getMid() << '\n';
	}

	return 0;
}
