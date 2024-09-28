#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

constexpr int MAX_N = 2000000;
constexpr int MAX_RANGE = 100000;
static vector<int> g_primes;

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

int solve(int N, int A, int B)
{
	set<int> primeInRange;
	auto lo = lower_bound(g_primes.begin(), g_primes.end(), A);
	for (auto it = lo; it != g_primes.end() && *it <= B; it++) {
		primeInRange.insert(*it);
	}

	if (primeInRange.size() == 0) {
		return -1;
	}

	queue<int> q;
	vector<int> visited(MAX_N + 1, -1);

	q.push(N);
	visited[N] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		if (primeInRange.find(cur) != primeInRange.end()) {
			return visited[cur];
		}

		vector<int> nexts;
		if (cur > 0) {
			nexts.push_back(cur / 2);
			nexts.push_back(cur / 3);
			nexts.push_back(cur - 1);
		}
		nexts.push_back(cur + 1);

		for (int next : nexts) {
			if (visited[next] == -1) {
				q.push(next);
				visited[next] = visited[cur] + 1;
			}
		}
	}

	return -1;
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Eratos(MAX_RANGE, g_primes);

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		int N, A, B;
		cin >> N >> A >> B;
		cout << solve(N, A, B) << endl;
	}

	return 0;
}
