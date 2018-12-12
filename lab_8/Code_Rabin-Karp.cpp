#include <iostream>
#include <fstream>

using namespace std;

// деяке просте число, що приблизно
// дорівює кількості символів в алфавіті
const int P = 31;
const int MAXN = 100000;
	
int pow[MAXN];
int ha[MAXN], hb[MAXN];
string a, b;

// завчасний розрахунок степені числа P
void calculatePowers(int n) {
	pow[0] = 1;
	for (int i = 1; i < n; i++) {
		pow[i] = pow[i - 1] * P;
	}
}

// обчислення хеш-поліномів для всіх префіксів 
// рядка s і їх поміщення в масив h
void makeHash(string s, int* h) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++) {
		pow[i] = pow[i - 1] * P;
		h[i] = h[i - 1] + s[i] * pow[i];
	}
}

// посимвольна перевірка на рівність b[l..r] і a
bool trivialCheck(int l, int r) {
	for (int i = l; i <= r; i++) {
		if (b[i] != a[i - l]) {
			return false;
		}
	}
	return true;
}

int main() {
	// зчитування назви вхідного файлу
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	//зчитування вхідних даних
	cin >> a;
	cin >> b;
	//обчислення хешів a та b
	calculatePowers(b.size());
	makeHash(a, ha);
	makeHash(b, hb);
	// перевірка всіх можливих підрядків b довжиною a.size() на рівність з a
	for (int l = 0; l < b.size() - a.size() + 1; l++) {
	int r = l + a.size() - 1;
		if (hb[r] - (l ? hb[l - 1] : 0) == ha[a.size() - 1] * pow[l] &&
			trivialCheck(l, r)) {
			// хеші рівні та рядки посимвольно рівні
			cout << "YES" << endl;
			return 0; 
		}
	}
	// не знайшлося рядків рівних посимвольно
	cout << "NO" << endl;
}
