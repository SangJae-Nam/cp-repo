#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstring>
#include <bitset>
#include <queue>
#include <limits>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solve {
private:
	int N;
	vector<int> V;

public:
	Solve () {}

	void input() {
		cin >> N;
		V.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> V[i];
		}
	}

	void solve() {
		vector<long long int> l(N/3 + 1), r(N/3 + 1), a(N/3 + 1);

		l[0] = 0;
		long long int sum = 0;
		long long int qsum = 0;
		priority_queue<int> pq;
		priority_queue<int> pqMax;
		for (int i = 0; i < N - 1; i++) {
			sum += V[i];

			int qsize = i / 3 + 1;
			if (pq.size() < qsize) {
				if (!pqMax.empty() && pqMax.top() > V[i]) {
					pq.push(-pqMax.top());
					qsum += pqMax.top();
					pqMax.pop();
					pqMax.push(V[i]);
				}
				else {
					pq.push(-V[i]);
					qsum += V[i];
				}
			}
			else if (pq.size() == qsize) {
				if (-pq.top() < V[i]) {
					qsum -= -pq.top();
					pqMax.push(-pq.top());
					pq.pop();

					pq.push(-V[i]);
					qsum += V[i];
				}
				else {
					pqMax.push(V[i]);
				}
			}
			else {
				assert(false);
			}

			if (i % 3 == 2) {
				l[i / 3 + 1] = sum - qsum;
			}
		}

		/*
		cout << endl;
		for (auto n : l) {
			cout << n << ' ';
		}
		cout << endl;
		*/

		*r.rbegin() = 0;
		sum = 0;
		qsum = 0;
		priority_queue<int> pq1;
		priority_queue<int> pq1Max;
		for (int i = N - 1; i > 0; i--) {
			sum += V[i];
			int j = N - 1 - i;

			int qsize = j / 3 + 1;
			if (pq1.size() < qsize) {
				if (!pq1Max.empty() && pq1Max.top() > V[i]) {
					pq1.push(-pq1Max.top());
					qsum += pq1Max.top();
					pq1Max.pop();
					pq1Max.push(V[i]);
				}
				else {
					pq1.push(-V[i]);
					qsum += V[i];
				}
			}
			else if (pq1.size() == qsize) {
				if (-pq1.top() < V[i]) {
					qsum -= -pq1.top();
					pq1Max.push(-pq1.top());
					pq1.pop();

					pq1.push(-V[i]);
					qsum += V[i];
				}
				else {
					pq1Max.push(V[i]);
				}
			}
			else {
				assert(false);
			}

			if (i % 3 == 1) {
				r[i / 3] = sum - qsum;
			}
		}

		/*
		for (auto n : r) {
			cout << n << ' ';
		}
		cout << endl;
		*/

		long long int ans = -1;
		int ansIdx = -1;

		for (int i = 0; i < N / 3 + 1; i++) {
			long long int a = l[i] + r[i] + V[i * 3];
			if (a > ans) {
				ans = a;
				ansIdx = i * 3;
			}
		}

		cout << ansIdx << ' ' << ans << '\n';
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solve s;

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		s.input();
		s.solve();
	}

	return 0;
}

