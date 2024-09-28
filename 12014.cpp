#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T3>
class LIS {
private:
	const vector<T3> &seq;

public:
	LIS(const vector<T3> &s) : seq(s) {
	}

	int getMaxLen() {
		vector<T3> lis;
		lis.reserve(seq.size());

		int maxLen = 0;
		for (size_t i = 0; i < seq.size(); i++) {
			auto it = lower_bound(lis.begin(), lis.end(), seq[i]);
			if (it == lis.end()) {
				lis.push_back(seq[i]);
			}
			else {
				*it = seq[i];
			}
			maxLen = max(maxLen, static_cast<int>(lis.size()));
		}

		return maxLen;
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	for (int t = 1; t <= nTestcases; t++) {
		int N;
		int K;
		cin >> N >> K;
		vector<int> seq(N);

		for (int i = 0; i < N; i++) {
			cin >> seq[i];
		}

		LIS<int> lis(seq);
		cout << "Case #" << t << '\n';
		if (lis.getMaxLen() >= K) {
			cout << 1 << '\n';
		}
		else {
			cout << 0 << '\n';
		}
	}

	return 0;
}
