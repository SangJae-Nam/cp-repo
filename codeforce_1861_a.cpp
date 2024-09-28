#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	const char *answers[] = {"0", "17", "29", "37", "43", "59", "61", "73", "89", "97"};

	int nTestcases;
	cin >> nTestcases;
	while (nTestcases--) {
		string s;
		cin >> s;
		cout << answers[s[0] - '0'] << '\n';
	}

	return 0;
}
