/*
   6 5
1 6
2 4 5
2 1 2
2 2 3
2 3 4
2 5 6
--> 0

 */
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <set>

using namespace std;

constexpr int TRUE = 1;
constexpr int FALSE = 0;
constexpr int UNKNOWN = -1;

int N;
int M;

vector<int> people;
vector<bool> knownTruth;
vector<vector<int>> party;

int maxFalse(int partyIndex)
{
	if (partyIndex >= M) {
		return 0;
	}

	bool hasTrue = false;
	bool hasFalse = false;
	bool canFalse = true;
	for (int person : party[partyIndex]) {
		if (people[person] == TRUE) {
			canFalse = false;
			hasTrue = true;
		}
		else if (people[person] == FALSE) {
			hasFalse = true;
		}
	}

	// Invalid case
	if (hasTrue && hasFalse) {
		return -100;
	}

	vector<pair<int, int>> prev;
	for (int person : party[partyIndex]) {
		prev.push_back(make_pair(person, people[person]));
	}

	int ret = -100;
	if (canFalse) {
		for (int person : party[partyIndex]) {
			people[person] = FALSE;
		}
		ret = maxFalse(partyIndex + 1) + 1;

		for (auto &n : prev) {
			people[n.first] = n.second;
		}
	}
	if (!hasFalse) {
		for (int person : party[partyIndex]) {
			people[person] = TRUE;
		}
		ret = max(ret, maxFalse(partyIndex + 1));

		for (auto &n : prev) {
			people[n.first] = n.second;
		}
	}

	return ret;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> M;
	people.resize(N + 1, UNKNOWN);
	knownTruth.resize(N + 1, false);
	party.resize(M);

	int p;
	cin >> p;
	for (int i = 0; i < p; i++) {
		int n;
		cin >> n;
		knownTruth[n] = true;
		people[n] = TRUE;
	}

	for (int i = 0; i < M; i++) {
		cin >> p;
		party[i].resize(p);
		for (int j = 0; j < p; j++) {
			int n;
			cin >> n;
			party[i][j] = n;
		}
	}

	cout << maxFalse(0) << endl;

	return 0;
}
