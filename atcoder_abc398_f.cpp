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

// Palindrome, 펠린드롬 구하기
// ans[i]는 i번째를 를 중심으로 한 펠린드롬 반지름 길이가 저장됨
template <typename T>
void manacherAlgorithm(const vector<T> &arr, vector<int> &ans)
{
	ans.resize(arr.size());
	int r = -1;
	int p = -1;
	int n = static_cast<int>(arr.size());
	for (int i = 0; i < n; i++) {
		if (i <= r) {
			ans[i] = min(ans[2*p - i], r - i);
		}
		else {
			ans[i] = 0;
		}

		while (i - ans[i] - 1 >= 0 && i + ans[i] + 1 < n &&
				arr[i - ans[i] - 1] == arr[i + ans[i] + 1]) {
			ans[i]++;
		}

		if (i + ans[i] > r) {
			r = i + ans[i];
			p = i;
		}
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string S;
	cin >> S;
	int n = static_cast<int>(S.size());

	vector<char> ms;
	ms.reserve(n * 2);
	for (int i = 0; i < n; i++) {
		ms.push_back(S[i]);
		ms.push_back('#');
	}
	ms.pop_back();
	int nn = static_cast<int>(ms.size());

	vector<int> ma;
	manacherAlgorithm<char>(ms, ma);

	int preIdx = nn - 1;
	for (int k = preIdx - 1; k > 0; k--) {
		if (k + ma[k] == nn - 1) {
			preIdx = k - ma[k];
		}
	}

	cout << S;
	for (int i = preIdx - 2; i >= 0; i -= 2) {
		cout << ms[i];
	}
	cout << '\n';

	return 0;
}
