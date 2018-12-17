#include <iostream>
#include<fstream>

using namespace std;

const int P = 31;
const int MAXM = 1000;

int m, n;
int pow[MAXM];
int ha[MAXM][MAXM], hb[MAXM][MAXM];
string a[MAXM], b[MAXM];

// розрахунок степені числа P
void calculatePowers(int n) {
	pow[0] = 1;
	for (int i = 1; i < n; i++) {
		pow[i] = pow[i - 1] * P;
	}
}

// обчислення хеш-функції рядка s в масив h
void makeHash(string s, int* h) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++) {
		pow[i] = pow[i - 1] * P;
		h[i] = h[i - 1] + s[i] * pow[i];
	}
}

// посимвольна перевірка на рівність a[q][l..r] і b[q - t]
bool trivialCheck(int t, int q, int l, int r) {
	for (int i = l; i <= r; i++) {
		if (a[q][i] != b[q - t][i - l]) {
			return false;
		}
	}
	return true;
}

// двокрокова перевірка на рівність a[q][l..r] і b[q - t]
bool check(int t, int q, int l, int r) {
	if(ha[q][r] - (l ? ha[q][l - 1] : 0) != hb[q - t][n - 1] * pow[l]) {
		return false;
	} else if (trivialCheck(t, q, l, r)) {
		return true;
	}
	return false;
}

int main() {
	// зчитування імені вхідного файлу
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);

	//зчитування вхідних даних
	cin >> m >> n;
	if (m < n) {
		cout << "NO" << endl;
		return 0;
	}
	//обчислення хешів a[0..m-1] та b[0..n-1]
	calculatePowers(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i];
		makeHash(a[i], ha[i]);
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
		makeHash(b[i], hb[i]);
	}
	// перебір початкової позиції
	for (int i = 0; i < m - n + 1; i++) {
		for (int j = 0; j < m - n + 1; j++) {
			// порівняння рядків
			bool found = true;
			for (int k = i; k < i + n; k++) {
				if (!check(i, k, j, j + n - 1)) {
					// якщо існує рядок, що не співпадає
					// дана позиція не підходить
 					found = false;
					break;
				}
			}
			if (found) {
				// якщо всі рядки на які розбита матриця співпадають
				// то і вся матриця співпадає
				cout << "YES" << endl;
				return 0;
			}
		}
	}
	// не існує матриці, що співпадає
	cout << "NO" << endl;
}
