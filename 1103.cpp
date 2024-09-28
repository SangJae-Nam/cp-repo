#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <tuple>
#include <sstream>
#include <cassert>
#include <queue>

using namespace std;

static int N, M;
static vector<string> board;
static vector<vector<bool>> visited;
static vector<vector<int>> dp;

int dfs(int curX, int curY)
{
	int &ret = dp[curY][curX];
	if (ret != -1) {
		return ret;
	}

	int maxJump = 1;
	const int dx[] = {1, 0, -1, 0};
	const int dy[] = {0, 1, 0, -1};
	for (int i = 0; i < 4; i++) {
		int nextX = curX + (dx[i] * (board[curY][curX] - '0'));
		int nextY = curY + (dy[i] * (board[curY][curX] - '0'));

		if (nextX >= 0 && nextY >= 0 && nextX < M && nextY < N &&
			board[nextY][nextX] != 'H')
		{
			if (visited[nextY][nextX] != 0) {
				return -1;
			}
			else {
				visited[nextY][nextX] = true;
				int jump = dfs(nextX, nextY);
				if (jump == -1) {
					return -1;
				}
				maxJump = max(maxJump, jump + 1);
				visited[nextY][nextX] = false;
			}
		}
	}

	return ret = maxJump;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;

	board.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> board[i]; 
	}

	if (board[0][0] == 'H') {
		cout << "0\n";
		return 0;
	}

	visited.resize(N, vector<bool>(M, false));
	dp.resize(N, vector<int>(M, -1));
	visited[0][0] = true;

	cout << dfs(0, 0) << '\n';

	return 0;
}
