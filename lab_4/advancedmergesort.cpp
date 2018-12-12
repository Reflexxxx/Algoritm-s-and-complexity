#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

int n, a[MAXN];

void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

void reverse(int l, int r) {
	for (int i = l; i < (l + r + 1) / 2; i++) {
		swap(a[i], a[l + r - i]);
	}
}

void merge(int l, int m, int r) {
	if (m < l || m >= r) {
		return;
	}
	int i = l - 1, j = m, p = (r - l + 1) / 2;
	for (int k = 0; k < p; k++) {
		if (j == r || i < m && a[i + 1] <= a[j + 1]) {
			i++;
		} else {
			j++;
		}
	}
	reverse(i + 1, j);
	reverse(i + 1, j - m + i);
	reverse(j - m + i + 1, j);
	merge(l, i, l + p - 1);
	merge(l + p, l + p + m - i - 1, r);
}

void sort(int l, int r) {
	if (l == r) {
		return;
	}
	int m = (l + r) / 2;
	sort(l, m);
	sort(m + 1, r);
	merge(l, m, r);
}

int main() {
	n = 0;
	while (n < 20 && cin >> a[n]) {
		n++;
	}
	sort(0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
