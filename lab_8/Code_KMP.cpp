#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100000;

int p[MAXN];

// обчислення префікс-функції рядка s в масив p
void findPrefixFunction(string s) {
	p[0] = 0;
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == s[p[i - 1]]) {
			p[i] = p[i - 1] + 1;
		} else {
			int j = p[i - 1];
			while (j != 0 && s[j] != s[i]) {
				j = p[j - 1];
			}
			if (j == 0 && s[j] != s[i]) {
				p[i] = 0;
			} else {
				p[i] = j + 1;
			}
		}
	}
}

int main() {
	// зчитування назви вхідного файлу
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	// зчитування вхідних даних
	string a, b;
	cin >> a >> b;
	// знаходження префікс-функції рядка a#b
	findPrefixFunction(a + "#" + b); 
	// якщо префікс-функція для деякої позиції після фіктивного символу
	// дорівнює розміру зразка, то ми знайшли співпадіння
	for (int i = a.size() + 1; i < a.size() + b.size() + 1; i++) {
		if (p[i] == a.size()) {
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
}
