#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;

	vector<int> lis;
	vector<int> lisIdx;
	vector<int> prev(n, -1);
	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++) {
		int &num = arr[i];

		auto it = lower_bound(lis.begin(), lis.end(), num);
		if (it == lis.end()) {
			if (!lisIdx.empty()) {
				prev[i] = *lisIdx.rbegin();
			}
			lis.push_back(num);
			lisIdx.push_back(i);
		}
		else {
			if (*it > num) {
				int idx = static_cast<int>(it - lis.begin());
				if (idx > 0) {
					prev[i] = lisIdx[idx - 1];
				}
				else {
					prev[i] = -1;
				}

				*it = num;
				lisIdx[idx] = i;
			}
		}
	}

	vector<int> ans;
	ans.reserve(lis.size());
	int curIdx = *lisIdx.rbegin();
	while (curIdx >= 0) {
		ans.push_back(arr[curIdx]);
		curIdx = prev[curIdx];
	}

	cout << lis.size() << '\n';
	for (auto it = ans.rbegin(); it != ans.rend(); it++) {
		cout << *it << ' ';
	}
	cout << '\n';

	return 0;
}
