#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

// обчислення префікс-функції рядка s
vector <int> prefixFunction(string s) {
	vector <int> p(s.size());
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
	return p;
}

bool boyer_moore(string a, string b) {
	// обчислення таблиці стоп-символів
	map <char, int> stopTable;
	for (int i = 0; i < a.length(); i++) {
		stopTable[a[i]] = i;
	}
	// обчислення префікс функції a та перевернутого рядка a
	string ra(a.rbegin(), a.rend());
	vector<int> p = prefixFunction(a), pr = prefixFunction(ra);
	// обчислення таблиці суфіксів
	map <int, int> suffixTable;
	for (int i = 0; i < a.length() + 1; i++) {
		suffixTable[i] = a.length() - p.back();
	}
	for (int i = 1; i < a.length(); i++) {
		int j = pr[i];
		suffixTable[j] = min(suffixTable[j], i - pr[i] + 1);
	}
	// зміщення шаблону за допомогою
	// префікс-функції, таблиць суфіксів та стоп-символів
	int shift = 0;
	while (shift <= b.length() - a.length()) {
		int pos = a.length() - 1;
		while (a[pos] == b[pos + shift]) {
			if (pos == 0) {
				return true;
			}
			pos--;
		}
		if (pos == a.length() - 1) {
			auto stopSymbol = stopTable.find(b[pos + shift]);
			int stopSymbolAdditional = pos - (stopSymbol != stopTable.end() ? stopSymbol->second : -1);
			shift += stopSymbolAdditional;
		} else {
			shift += suffixTable[a.length() - pos - 1];
		}
	}

	return false;
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
	// перевірка входження a у b за допомогою алгоритма Бойєра-Мура
	if (boyer_moore(a, b)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
