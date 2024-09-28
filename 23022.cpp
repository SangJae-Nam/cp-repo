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

	int n, S;
	vector<pair<int, int>> vt;
	priority_queue<pair<int, int>> q;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		cin >> n >> S;
		vt.resize(n);

		for (int i = 0; i < n; i++) {
			cin >> vt[i].first; //t
		}
		for (int i = 0; i < n; i++) {
			cin >> vt[i].second; //v
		}
		sort(vt.begin(), vt.end());

		int idx = 0;
		long long int t = S;
		long long int p = 0;

		while (idx < n || !q.empty()) {
			while (idx < n && vt[idx].first <= t) {
				q.push(make_pair(vt[idx].second, vt[idx].first));
				idx++;
			}

			if (q.empty()) {
				t = vt[idx].first;
				continue;
			}

			long long int nt = (idx < n) ? vt[idx].first : 2010000000;
			while (!q.empty() && t < nt) {
				auto &top = q.top();
				long long int cv = top.first;
				long long int ct = top.second;
				q.pop();

				p += (t - ct) * cv;
				t++;
			}
		}

		cout << p << '\n';
	}

	return 0;
}
