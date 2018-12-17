#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100000;

int shift[MAXN];

// порівнює рядки a та b посимвольно
// починаючи  з передостаннього
bool equalH(string a, string b) {
	int i = a.size() - 2;
	while (i >= 0 && a[i] == b[i]) {
		i--;
	}
	return i == -1;
}

// алгоритм Хорспула
// стоп-символ - символ над останнім символом шаблона
bool horspool(string a, string b) {
	// для кожного символу алфавіту рахуємо
	// максимально можливе зміщення, що не пропускає стоп-символ
	for (int i = 'a'; i <= 'z'; i++) {
		shift[i] = a.size();
	}
	for (int i = 0; i < a.size() - 1; i++) {
		shift[a[i]] = a.size() - i - 1;
	}
	// рухаємо шаблон за допомогою обчислених зміщень
	int i = a.size() - 1;
	while (i < b.size()) {
		if (a[a.size() - 1] != b[i]) {
			i += 1;
		} else if (!equalH(a, b.substr(i - a.size() + 1, a.size()))) {
			i += shift[b[i]];	
		} else {
			break;
		}
	}
	return i < b.size();
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
	// перевірка входження a у b за допомогою алгоритма Хорспула
	if (horspool(a, b)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
