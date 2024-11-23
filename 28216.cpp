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

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.first < b.first;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	constexpr int LEN = 200001;
	vector<vector<pair<int, int>>> rows(LEN);
	vector<vector<pair<int, int>>> cols(LEN);

	for (int i = 0; i < N; i++) {
		int x, y, w;
		cin >> x >> y >> w;

		rows[y].push_back(make_pair(x, w));
		cols[x].push_back(make_pair(y, w));
	}

	for (int i = 0; i < LEN; i++) {
		sort(rows[i].begin(), rows[i].end());
		sort(cols[i].begin(), cols[i].end());
	}

	vector<vector<long long int>> prefixSumRows(rows.size());
	vector<vector<long long int>> prefixSumCols(cols.size());

	for (int i = 0; i < LEN; i++) {
		prefixSumRows[i].resize(rows[i].size() + 1);
		for (size_t j = 0; j < rows[i].size(); j++) {
			prefixSumRows[i][j + 1] = prefixSumRows[i][j] + rows[i][j].second;
		}

		prefixSumCols[i].resize(cols[i].size() + 1);
		for (size_t j = 0; j < cols[i].size(); j++) {
			prefixSumCols[i][j + 1] = prefixSumCols[i][j] + cols[i][j].second;
		}
	}

	int x = 1, y = 1;
	long long int ret = 0;
	for (int q = 0; q < Q; q++) {
		int d, v;
		cin >> d >> v;

		int nx = x, ny = y;
		if (d == 0) {
			nx += v;
			auto its = lower_bound(rows[y].begin(), rows[y].end(), make_pair(x+1, 0));
			if (its != rows[y].end() && (*its).first > nx) {
				its = rows[y].end();
			}
			auto ite = lower_bound(rows[y].begin(), rows[y].end(), make_pair(nx+1, 0));
			if (its != rows[y].end() && ite != rows[y].begin()) {
				int is = its - rows[y].begin() + 1;
				int ie;
				if (ite != rows[y].end()) {
					ie = ite - rows[y].begin();
				}
				else {
					ie = static_cast<int>(rows[y].size());
				}
				ret += prefixSumRows[y][ie] - prefixSumRows[y][is - 1];
			}
		}
		else if (d == 1) {
			ny += v;
			auto its = lower_bound(cols[x].begin(), cols[x].end(), make_pair(y+1, 0));
			if (its != cols[x].end() && (*its).first > ny) {
				its = cols[x].end();
			}
			auto ite = lower_bound(cols[x].begin(), cols[x].end(), make_pair(ny+1, 0));
			if (its != cols[x].end() && ite != cols[x].begin()) {
				int is = its - cols[x].begin() + 1;
				int ie;
				if (ite != cols[x].end()) {
					ie = ite - cols[x].begin();
				}
				else {
					ie = static_cast<int>(cols[x].size());
				}
				ret += prefixSumCols[x][ie] - prefixSumCols[x][is - 1];
			}
		}
		else if (d == 2) {
			nx -= v;
			auto its = lower_bound(rows[y].begin(), rows[y].end(), make_pair(nx, 0));
			if (its != rows[y].end() && (*its).first > x) {
				its = rows[y].end();
			}
			auto ite = lower_bound(rows[y].begin(), rows[y].end(), make_pair(x, 0));

			if (its != rows[y].end() && ite != rows[y].begin()) {
				int is = its - rows[y].begin() + 1;
				int ie;
				if (ite != rows[y].end()) {
					ie = ite - rows[y].begin();
				}
				else {
					ie = static_cast<int>(rows[y].size());
				}
				ret += prefixSumRows[y][ie] - prefixSumRows[y][is - 1];
			}
		}
		else if (d == 3) {
			ny -= v;
			auto its = lower_bound(cols[x].begin(), cols[x].end(), make_pair(ny, 0));
			if (its != cols[x].end() && (*its).first > y) {
				its = cols[x].end();
			}
			auto ite = lower_bound(cols[x].begin(), cols[x].end(), make_pair(y, 0));

			if (its != cols[x].end() && ite != cols[x].begin()) {
				int is = its - cols[x].begin() + 1;
				int ie;
				if (ite != cols[x].end()) {
					ie = ite - cols[x].begin();
				}
				else {
					ie = static_cast<int>(cols[x].size());
				}
				ret += prefixSumCols[x][ie] - prefixSumCols[x][is - 1];
			}
		}

		x = nx;
		y = ny;
	}

	cout << ret << '\n';

	return 0;
}
