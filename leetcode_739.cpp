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
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
		vector<int> ret(temperatures.size());

		stack<int, vector<int>> s;
		for (int i = 0; i < static_cast<int>(temperatures.size()); i++) {
			while (!s.empty() && temperatures[s.top()] < temperatures[i]) {
				auto t = s.top();
				s.pop();

				ret[t] = i - t;
			}
			s.push(i);
		}

		return ret;
    }
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<vector<int>> tcs = {
		{73,74,75,71,69,72,76,73},
		{30,40,50,60},
		{30, 60, 90},
		{89,62,70,58,47,47,46,76,100,70},
	};

	Solution s;
	for (auto tc : tcs) {
		auto r = s.dailyTemperatures(tc);
		for (auto n : r) {
			cout << n << ' ';
		}
		cout << endl;
	}

	return 0;
}
