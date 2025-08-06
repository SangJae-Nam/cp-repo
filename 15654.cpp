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

void run(const vector<int> &arr, int M, bitset<8> &sel, vector<int> &ret)
{
	int N = static_cast<int>(arr.size());
	if (sel.count() == M) {
		for (int n : ret) {
			cout << n << ' ';
		}
		cout << '\n';
		return;
	}

	for (int i = 0; i < N; i++) {
		if (sel[i]) {
			continue;
		}
		ret.push_back(arr[i]);
		sel[i] = true;
		run(arr, M, sel, ret);
		sel[i] = false;
		ret.pop_back();
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;
	vector<int> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());

	bitset<8> sel;
	vector<int> ret;
	run(arr, M, sel, ret);

	return 0;
}
