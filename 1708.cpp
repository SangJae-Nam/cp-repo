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
long long int ccw(const pii &p1, const pii &p2, const pii &p3)
{
	//(x2 - x1)(y3 - y1) - (x3 - x1)(y2 - y1)
	auto &[x1, y1] = p1;
	auto &[x2, y2] = p2;
	auto &[x3, y3] = p3;

	return static_cast<long long int>((x2 - x1)) * (y3 - y1) - (x3- x1) * (y2 - y1);
}

// Andrew's algorithm을 이용한 블록껍질(Convex Hull)을 구함
void getConvexHull(vector<pii> &points, vector<pii> &output)
{
	int psize = static_cast<int>(points.size());
	sort(points.begin(), points.end());
	output.reserve(psize);

	// 위쪽
	output.push_back(points[0]);
	output.push_back(points[1]);
	for (int i = 2; i < psize; i++) {
		size_t os;
		while ((os = output.size()) >= 2) {
			auto dir = ccw(output[os - 2], output[os - 1], points[i]);
			if (dir >= 0) {
				output.pop_back();
			}
			else {
				break;
			}
		}
		output.push_back(points[i]);
	}

	// 아래쪽
	output.push_back(points[psize - 2]);
	size_t upperSize = output.size();
	for (int i = psize - 3; i >= 0; i--) {
		size_t os;
		while ((os = output.size()) >= upperSize) {
			auto dir = ccw(output[os - 2], output[os - 1], points[i]);
			if (dir >= 0) {
				output.pop_back();
			}
			else {
				break;
			}
		}
		output.push_back(points[i]);
	}

	//제일 마지막은 제일 첫번째와 같으므로 삭제
	output.pop_back();
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<pii> points(N);
	for (int i = 0; i < N; i++) {
		cin >> points[i].first >> points[i].second;
	}
	vector<pii> output;
	getConvexHull(points, output);
	cout << output.size() << '\n';

	return 0;
}
