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
void manacherAlgorithm(const vector<int> &str, vector<int> &ans)
{
	ans.resize(str.size());
	int r = -1;
	int p = -1;
	int n = static_cast<int>(str.size());
	for (int i = 0; i < n; i++) {
		if (i <= r) {
			ans[i] = min(ans[2*p - i], r - i);
		}
		else {
			ans[i] = 0;
		}

		while (i - ans[i] - 1 >= 0 && i + ans[i] + 1 < n &&
				str[i - ans[i] - 1] == str[i + ans[i] + 1]) {
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

	int N;
	cin >> N;
	vector<int> seq;
	seq.reserve(N * 2);
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		seq.push_back(n);
		seq.push_back('#');
	}
	seq.pop_back();

	vector<int> ans;
	manacherAlgorithm(seq, ans);

	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int s, e;
		cin >> s >> e;
		s--;
		e--;
		s *= 2;
		e *= 2;
		int mid = (s + e) / 2;

		if (s == e) {
			cout << "1\n";
		}
		else {
			if (mid - ans[mid] <= s && mid + ans[mid] >= e) {
				cout << "1\n";
			}
			else {
				cout << "0\n";
			}
		}
	}

	return 0;
}
