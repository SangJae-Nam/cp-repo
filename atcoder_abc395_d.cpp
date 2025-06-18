#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	vector<int> nestName2Idx(N);
	vector<int> nestIdx2Name(N);
	vector<int> pigeon(N);//index
	for (int i = 0; i < N; i++) {
		nestName2Idx[i] = i;
		nestIdx2Name[i] = i;
		pigeon[i] = i;
	}

	for (int i = 0; i < Q; i++) {
		int o, a, b;
		cin >> o;

		if (o == 1) {
			cin >> a >> b;
			a--;
			b--;
			int idx = nestName2Idx[b];
			pigeon[a] = idx;
		}
		else if (o == 2) {
			cin >> a >> b;
			a--;
			b--;
			int idxa = nestName2Idx[a];
			int idxb = nestName2Idx[b];
			swap(nestName2Idx[a], nestName2Idx[b]);
			swap(nestIdx2Name[idxa], nestIdx2Name[idxb]);
		}
		else {
			cin >> a;
			a--;
			cout << nestIdx2Name[pigeon[a]] + 1 << '\n';
		}
	}

	return 0;
}
