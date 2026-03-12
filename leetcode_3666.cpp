#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstring>
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
public:
    int minOperations(string s, int k) {
		int len = static_cast<int>(s.size());

		int first = 0;
		for (char ch : s) {
			if (ch == '1') {
				first++;
			}
		}

		set<int> nodes[2];
		for (int i = 0; i <= len; i++) {
			nodes[i % 2].insert(i);
		}

		vector<int> dist(len + 1, -1);
		queue<int> q;
		q.push(first);
		dist[first] = 0;
		nodes[first % 2].erase(first);

		while (!q.empty()) {
			int count1 = q.front();
			q.pop();
			int &step = dist[count1];

			if (count1 == len) {
				return step;
			}

			int left = max(0, k - count1);
			int right = min(k, len - count1);

			int n1left = count1 - k + 2 * left;
			int n1right = count1 - k + 2 * right;

			set<int> &n = nodes[n1left % 2];
			auto s = n.lower_bound(n1left);
			auto e = n.upper_bound(n1right);
			for (auto it = s; it != e;) {
				assert(dist[*it] == -1);
				q.push(*it);
				dist[*it] = step + 1;
				it = n.erase(it);
			}
		}

		return -1;
    }
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution s;
	cout << s.minOperations("110", 1) << endl;
	cout << s.minOperations("0101", 3) << endl;
	cout << s.minOperations("101", 2) << endl;
	cout << s.minOperations("0", 1) << endl;
	cout << s.minOperations("00001011100000010110110110010000001010010001100100000000111010000100100000001011111001100011001100100011011000000111000111010110101100000001001100100001001010001010000101000001111110011110110011100001000100011010000011101100101010001010110000110100111010101110001000101011011011111101010000011010000010100001010001011101111010100100010010011000101011010010100100100000011100010010110100001101", 354) << endl;
	cout << s.minOperations("01000001001001110010001001111010010001011000001000000000100110000101111100000111010001101010110100000110010101110000000011110000001110010001100001010100000011100010100111111000000011110001001010110110000011000000001010100001111001100100000111011100101101001000001111110111010000110001101011110001100101110111000100111111100000010100101000010000110010101001000001010010011011000111000001110011000011111000100011001100010011100100001000101000", 15) << endl;

	return 0;
}
