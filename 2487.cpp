#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	vector<int> adj(N);
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		adj[i] = n - 1;
	}

	long long int ans = 1;
	vector<bool> visited(N);
	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			continue;
		}

		long long int count = 0;
		int cur = i;
		do {
			visited[cur] = true;
			count++;
			cur = adj[cur];
		} while (cur != i);

		ans = ans * count / gcd(ans, count);
	}

	cout << ans << '\n';

	return 0;
}
