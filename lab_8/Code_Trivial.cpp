#include <iostream>
#include <fstream>

using namespace std;

string a, b;

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
	// перевірка всіх можливих підрядків b довжиною a.size() на рівність з a
	for (int l = 0; l < b.size() - a.size() + 1; l++) {
		int r = l + a.size() - 1;
		if (trivialCheck(l, r)) {
			// рядки посимвольно рівні
			cout << "YES" << endl;
			return 0; 
		}
	}
	// не знайшлося рядків рівних посимвольно
	cout << "NO" << endl;
}
