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

class Solve {
private:
public:
	Solve () {}

	void input() {
	}

	void solve() {
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string S = "wbwbwwbwbwbw";
	int W, B;
	cin >> W >> B;

	bool yes = false;
	for (int i = 0; i < W + B; i++) {
		int startIdx = i % S.size();
		int w = 0;
		int b = 0;
		for (int j = 0; j < W + B; j++) {
			int idx = (startIdx + j) % S.size();
			if (S[idx] == 'w') {
				w++;
			}
			else if (S[idx] == 'b') {
				b++;
			}

			if (w == W && b == B) {
				yes = true;
				break;
			}
		}
		if (yes) {
			break;
		}
	}

	if (yes) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}

	return 0;
}
