#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

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

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases;
	cin >> nTestcases;
	for (int c = 0; c < nTestcases; c++) {
		int N;
		cin >> N;

		vector<vector<int>> A(N, vector<int>(N));
		vector<vector<int>> B(N, vector<int>(N));
		vector<int> R(N);
		vector<int> C(N);
		vector<pair<int, pair<int, int>>> edges;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> A[i][j];
			}
		}
		long long int totalCost = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> B[i][j];
				if (B[i][j] > 0) {
					// R(0~N-1) C(N~2N-1)
					edges.push_back(make_pair(B[i][j], make_pair(i, N + j)));
					totalCost += B[i][j];
				}
			}
		}
		for (int i = 0; i < N; i++) {
			cin >> R[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> C[i];
		}

		sort(edges.rbegin(), edges.rend());
		long long int selectedCost = 0;
		UnionFind uf(2 * N);

		for (auto &edge : edges) {
			int cost = edge.first;
			int r = edge.second.first;
			int c = edge.second.second;

			if (!uf.same(r, c)) {
				selectedCost += cost;
				uf.unite(r, c);
			}
		}

		cout << "Case #" << c + 1 << ": " << totalCost - selectedCost << '\n';
	}

	return 0;
}
