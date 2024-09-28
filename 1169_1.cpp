#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <numeric>
#include <cassert>
#include <bitset>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

void Eratos(int n, vector<unsigned char> &isPrime)
{
    /*  만일 n이 1보다 작거나 같으면 함수 종료 */
    if (n <= 1) return;

    /*  2부터 n까지 n-1개를 저장할 수 있는 배열 할당
    배열 참조 번호와 소수와 일치하도록 배열의 크기는
    n+1 길이만큼 할당(인덱스 번호 0과 1은 사용하지 않음)    */
    /*  배열초기화: 처음엔 모두 소수로 보고 true값을 줌 */
	isPrime.clear();
	isPrime.resize(n + 1, 1);
	isPrime[0] = isPrime[1] = 0;

    /*  에라토스테네스의 체에 맞게 소수를 구함
        만일, PrimeArray[i]가 true이면 i 이후의 i 배수는 약수로 i를
        가지고 있는 것이 되므로 i 이후의 i 배수에 대해 false값을 준다.
        PrimeArray[i]가 false이면 i는 이미 소수가 아니므로 i의 배수 역시
        소수가 아니게 된다. 그러므로 검사할 필요도 없다.
또한 i*k (k < i) 까지는 이미 검사되었으므로 j시작 값은 i*2에서 i*i로 개선할 수 있다.
    */

	int sqrtn = int(sqrt(n));
    for (int i = 2; i <= sqrtn; i++)
    {
		if (isPrime[i])
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = 0;
    }
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<unsigned char> isPrime;
	Eratos(9001, isPrime);

	int M, N;
	cin >> N >> M;

	vector<short> H(N);
	for (int i = 0; i < N; i++) {
		cin >> H[i];
	}

	vector<short> ans;
	short end = 1 << N;
	for (short i = 0; i < end; i++) {
		if (__builtin_popcount(i) == M) {
			short sum = 0;
			short cur = i;
			short idx = 0;
			while (cur > 0) {
				if (cur & 1) {
					sum += H[idx];
				}
				cur >>= 1;
				idx++;
			}

			if (isPrime[sum]) {
				ans.push_back(sum);
			}
		}
	}

	if (ans.size() > 0) {
		sort(ans.begin(), ans.end());
		short prev = -1;
		for (auto n : ans) {
			if (prev != n) {
				cout << n << ' ';
			}
			prev = n;
		}
		cout << '\n';
	}
	else {
		cout << "-1\n";
	}

	return 0;
}
