#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

const int MAXN = 1e5 + 1;

// об'явлення типу запису
struct Pair {
	int key;
	int id;
};

int n;
Pair a[MAXN], b[MAXN];

// вивід масиву a
void printA() {
	for (int i = 0; i < n; i++) {
		cout << "(" << a[i].key << ", " << a[i].id << ") ";
	}
	cout << endl;
}

// скопіювати масив x в масив y
void copy(Pair* x, Pair* y) {
	for (int i = 0; i < n; i++) {
		y[i] = x[i];
	}
}

// сортування з властивостями 1 і 2
void sort12() {
	// розбиваємо масив на дві черги
	queue <int> q0, q1;
	for (int i = 0; i < n; i++) {
		if (a[i].key == 0) {
			q0.push(i);
		} else {
			q1.push(i);
		}
	}
	// з'єднуємо ці черги
	int i = 0;
	while (!q0.empty()) {
		a[i].id = q0.front();
		q0.pop();
		a[i].key = 0;
		i++;
	}
	while (!q1.empty()) {
		a[i].id = q1.front();
		q1.pop();
		a[i].key = 1;
		i++;
	}
}

// поміняти елементи місцями
void swap(Pair& a, Pair& b) {
	Pair c = a;
	a = b;
	b = c;
}

// сортування з властивостями 1 і 3
void sort13() {
	int p0 = 0, p1 = n - 1; 
	for (int i = 0; p0 != p1; ) {
		if (a[i].key == 0) {
			if (i == p0) {
				p0++;
				i++;
			} else {
				swap(a[i], a[p0]);
				p0++;
			}
		} else {
			if (i == p1) {
				p1--;
				i++;
			} else {
				swap(a[i], a[p1]);
				p1--;
			}
		}
	}
}

// перевернути масив a на відрізку [l, r]  
void reverse(int l, int r) {
	for (int i = l; i < (l + r + 1) / 2; i++) {
		swap(a[i], a[l + r - i]);
	}
}

// функція рекурсивного злиття
void merge(int l, int m, int r) {
	if (m < l || m >= r) {
		return;
	}
	// знаходження необхідних індексів i та j
	int i = l - 1, j = m, p = (r - l + 1) / 2;
	for (int k = 0; k < p; k++) {
		if (j == r || i < m && a[i + 1].key <= a[j + 1].key) {
			i++;
		} else {
			j++;
		}
	}
	// зсув частини масиву
	reverse(i + 1, j);
	reverse(i + 1, j - m + i);
	reverse(j - m + i + 1, j);
	// злиття менших частин
	merge(l, i, l + p - 1);
	merge(l + p, l + p + m - i - 1, r);
}

// сортування з властивостями 2 і 3
void sort23(int l, int r) {
	if (l == r) {
		return;
	}
	int m = (l + r) / 2;
	sort23(l, m);
	sort23(m + 1, r);
	merge(l, m, r);
}

int main() {
	// зчитування назви вхідного файлу
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	// зчитування вхідних даних
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].key >> a[i].id;
	}
	cout << "Start array:" << endl;
	printA();
	// проведення 3-ьох видів сортувань
	// зі збереженням стану початкового масиву
	copy(a, b);
	// 1 і 2
	sort12();
	cout << "O(n) and stable:" << endl;
	printA();
	// 1 і 3
	copy(b, a);
	sort13();
	cout << "O(n) and without adding memory:" << endl;
	printA();
	// 2 і 3
	copy(b, a);
	sort23(0, n - 1);
	cout << "stable and without adding memory, O(nlog^2n):" << endl;
	printA();
}
