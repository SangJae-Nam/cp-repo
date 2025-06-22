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

	int N;
	cin >> N;
	vector<int> B(N);
	for (int i = 0; i < N; i++) {
		cin >> B[i];
	}

	vector<int> b;
	b.reserve(N);
	for (int i = 0; i < N; i++) {
		auto it = lower_bound(b.begin(), b.end(), B[i]);
		if (it == b.end()) {
			b.push_back(B[i]);
		}
		else {
			*it = B[i];
		}
	}
	
	cout << N - static_cast<int>(b.size()) << '\n';

	return 0;
}
