#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

int run(const int K, int idx, int selected, const vector<int> &words)
{
	if (__builtin_popcount(selected) == K) {
		int ret = 0;
		for (const int &w : words) {
			if ((selected & w) == w) {
				ret++;
			}
		}
		return ret;
	}

	if (idx >= 26) {
		return 0;
	}

	int ret = 0;
	if (idx < 26) {
		ret = max(ret, run(K, idx + 1, selected | (1<<idx), words));
		ret = max(ret, run(K, idx + 1, selected, words));
	}
	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, K;
	cin >> N >> K;

	vector<int> words(N);
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		for (char c : s) {
			words[i] |= (1 << (c - 'a'));
		}
	}

	if (K < 5) {
		cout << "0\n";
		return 0;
	}

	cout << run(K, 0, 0, words) << '\n';

	return 0;
}
