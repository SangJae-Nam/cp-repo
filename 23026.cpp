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

	short n, B;
	long long int R;
	vector<short> v;
	string sep = "A";

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		cin >> n >> B >> R;
		v.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}

		long long int ret = 1;
		long long int startI = 0;
		int cur = 0;
		bool cycle = false;
		string curKey;
		unordered_map<string, pair<long long int, long long int>> buckets;

		for (long long int i = 0; i < n * R; i++) {
			int vi = i % n;
			if (B - cur >= v[vi]) {
				cur += v[vi];
				curKey += to_string(v[vi]) + sep;
			}
			else {
				if (!cycle && buckets.count(curKey) != 0) {
					cycle = true;

					long long int stepI = startI - buckets[curKey].first;
					long long int stepR = ret - buckets[curKey].second;

					long long int mul = ((n * R) - buckets[curKey].first) / stepI;

					i = buckets[curKey].first + (stepI * mul);
					ret = buckets[curKey].second - 1 + (stepR * mul);

					if (i < n * R) {
						i--;
						ret++;
					
						curKey.clear();
						cur = 0;
						startI = i + 1;
					}
					continue;
				}
				
				buckets[curKey] = make_pair(startI, ret);
				ret++;
				startI = i;

				curKey = to_string(v[vi]) + sep;
				cur = v[vi];
			}
		}

		cout << ret << '\n';
	}

	return 0;
}
