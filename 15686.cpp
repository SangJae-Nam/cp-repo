#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

constexpr int MAX_DIST = 1000000;
int N, M;
vector<pair<int, int>> houses;
vector<pair<int, int>> hofs;

int run(int selected, int idx)
{
	if (__builtin_popcount(selected) == M) {
		int ret = 0;
		for (auto &house : houses) {
			int dist = MAX_DIST;
			for (size_t i = 0; i < hofs.size(); i++) {
				auto &hof = hofs[i];
				if ((1<<i) & selected) {
					dist = min(dist, abs(house.first - hof.first) + abs(house.second - hof.second));
				}
			}
			ret += dist;
		}
		return ret;
	}

	if (idx >= hofs.size()) {
		return MAX_DIST;
	}

	int ret = run(selected | (1<<idx), idx + 1);
	ret = min(ret, run(selected, idx + 1));
	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int city[50][50];
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> city[i][j];
			if (city[i][j] == 1) {
				houses.push_back(make_pair(i, j));
			}
			else if (city[i][j] == 2) {
				hofs.push_back(make_pair(i, j));
			}
		}
	}

	cout << run(0, 0) << '\n';

	return 0;
}
