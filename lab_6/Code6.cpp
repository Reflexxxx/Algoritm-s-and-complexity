#include <iostream>
#include <fstream>

using namespace std;

const int P = 31;
const int MAXN = 100000;
	
int pow[MAXN];
int ha[MAXN], hb[MAXN];
string a, b;

// розрахунок степені числа P
void calculatePowers(int n) {
	pow[0] = 1;
	for (int i = 1; i < n; i++) {
		pow[i] = pow[i - 1] * P;
	}
}

// обчислення хеш-функції рядка s і його поміщення в масив h
void makeHash(string s, int* h) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++) {
		pow[i] = pow[i - 1] * P;
		h[i] = h[i - 1] + s[i] * pow[i];
	}
}

// посимвольна перевірка на рівність a[l..r] і b
bool trivialCheck(int l, int r) {
	for (int i = l; i <= r; i++) {
		if (a[i] != b[i - l]) {
			return false;
		}
	}
	return true;
}

int main() {
	// зчитування імені вхідного файлу
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	//зчитування вхідних даних
	cin >> a;
	cin >> b;
	int n = a.size();
	// подвоєння рядка a
	a += a;
	//обчислення хешів a та b
	calculatePowers(2 * n);
	makeHash(a, ha);
	makeHash(b, hb);
	// перевірка всіх можливих підрядків a довжиною n на рівність з b
	for (int l = 0; l < n - 1; l++) {
		int r = l + n - 1;
		// якщо в логічному виразі a && b a = false,
		// то умова b не перевіряється
		if (ha[r] - (l ? ha[l - 1] : 0) == hb[n - 1] * pow[l] &&
			trivialCheck(l, r)) {
			// хеші рівні та рядки посимвольно рівні
			cout << "YES" << endl;
			return 0; 
		}
	}
	// не знайшлося рядків рівних посимвольно
	cout << "NO" << endl;
}
