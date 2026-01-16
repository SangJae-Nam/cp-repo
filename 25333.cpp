#include <algorithm>
#include <iostream>
#include <utility>
#include <numeric>

using namespace std;

class Solve {
private:
	int A, B, X;

public:
	Solve () {}

	void input() {
		cin >> A >> B >> X;
	}

	void solve() {
		int d = gcd(A, B);
		cout << X / d << '\n';
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
