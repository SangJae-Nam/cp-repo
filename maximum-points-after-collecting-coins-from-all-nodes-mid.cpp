class Solution {
private:
    vector<vector<int>> adjs;
    map<pair<int, int>, int> dp;

    int dfs(int cur, int prev, int divide, const vector<int> &coins, const int k) {
        if (divide >= 20) {
            divide = 20;
        }

        auto key = make_pair(cur, divide);
        auto it = dp.find(key);
        if (it != dp.end()){
            return it->second;
        }

        int prePoint = coins[cur] / (1<<divide);

        int point1 = prePoint - k;
        for (int next : adjs[cur]) {
            if (next == prev) {
                continue;
            }

            point1 += dfs(next, cur, divide, coins, k);
        }

        int point2 = prePoint / 2;
        for (int next : adjs[cur]) {
            if (next == prev) {
                continue;
            }

            point2 += dfs(next, cur, divide + 1, coins, k);
        }

        int point = max(point1, point2);
        dp[key] = point;
        return point;
    }

public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        int numNodes = static_cast<int>(coins.size());
        adjs.resize(numNodes);

        for (auto &edge : edges) {
            adjs[edge[0]].push_back(edge[1]);
            adjs[edge[1]].push_back(edge[0]);
        }

        return dfs(0, 0, 0, coins, k);
    }
};
