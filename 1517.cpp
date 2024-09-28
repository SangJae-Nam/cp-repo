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

using namespace std;

int merge(vector<int> &src, vector<int> &dst, int start, int end)
{
	int mid = (start + end) / 2;
	int left = start;
	int right = mid;
	int nInversion = 0;
	for (int i = 0; i < end - start; i++) {
		if (left < mid && (right >= end || src[left] <= src[right])) {
			dst[start + i] = src[left++];
		}
		else {
			dst[start + i] = src[right++];
			//inversion
			nInversion += mid - left;
		}
	}

	for (int i = 0; i < end - start; i++) {
		src[start + i] = dst[start + i];
	}

	return nInversion;
}

long long int mergeSort(vector<int> &src, vector<int> &dst, int start, int end)
{
	if (end - start < 1) {
		return 0;
	}
	else if (end - start == 1) {
		dst[start] = src[start];
		return 0;
	}
	else if (end - start == 2) {
		return merge(src, dst, start, end);
	}
	else {
		int mid = (start + end) / 2;
		long long int ret = mergeSort(src, dst, start, mid);
		ret += mergeSort(src, dst, mid, end);
		ret += merge(src, dst, start, end);

		return ret;
	}
}

int main(int argc, char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;
	vector<int> src(N);
	for (int i = 0; i < N; i++) {
		cin >> src[i];
	}
	vector<int> dst(N);
	cout << mergeSort(src, dst, 0, N) << '\n';
	for (int a : dst) {
		cout << a << ' ';
	}
	cout << endl;

	return 0;
}
