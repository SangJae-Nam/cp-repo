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

//constexpr int NODE = -1;
constexpr int WALL = -200000;
constexpr int TARGET = -300000;
constexpr int VISITED = -400000;

void print(vector<vector<int>> &board)
{
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void clear(vector<vector<int>> &board, vector<pair<int, int>> &nodes, int targetX, int targetY)
{
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			if (board[i][j] == VISITED) {
				board[i][j] = 0;
			}
		}
	}

	for (int i = 1; i < nodes.size(); i++) {
		auto &n = nodes[i];
		board[n.first][n.second] = i;
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int R, C, N, r, c;
		cin >> R >> C >> N >> r >> c;

		r--;
		c--;
		vector<vector<int>> board(R, vector<int>(C));

		vector<pair<int, int>> nodes(N + 1);
		board[r][c] = TARGET;
		for (int i = 1; i <= N; i++) {
			int x, y;
			cin >> x >> y;
			board[x - 1][y - 1] = i;
			nodes[i] = make_pair(x - 1, y - 1);
		}

		vector<int> walls;
		for (int i = 0; i < R; i++) {
			string s;
			cin >> s;
			for (int j = 0; j < C; j++) {
				if (s[j] == 'W') {
					board[i][j] = WALL;
					walls.push_back(i * C + j);
				}
			}
		}

		//print(board);

		int D = 0;
		vector<int> originalD(N + 1);
		unordered_map<int, int> targetToWall;

		queue<pair<int, pair<int, int>>> q;
		q.push(make_pair(0, make_pair(r, c)));
		while (!q.empty()) {
			auto cur = q.front();
			q.pop();

			int &curMove = cur.first;
			int &curX = cur.second.first;
			int &curY = cur.second.second;

			int dx[] = {1, 0, -1, 0};
			int dy[] = {0, 1, 0, -1};
			for (int i = 0; i < 4; i++) {
				int nextX = curX + dx[i];
				int nextY = curY + dy[i];

				if (nextX >= 0 && nextX < R && nextY >= 0 && nextY < C) {
					if (board[nextX][nextY] == 0) {
						q.push(make_pair(curMove + 1, make_pair(nextX, nextY)));
						board[nextX][nextY] = VISITED;
					}
					else if (board[nextX][nextY] > 0) {
						q.push(make_pair(curMove + 1, make_pair(nextX, nextY)));
						D += curMove + 1;
						originalD[board[nextX][nextY]] = curMove + 1;
						board[nextX][nextY] = VISITED;
					}
					else if (board[nextX][nextY] == WALL) {
						if (targetToWall.count(nextX * C + nextY) == 0) {
							targetToWall[nextX * C + nextY] = curMove + 1;
						}
					}
				}
			}
		}

		vector<vector<int>> nodeToWall(N + 1, vector<int>(R * C));
		for (int n = 1; n <= N; n++) {
			clear(board, nodes, r, c);

			queue<pair<int, pair<int, int>>> q;
			q.push(make_pair(0, make_pair(nodes[n].first, nodes[n].second)));
			while (!q.empty()) {
				auto cur = q.front();
				q.pop();

				int &curMove = cur.first;
				int &curX = cur.second.first;
				int &curY = cur.second.second;

				int dx[] = {1, 0, -1, 0};
				int dy[] = {0, 1, 0, -1};
				for (int i = 0; i < 4; i++) {
					int nextX = curX + dx[i];
					int nextY = curY + dy[i];

					if (nextX >= 0 && nextX < R && nextY >= 0 && nextY < C) {
						if (board[nextX][nextY] >= 0 || board[nextX][nextY] == TARGET) {
							q.push(make_pair(curMove + 1, make_pair(nextX, nextY)));
							board[nextX][nextY] = VISITED;
						}
						else if (board[nextX][nextY] == WALL) {
							if (nodeToWall[n][nextX * C + nextY] == 0) {
								nodeToWall[n][nextX * C + nextY] = curMove + 1;
							}
						}
					}
				}
			}
		}

		long long int allValueD = 0;
		for (int wall : walls) {
			long long int valueD = 0;
			for (int i = 1; i <= N; i++) {
				if (nodeToWall[i][wall] > 0 && targetToWall.count(wall) > 0) {
					int newLen = targetToWall[wall] + nodeToWall[i][wall];
					if (originalD[i] > newLen) {
						valueD += originalD[i] - newLen;
					}
				}
				else {
					valueD = -1;
					break;
				}
			}

			if (valueD > 0) {
				allValueD += valueD;
			}
		}

		cout << D << " " << allValueD << '\n';
	}

	return 0;
}

