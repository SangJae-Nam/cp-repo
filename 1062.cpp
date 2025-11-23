#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>

using namespace std;

int run(const int K, int count, int startidx, int selected, int *used, const vector<int> &words)
{
	if (count == K) {
		int ret = 0;
		for (const int &w : words) {
			if ((selected & w) == w) {
				ret++;
			}
		}
		return ret;
	}

	int ret = 0;
	for (int i = startidx; i < 26; i++) {
		if (used[i] == 0) {
			continue;
		}

		if (((1<<i) & selected) == 0) {
			ret = max(ret, run(K, count + 1, i + 1, selected | (1<<i), used, words));
		}
	}
	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int used[26];
	memset(used, 0, sizeof(used));

	int N, K;
	cin >> N >> K;

	vector<int> words(N);
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		for (char c : s) {
			words[i] |= (1 << (c - 'a'));
			used[c - 'a'] = 1;
		}
	}

	if (K < 5) {
		cout << "0\n";
		return 0;
	}

	cout << run(K, 0, 0, 0, used, words) << '\n';

	return 0;
}
