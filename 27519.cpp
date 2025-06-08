#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>

using namespace std;

constexpr int MAX_N = 100000;
constexpr int DIV = 1000000007;

class Eratos
{
public:
	int size;
	vector<bool> isPrime;
	vector<int> primes;

	Eratos(int n) {
		size = n + 1;
		init();
	}

	void init() {
		isPrime.resize(size, true);

		/*  만일 n이 1보다 작거나 같으면 함수 종료 */
		if (size <= 1) return;

		/*  2부터 n까지 n-1개를 저장할 수 있는 배열 할당
		배열 참조 번호와 소수와 일치하도록 배열의 크기는
		n+1 길이만큼 할당(인덱스 번호 0과 1은 사용하지 않음)	*/
		/*  배열초기화: 처음엔 모두 소수로 보고 true값을 줌 */
		isPrime[0] = isPrime[1] = false;

		/*  에라토스테네스의 체에 맞게 소수를 구함
			만일, PrimeArray[i]가 true이면 i 이후의 i 배수는 약수로 i를
			가지고 있는 것이 되므로 i 이후의 i 배수에 대해 false값을 준다.
			PrimeArray[i]가 false이면 i는 이미 소수가 아니므로 i의 배수 역시
			소수가 아니게 된다. 그러므로 검사할 필요도 없다.
			또한 i*k (k < i) 까지는 이미 검사되었으므로 j시작 값은 i*2에서 i*i로 개선할 수 있다.
		*/

		for (int i = 2; i * i < size; i++)
		{
			if (isPrime[i]) {
				for (int j = i * i; j < size; j += i) {
					isPrime[j] = false;
				}
			}
		}
	}

	void initPrimes() {
		primes.reserve(size);
		for (int i = 0; i < size; i++) {
			if (isPrime[i]) {
				primes.push_back(i);
			}
		}
	}
};

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Eratos eratos(MAX_N);
	eratos.initPrimes();
	
	int dp[MAX_N + 1];
	memset(dp, 0, sizeof(dp));

	int nTestcases;
	cin >> nTestcases;
	vector<int> ns;
	int maxN = -1;
	while (nTestcases--) {
		int n;
        cin >> n;
		maxN = max(n, maxN);
		ns.push_back(n);
	}

	dp[0] = 1;
	for (int prime : eratos.primes) {
		for (int i = prime; i <= maxN; i++) {
			dp[i] += dp[i - prime];
			dp[i] %= DIV;
		}
	}

	for (int n : ns) {
		cout << dp[n] << '\n';
	}

	return 0;
}
