#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <deque>
#include <cassert>

using namespace std;

template <typename T>
class simpleQ {
private:
	vector<T> buf;
	size_t index;

public:
	simpleQ() {
		index = 0;
	}

	T front() {
		assert(!empty());
		return buf[index];
	}

	T top() {
		return front();
	}

	void pop() {
		index++;
	}

	void push(T item) {
		buf.push_back(item);
	}

	size_t size() {
		return buf.size();
	}

	bool empty() {
		return buf.size() <= index;
	}
};

bool solve(int m, int n, const vector<int> &t, vector<simpleQ<int>> &rainyDaysPerLake, vector<int> &answer)
{
	priority_queue<int> drinkQ;
	for (int l = 1; l <= n; l++) {
		if (!rainyDaysPerLake[l].empty()) {
			drinkQ.push(-rainyDaysPerLake[l].front());
			rainyDaysPerLake[l].pop();
		}
	}
	vector<bool> lakeFull(n + 1, true);

	for (int i = 0; i < m; i++) {
		if (t[i] == 0) {
			if (!drinkQ.empty()) {
				int day = -drinkQ.top();
				drinkQ.pop();
				int lake = t[day];
				answer.push_back(lake);
				lakeFull[lake] = false;
			}
			else {
				answer.push_back(0);
			}
		}
		else {
			int lake = t[i];
			if (lakeFull[lake]) {
				return false;
			}
			else {
				lakeFull[lake] = true;
				if (!rainyDaysPerLake[lake].empty()) {
					drinkQ.push(-rainyDaysPerLake[lake].front());
					rainyDaysPerLake[lake].pop();
				}
			}
		}
	}

	return true;
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int nTestcases;
    cin >> nTestcases;
    while (nTestcases--) {
        int n, m;
        cin >> n >> m;

		vector<simpleQ<int>> rainyDaysPerLake(n + 1);
        vector<int> t(m);
        for (int i = 0; i < m; i++) {
            cin >> t[i];
			if (t[i] > 0) {
				rainyDaysPerLake[t[i]].push(i);
			}
        }

		vector<int> answer;
		if (solve(m, n, t, rainyDaysPerLake, answer)) {
       		cout << "YES\n";
	       	for	(int a : answer) {
   	        	cout << a << " ";
   	   		}
   	    	cout << "\n";
		}
		else {
			cout << "NO\n";
		}
    }

    return 0;
}

