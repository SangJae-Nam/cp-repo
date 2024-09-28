#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <cstring>

using namespace std;

class UnionFind
{
private:
	vector<int> parent;
	vector<int> size;

public:
	UnionFind(int n) : parent(n + 1), size(n + 1, 1) {
		for (int i = 0; i <= n; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] == x) {
			return x;
		}

		return parent[x] = find(parent[x]);
	}

	bool same(int a, int b) {
		return find(a) == find(b);
	}

	void unite(int a, int b) {
		a = find(a);
		b = find(b);

		if (a == b) {
			return;
		}

		if (size[a] < size[b]) {
			swap(a, b);
		}

		parent[b] = a;
		size[a] += size[b];
	}
};

// It's from Wikipedia
void Eratos(int n, vector<int> &primes)
{
    /*  만일 n이 1보다 작거나 같으면 함수 종료 */
    if (n <= 1) return;

    /*  2부터 n까지 n-1개를 저장할 수 있는 배열 할당
    배열 참조 번호와 소수와 일치하도록 배열의 크기는
    n+1 길이만큼 할당(인덱스 번호 0과 1은 사용하지 않음)    */
    bool* PrimeArray = new bool[n + 1];

    /*  배열초기화: 처음엔 모두 소수로 보고 true값을 줌 */
    for (int i = 2; i <= n; i++)
        PrimeArray[i] = true;

    /*  에라토스테네스의 체에 맞게 소수를 구함
        만일, PrimeArray[i]가 true이면 i 이후의 i 배수는 약수로 i를
        가지고 있는 것이 되므로 i 이후의 i 배수에 대해 false값을 준다.
        PrimeArray[i]가 false이면 i는 이미 소수가 아니므로 i의 배수 역시
        소수가 아니게 된다. 그러므로 검사할 필요도 없다.
또한 i*k (k < i) 까지는 이미 검사되었으므로 j시작 값은 i*2에서 i*i로 개선할 수 있다.
    */
    for (int i = 2; i * i <= n; i++)
    {
        if (PrimeArray[i])
            for (int j = i * i; j <= n; j += i)
                PrimeArray[j] = false;
    }

    for (int i = 0; i <= n; i++) {
        if (PrimeArray[i]) {
            primes.push_back(i);
        }
    }

	delete[] PrimeArray;
}

#define MAX_N	(28)
#define START	(26)
#define END		(27)

short completeDays[MAX_N];
vector<pair<int, int>> adj[MAX_N];

int visited[MAX_N];
vector<int> topologicalResult;

void dfs(int idx)
{
	visited[idx] = 1;

	for (auto [next, size] : adj[idx]) {
		if (visited[next] == 0) {
			dfs(next);
		}
	}
	topologicalResult.push_back(idx);
}

int ds(int start, int end)
{
	vector<int> distance(MAX_N, 10000000);

	distance[topologicalResult[0]] = 0;
	for (int cur : topologicalResult) {
		for (auto [next, size] : adj[cur]) {
			distance[next] = min(distance[cur] - size, distance[next]);
		}
	}

	return -distance[end];
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string line;
	char job;
	memset(completeDays, 0, sizeof(completeDays));

	while (getline(cin, line)) {
		if (line.empty()) {
			break;
		}

		string col;
		istringstream iss(line);
		getline(iss, col, ' ');
		job = col[0];

		getline(iss, col, ' ');
		completeDays[job - 'A'] = stoi(col);

		if (getline(iss, col)) {
			for (char n : col) {
				adj[n - 'A'].push_back(make_pair(job - 'A', 0));
			}
		}
		else {
			adj[START].push_back(make_pair(job - 'A', 0));
		}
	}

	for (int i = 0; i < 26; i++) {
		if (completeDays[i] > 0) {
			if (adj[i].size() == 0) {
				adj[i].push_back(make_pair(END, completeDays[i]));
			}
			else {
				for (auto &n : adj[i]) {
					n.second = completeDays[i];
				}
			}
		}
	}

	memset(visited, 0, sizeof(visited));
	visited[START] = 1;
	dfs(START);
	for (int i = 0; i < 26; i++) {
		if (completeDays[i] > 0 && visited[i] == 0) {
			dfs(i);
		}
	}

	reverse(topologicalResult.begin(), topologicalResult.end());
	cout << ds(START, END) << '\n';

	return 0;
}
