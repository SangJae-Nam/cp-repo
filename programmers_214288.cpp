#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <iostream>

using namespace std;

class Solve {
private:
    int K;
    int N;
    vector<vector<int>> cases;
    const vector<vector<int>> &reqs;
    
    void createCases(int curK, int remainN, vector<int> &cas) {
        if (curK == K - 1) {
            cas[curK] += remainN;
            cases.push_back(vector<int>(cas));
            cas[curK] -= remainN;
            return;
        }

        for (int i = 0; i <= remainN; i++) {
            cas[curK] += i;
            createCases(curK + 1, remainN - i, cas);
            cas[curK] -= i;
        }
    }
    
    int getWaitTime(vector<int> &cas) {
        vector<priority_queue<int, vector<int>, greater<int>>> consultants(cas.size(), priority_queue<int, vector<int>, greater<int>>());
        for (int i = 0; i < cas.size(); i++) {
            for (int j = 0; j < cas[i]; j++) {
                consultants[i].push(0);
            }
        }
        
        int ret = 0;
        for (int i = 0; i < reqs.size(); i++) {
            const int &curTime = reqs[i][0];
            const int &len = reqs[i][1];
            int targetK = reqs[i][2] - 1;
            
            int endTime = consultants[targetK].top();
            consultants[targetK].pop();
            
            if (endTime > curTime) {
                ret += endTime - curTime;
                consultants[targetK].push(endTime + len);
            }
            else {
                consultants[targetK].push(curTime + len);
            }
        }
        
        return ret;
    }
    
public:
    Solve(int k, int n, vector<vector<int>> &r) : K(k), N(n), reqs(r) {}
    
    int solve() {
        vector<int> cas(K);
        for (int i = 0; i < K; i++) {
            cas[i] = 1;
        }
        createCases(0, N - K, cas);
        
        int ret = numeric_limits<int>::max();
        for (auto &c : cases) {
            ret = min(ret, getWaitTime(c));
        }
        
        return ret;
    }
    
};

int solution(int k, int n, vector<vector<int>> reqs) {
    Solve s(k, n, reqs);
    return s.solve();
}

int main(int argc, char *argv[])
{
	vector<int> ks{3, 2};
	vector<int> ns{5, 3};
	vector<vector<vector<int>>> reqss{
		{
			{10, 60, 1},
			{15, 100, 3},
			{20, 30, 1},
			{30, 50, 3},
			{50, 40, 1},
			{60, 30, 2},
			{65, 30, 1},
			{70, 100, 2},
		},
		{
			{5, 55, 2},
			{10, 90, 2},
			{20, 40, 2},
			{50, 45, 2},
			{100, 50, 2},
		},
	};

	for (int t = 0; t < ks.size(); t++) {
		cout << solution(ks[t], ns[t], reqss[t]) << endl;
	}
}
