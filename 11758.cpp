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

using pii = pair<int, int>;


/* p1 -> p2 -> p3의 외적을 통해 시계/반시계/직전여부를 구함
   > 0 : 반시계방향
   = 0 : 직선
   < 0 : 시계방향
   */
int ccw(const pii &p1, const pii &p2, const pii &p3)
{
	//(x2 - x1)(y3 - y1) - (x3 - x1)(y2 - y1)
	auto &[x1, y1] = p1;
	auto &[x2, y2] = p2;
	auto &[x3, y3] = p3;

	return (x2 - x1) * (y3 - y1) - (x3- x1) * (y2 - y1);
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<pii> points(3);
	for (int i = 0; i < 3; i++) {
		cin >> points[i].first >> points[i].second;
	}

	int ret = ccw(points[0], points[1], points[2]);
	if (ret > 0) {
		cout << "1\n";
	}
	else if (ret < 0) {
		cout << "-1\n";
	}
	else {
		cout << "0\n";
	}

	return 0;
}
