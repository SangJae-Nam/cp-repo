#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <queue>

using namespace std;

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

        vector<int> t(m + 1);
        for (int i = 1; i <= m; i++) {
            cin >> t[i];
        }

        vector<int> answer;
        vector<int> drinked(n + 1, 0);
        vector<int> used(m + 1, false);
        int notRained = 0;

        bool no = false;
        for (int i = 1; i <= m; i++) {
            if (t[i] > 0) {
                int iLake = t[i];
                int start = drinked[iLake] + 1;
                int j;
                for (j = start; j < i; j++) {
                    if (t[j] == 0 && !used[j]) {
                        used[j] = true;
                        answer.push_back(iLake);
                        drinked[iLake] = i;
                        break;
                    }
                }
                if (j >= i) {
                    cout << "NO\n";
                    no = true;
                    break;
                }
            }
            else {
                notRained++;
            }
        }
        if (no) {
            continue;
        }

        cout << "YES\n";
        for (int a : answer) {
            cout << a << " ";
        }
        if (answer.size() != notRained) {
            for (int i = 0; i < notRained - answer.size(); i++) {
                cout << 0 << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}

