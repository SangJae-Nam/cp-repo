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

class Solution {
private:
	vector<int> *pNums;
	vector<int> *pAndValues;
	vector<vector<map<int, int>>> dp;
	int numsSize;
	int andsSize;
	const int MAX_VALUE = 200000000;
	const int INIT_MASK = 0x7FFFFFFF;

	int divideArray(int seq, int idx, int andVal) {
		if (seq == andsSize && idx == numsSize) {
			return 0;
		}
		if (seq == andsSize || idx == numsSize) {
			return MAX_VALUE;
		}

		if (dp[seq][idx].count(andVal) > 0) {
			return dp[seq][idx][andVal];
		}

		dp[seq][idx][andVal] = MAX_VALUE;
		int &ret = dp[seq][idx][andVal];
		const vector<int> &nums = *pNums;
		const vector<int> &andValues = *pAndValues;

		int curAnd = andVal & nums[idx];
		int splitVal = MAX_VALUE;
		if (curAnd == andValues[seq]) {
			splitVal = divideArray(seq + 1, idx + 1, INIT_MASK) + nums[idx];
		}
		else if (curAnd < andValues[seq]) {
			return ret = MAX_VALUE;
		}
		int includeVal = divideArray(seq, idx + 1, curAnd);

		return ret = min(splitVal, includeVal);
	}

public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
		numsSize = static_cast<int>(nums.size());
		andsSize = static_cast<int>(andValues.size());
		pAndValues = &andValues;
		pNums = &nums;
		dp.resize(andsSize, vector<map<int, int>>(numsSize));

		int ret = divideArray(0, 0, INIT_MASK);
		return ret != MAX_VALUE ? ret : -1;
    }
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//vector<int> nums{1, 4, 3, 3, 2};
	//vector<int> andValues{0, 3, 3, 2};
	//vector<int> nums{2, 3, 5, 7, 7, 7, 5};
	//vector<int> andValues{0, 7, 5};
	//vector<int> nums{1, 2, 3, 4};
	//vector<int> andValues{2};

	//vector<int> nums{32,114,114,105,61,37,49,49,122,60,38,55,114,110,37,96,62,34,122,97,98,122,49,106,99,54,57,32,125,38,36,48,62,105,41,119,33,54,125,96,126,127,124,40,50,57,47,62,97,42,58,34,119,44,58,40,60,47,63,117,35,124,41,116,53,127,48,52,33,99,98,100,56,54,61,61,104,42,110,39,53,38,101,49,50,123,40,32,123,56,115,33,63,99,99,100,61,47,99,57};
	//vector<int> andValues{32, 32, 32, 32, 32, 32, 33};

	vector<int> nums{3, 9};
	vector<int> andValues{1};

	Solution s;
	cout << s.minimumValueSum(nums, andValues) << endl;

	return 0;
}
