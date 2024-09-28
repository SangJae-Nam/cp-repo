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

using namespace std;

constexpr char ROAD = '0';
constexpr char WALL = '1';

typedef struct _point {
	short row;
	short col;
	int length;
	bool morning;
	unsigned char K;

	_point(short row, short col, int length, bool morning, unsigned char K) {
		this->row = row;
		this->col = col;
		this->length = length;
		this->morning = morning;
		this->K = K;
	}
} point;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, K;
	cin >> N >> M >> K;

	vector<string> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	queue<point> q;
	vector<vector<bitset<11>>> visited(N, vector<bitset<11>>(M));

	visited[0][0][0] = true;
	q.push(point(0, 0, 1, true, static_cast<unsigned char>(K)));

	int minLength = -1;
	while (!q.empty()) {
		point cur = q.front();
		q.pop();

		if (cur.row == N - 1 && cur.col == M - 1) {
			minLength = cur.length;
			break;
		}

		short dx[] = {-1, 0, 1, 0};
		short dy[] = {0, -1, 0, 1};
		for (int i = 0; i < 4; i++) {
			short nextRow = cur.row + dy[i];
			short nextCol = cur.col + dx[i];

			if (nextRow >= 0 && nextRow < N && nextCol >= 0 && nextCol < M) {
				if (arr[nextRow][nextCol] == ROAD) {
					if (!visited[nextRow][nextCol][cur.K]) {
						q.push(point(nextRow, nextCol, cur.length + 1, !cur.morning, cur.K));
						visited[nextRow][nextCol][cur.K] = true;
					}
				}
				else { //WALL
					if (cur.K > 0 && !visited[nextRow][nextCol][cur.K - 1]) {
						if (cur.morning) {
							q.push(point(nextRow, nextCol, cur.length + 1, !cur.morning, cur.K - 1));
							visited[nextRow][nextCol][cur.K - 1] = true;
						}
						else {
							q.push(point(cur.row, cur.col, cur.length + 1, !cur.morning, cur.K));
							visited[cur.row][cur.col][cur.K] = true;
						}
					}
				}
			}
		}
	}

	cout << minLength << '\n';
	return 0;
}

