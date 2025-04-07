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
#include <cstring>

using namespace std;

class Solution {
private:
	int dp[10][2500][82];

	void generateNumbers(int num, vector<int> &o) {
		while (num > 0) {
			o.push_back(num % 10);
			num /= 10;
		}
	}

	int calc(int idx, int mul, int sum, int front, const vector<int> &numbers) {
		if (idx < 0) {
			if (sum == 0) {
				return 0;
			}
			return (mul % sum == 0) ? 1 : 0;
		}

		if (mul < 2500 && !front) {
			if (dp[idx][mul][sum] != -1) {
				return dp[idx][mul][sum];
			}
		}

		int end;
		if (front) {
			end = numbers[idx];
		}
		else {
			end = 9;
		}

		int ret = 0;
		for (int i = 0; i < end; i++) {
			int newMul = (sum + i) ? mul * i : 1;
			ret += calc(idx - 1, newMul, sum + i, 0, numbers);
		}
		int newFront = front ? 1 : 0;
		ret += calc(idx - 1, mul * end, sum + end, newFront, numbers);

		if (mul < 2500 && !front) {
			dp[idx][mul][sum] = ret;
		}
		return ret;
	}

public:
    int beautifulNumbers(int l, int r) {
		vector<int> numL, numR;
		generateNumbers(l - 1, numL);
		generateNumbers(r, numR);
		
		memset(dp, -1, sizeof(dp));

		int rr = calc(numR.size() - 1, 1, 0, 1, numR);
		int ll = calc(numL.size() - 1, 1, 0, 1, numL);

		cout << rr << endl << ll << endl;

		return rr - ll;
    }
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution s;
	cout << s.beautifulNumbers(10, 20) << endl;
	cout << s.beautifulNumbers(1, 15) << endl;
	cout << s.beautifulNumbers(20, 100) << endl;
	cout << s.beautifulNumbers(10, 1000) << endl;  // 325
	cout << s.beautifulNumbers(5940, 79658243) << endl;  // 50232826

	return 0;
}
