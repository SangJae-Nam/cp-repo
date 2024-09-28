#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <array>
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

	int N, X, F;
	cin >> N >> X >> F;

	vector<array<int, 3>> stations(N + 1);
	for (int i = 0; i < N; i++) {
		auto &[x, p, a] = stations[i];
		cin >> x >> p >> a;
	}
	stations[N] = {X, 0, 0};

	// unit price, gas
	multiset<pair<int, int>> gas;
	bool failed = false;

	int prevPos = stations[0][0];
	int curGas = stations[0][2] > F ? F : stations[0][2];
	long long int costs = 0;
	gas.insert(make_pair(stations[0][1], curGas));

	for (int i = 1; i <= N; i++) {
		auto &[x, p, a] = stations[i];

		// drive
		int length = x - prevPos;
		while (gas.size() > 0 && length > 0) {
			auto it = gas.begin();
			int price = it->first;
			int g = it->second;
			gas.erase(it);

			if (g - length > 0) {
				gas.insert(make_pair(price, g - length));
			}
	
			int used = min(g, length);
			curGas -= used;
			length -= used;
			costs += static_cast<long long int>(used) * price;
		}
		if (length > 0) {
			failed = true;
			break;
		}

		// cell gas
		int cellGas = (a + curGas) - F;
		while (gas.size() > 0 && cellGas > 0) {
			auto it = prev(gas.end());
			int price = it->first;
			int g = it->second;

			if (price < p) {
				break;
			}

			gas.erase(it);
			if (cellGas >= g) {
				cellGas -= g;
				curGas -= g;
			}
			else {
				curGas -= cellGas;
				gas.insert(make_pair(price, g - cellGas));
				cellGas = 0;
			}
		}

		// buy gas
		int needGas = F - curGas;
		if (needGas > 0) {
			int buy = min(needGas, a);
			curGas += buy;
			gas.insert(make_pair(p, buy));
		}

		prevPos = x;
	}

	if (!failed) {
		cout << costs << '\n';
	}
	else {
		cout << "-1\n";
	}

	return 0;
}
