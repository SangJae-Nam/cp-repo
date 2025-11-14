#include <algorithm>
#include <iostream>
#include <utility>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	map<int, long long int> posmap;
	for (int i = 0; i < N; i++) {
		int p, v;
		cin >> p >> v;
		posmap[p] += v;
	}

	vector<pair<int, long long int>> pos(posmap.begin(), posmap.end());
	N = static_cast<int>(pos.size());

	long double rightVal = 0;
	long long int rightStep = 0;
	for (int i = 1; i < N; i++) {
		rightVal += 1.0 * (pos[i].first - pos[0].first) * pos[i].second;
		rightStep += pos[i].second;
	}

	long double leftVal = 0;
	long long int leftStep = pos[0].second;

	int ans = pos[0].first;
	long double val = rightVal;

	for (int i = 1; i < N; i++) {
		leftVal += 1.0 * leftStep * (pos[i].first - pos[i - 1].first);
		rightVal -= 1.0 * rightStep * (pos[i].first - pos[i - 1].first);

		if (val > leftVal + rightVal) {
			ans = pos[i].first;
			val = leftVal + rightVal;
		}

		leftStep += pos[i].second;
		rightStep -= pos[i].second;
	}

	cout << ans << '\n';

	return 0;
}

