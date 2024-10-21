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
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());

void printRandomNumbers(int nNumbers, int min, int max, char delim = ' ')
{
	uniform_int_distribution<int> dis(min, max);
	for (int i = 0; i < nNumbers; i++) {
		cout << dis(gen) << delim;
	}
	cout << '\n';
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int nTestcases = 1;
	cout << nTestcases << endl;
	while (nTestcases--) {
		uniform_int_distribution<int> dis(3, 20);
		int N = dis(gen);
		int M = dis(gen);
		cout << N << ' ' << M << endl;
		printRandomNumbers(N, 0, 10);
		printRandomNumbers(M, 1, 5);
		printRandomNumbers(M, 1, N);
		printRandomNumbers(M, 1, 10);
	}

	return 0;
}
