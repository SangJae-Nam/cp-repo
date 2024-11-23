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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long int L;
	int N, K;
	cin >> L >> N >> K;
	vector<long long int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	vector<int> ans;
	ans.reserve(K);
	for (int i = 0; i < N && ans.size() < K; i++) {
		ans.push_back(0);
	}

	while (ans.size() < K) {
		for (int k = 1; k <= K && ans.size() < K; k++) {
			for (int i = 0; i < N && ans.size() < K; i++) {
				//+
				if (i < N - 1) {
					if (A[i] + k <= A[i + 1] - k) {
						ans.push_back(k);
						if (ans.size() >= K) {
							break;
						}
					}
				}
				else {
					if (A[i] + k <= L) {
						ans.push_back(k);
						if (ans.size() >= K) {
							break;
						}
					}
				}

				//-
				if (i > 0) {
					if (A[i] - k > A[i - 1] + k) {
						ans.push_back(k);
						if (ans.size() >= K) {
							break;
						}
					}
				}
				else {
					if (A[i] - k >= 0) {
						ans.push_back(k);
						if (ans.size() >= K) {
							break;
						}
					}
				}
			}
		}
	}

	for (int a : ans) {
		cout << a << '\n';
	}

	return 0;
}
