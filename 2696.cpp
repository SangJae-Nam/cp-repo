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

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int M;
		cin >> M;
		vector<int> ans;

		FindMidVal<int> fmd;
		for (int i = 1; i <= M; i++) {
			int n;
			cin >> n;

			fmd.push(n);
			if (i % 2 == 1) {
				ans.push_back(fmd.getMid());
			}
		}

		cout << ans.size() << '\n';
		for (size_t i = 1; i <= ans.size(); i++) {
			char sep = ' ';
			if (i % 10 == 0) {
				sep = '\n';
			}
			cout << ans[i - 1] << sep;
		}
		cout << '\n';
	}

	return 0;
}
