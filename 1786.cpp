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

using namespace std;

// z[i] = str[i]에서 시작하는 부분 문자열이면서 str의 prefix이기도 한 가장 긴 문자열의 길이
void zAlgorithm(const string &str, vector<int> &z)
{
    int len = static_cast<int>(str.size());
    int l = 0;
    int r = 0;

	z.resize(len, 0);

    for (int i = 1; i < len; i++) {
        if (i > r) {
            l = r = i;
            while (r < len && str[r - l] == str[r]) {
                r++;
            }
            z[i] = r - l;
            r--;
        }
        else {
            if (z[i - l] < r - i + 1) {
                z[i] = z[i - l];
            }
            else {
                l = i;
                while (r < len && str[r - l] == str[r]) {
                    r++;
                }
                z[i] = r - l;
                r--;
            }
        }
    }
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string T, P;
	getline(cin, T);
	getline(cin, P);

	vector<int> z;
	zAlgorithm(P + T, z);

	vector<int> indexes;
	int psize = static_cast<int>(P.size());
	for (size_t i = P.size(); i < z.size(); i++) {
		if (z[i] >= psize) {
			indexes.push_back(i - psize + 1);
		}
	}

	cout << indexes.size() << '\n';
	if (indexes.size()) {
		for (int idx : indexes) {
			cout << idx << ' ';
		}
		cout << '\n';
	}

	return 0;
}
