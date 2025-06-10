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

class LIS {
private:
public:
	vector<int> lengths;
	vector<int> maxSeq;
	int maxLength;

	void make(const vector<int> &input, bool makeLengthArr = false, bool track = false) {
		int size = static_cast<int>(input.size());

		if (makeLengthArr) {
			lengths.resize(size);
		}

		vector<int> lis;
		lis.reserve(size);
		maxLength = 0;

		vector<int> lisIndex;
		if (track) {
			lisIndex.resize(size);
		}

		for (int i = 0; i < size; i++) {
			int len;
			auto it = lower_bound(lis.begin(), lis.end(), input[i]);
			if (it == lis.end()) {
				lis.push_back(input[i]);
				len = static_cast<int>(lis.size());
			}
			else {
				*it = input[i];
				len = static_cast<int>(it - lis.begin()) + 1;
			}

			maxLength = max(maxLength, len);
			if (makeLengthArr) {
				lengths[i] = len;
			}
			if (track) {
				lisIndex[i] = len - 1;
			}
		}

		if (track) {
			maxSeq.resize(maxLength);
			int retIdx = maxLength - 1;
			for (int i = size - 1; i >= 0; i--) {
				if (lisIndex[i] == retIdx) {
					maxSeq[retIdx] = input[i];
					retIdx--;
				}
			}
		}
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<pair<int, int>> AB(N);
	for (int i = 0; i < N; i++) {
		cin >> AB[i].first >> AB[i].second;
	}
	sort(AB.begin(), AB.end());

	unordered_map<int, int> b2aidx;
	for (int i = 0; i < N; i++) {
		b2aidx[AB[i].second] = i;
	}

	vector<int> B(N);
	for (int i = 0; i < N; i++) {
		B[i] = AB[i].second;
	}

	LIS lis;
	lis.make(B, false, true);

	vector<bool> reserve(N);
	for (int i = 0; i < lis.maxLength; i++) {
		reserve[b2aidx[lis.maxSeq[i]]] = true;
	}

	cout << N - lis.maxLength << '\n';
	for (int i = 0; i < N; i++) {
		if (!reserve[i]) {
			cout << AB[i].first << '\n';
		}
	}

	return 0;
}
