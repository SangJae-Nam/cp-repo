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
#include <cstring>
#include <immintrin.h>

#pragma GCC target("avx,avx2,fma")

using namespace std;

int N, M;
vector<vector<int>> adj;
vector<int> W, T;
char dirty[102400];

void dfs(int cur, int delta, int target)
{
	delta += W[cur];
	T[cur] += delta;
	W[cur] = 0;

	if (cur == target) {
		for (int next : adj[cur]) {
			W[next] += delta;
		}
	}
	else {
		for (int next : adj[cur]) {
			dfs(next, delta, target);
		}
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;
	adj.resize(N + 1);
	W.resize(N + 1);//delta
	T.resize(N + 1);//total
	memset(dirty, 0, sizeof(dirty));

	for (int i = 1; i <= N; i++) {
		int p;
		cin >> p;

		if (p != -1) {
			adj[p].push_back(i);
		}
	}

	for (int q = 0; q < M; q++) {
		int s;
		cin >> s;

		if (s == 1) {
			int idx, w;
			cin >> idx >> w;

			W[idx] += w;
			dirty[idx] = 1;
		}
		else if (s == 2) {
			int idx;
			cin >> idx;

			bool d = false;
			__m256i zero = _mm256_setzero_si256();
			long long int dst[4];

			for (int i = 0; i < sizeof(dirty); i+=256) {
				__m256i cur = _mm256_loadu_si256((__m256i*)(dirty + i));
				__m256i cmp = _mm256_cmpeq_epi64(cur, zero);
				_mm256_storeu_si256((__m256i*)(dst), cmp);

				for (int j = 0; j < 4; j++) {
					if (dst[j] != 0) {
						d = true;
						break;
					}
				}
				if (d = true) {
					break;
				}
			}

			if (d) {
				dfs(1, 0, idx);
				for (int i = 0; i < sizeof(dirty); i+=256) {
					_mm256_storeu_si256((__m256i*)(dirty + i), zero);
				}
			}

			cout << T[idx] << '\n';
		}
	}

	return 0;
}
