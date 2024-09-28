#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>

using namespace std;

pair<string, int> selectFirst(map<string, vector<int>> &sticks)
{
	for (auto it = sticks.begin(); it != sticks.end(); it++) {
		if (it->second.size() > 0) {
			pair<string, int> ret = make_pair(it->first, *(it->second.rbegin()));
			it->second.pop_back();

			if (it->second.size() == 0) {
				sticks.erase(it++);
			}
			return ret;
		}
		else {
			sticks.erase(it++);
		}
	}

	return make_pair("", -1);
}

static map<string, vector<string>> connect;
pair<string, int> selectNext(map<string, vector<int>> &sticks, string &key)
{
	int maxVal = 0;
	string maxKey;
	for (string &nextKey : connect[key]) {
		if (sticks.find(nextKey) != sticks.end()) {
			if (maxVal < *(sticks[nextKey].rbegin())) {
				maxVal = *(sticks[nextKey].rbegin());
				maxKey = nextKey;
			}
		}
	}

	if (maxKey.size() != 0) {
		sticks[maxKey].pop_back();
		if (sticks[maxKey].size() == 0) {
			sticks.erase(maxKey);
		}

		return make_pair(maxKey, maxVal);
	}
	else {
		return make_pair("", 0);
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	connect["II"].push_back("II");
	connect["II"].push_back("IN");
	connect["II"].push_back("IU");
	connect["IN"].push_back("IN");
	connect["IN"].push_back("II");
	connect["IN"].push_back("IU");
	connect["IN"].push_back("NN");
	connect["IN"].push_back("NU");
	connect["IU"].push_back("IU");
	connect["IU"].push_back("II");
	connect["IU"].push_back("IN");
	connect["IU"].push_back("NU");
	connect["IU"].push_back("UU");
	connect["NN"].push_back("IN");
	connect["NN"].push_back("NN");
	connect["NN"].push_back("NU");
	connect["NU"].push_back("NU");
	connect["NU"].push_back("IN");
	connect["NU"].push_back("IU");
	connect["NU"].push_back("NN");
	connect["NU"].push_back("UU");
	connect["UU"].push_back("UU");
	connect["UU"].push_back("IU");
	connect["UU"].push_back("NU");

	int N;
	map<string, vector<int>> sticks;

	cin >> N;
	for (int i = 0; i < N; i++) {
		string kind;
		int len;

		cin >> kind >> len;
		if (kind[0] > kind[1]) {
			swap(kind[0], kind[1]);
		}

		sticks[kind].push_back(len);
	}

	for (auto it = sticks.begin(); it != sticks.end(); it++) {
		sort(it->second.begin(), it->second.end());
	}

	int maxlen = 0;
	while (sticks.size() != 0) {
		int curlen = 0;
		auto cur = selectFirst(sticks);
		if (cur.second == -1) {
			break;
		}
		curlen += cur.second;

		string nextKey = cur.first;
		while (sticks.size() != 0) {
			auto next = selectNext(sticks, nextKey);
			if (next.first.size() == 0) {
				break;
			}
			curlen += next.second;
			nextKey = next.first;
		}

		maxlen = max(maxlen, curlen);
	}

	cout << maxlen << '\n';
	return 0;
}

