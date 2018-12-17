#include <iostream>
#include <fstream>

using namespace std;

// структура для зберігання інформації про деталь
struct Detail {
	float size;
	int id;
};

// сортування злиттям масиву структур Detail за полем size
void mergeSort(int l, int r, Detail* d) {
	// масив з одного елемента впорядкований за означенням
	if (l == r) {
		return;
	}
	// сортуємо ліву та праву половини відрізка
	int mid = (l + r) / 2;
	mergeSort(l, mid, d);
	mergeSort(mid + 1, r, d);
	// зливаємо ці половини в тимчасовий масив temp
	int size = r - l + 1;
	Detail *temp = new Detail[size];
	int p1 = l, p2 = mid + 1, pt = 0;
	while (pt != size) {
		if (p1 == mid + 1 || d[p2].size < d[p1].size) {
			temp[pt] = d[p2];
			p2++; 
		} else {
			temp[pt] = d[p1];
			p1++;
		}
		pt++;
	}
	// переносимо відсортований масив в d та видаляємо тимчасовий масив
	for (int i = 0; i < size; i++) {
		d[l + i] = temp[i];
	}
	delete temp;
}

int main() {
	// зчитування назви вхідного файлу
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	// ініціалізація структур для зберігання деталей
	// та зчитування інформації про них
	int n;
	cin >> n;
	Detail* b = new Detail[n];
	Detail* g = new Detail[n];
	for (int i = 0; i < n; i++) {
		cin >> b[i].size;
		b[i].id = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> g[i].size;
		g[i].id = i;
	}
	// сортування болтів та гайок відповідно
	mergeSort(0, n - 1, b);
	mergeSort(0, n - 1, g);
	// знаходження пар елементів:
	// парою вважається 2 індекси в початкових масивах
	// болтів та гайок, що однакові за розміром
	int pb = 0, pg = 0;
	while (pb < n && pg < n) {
		if (b[pb].size == g[pg].size) {
			cout << b[pb].id << " - " << g[pg].id << endl;
			pb++;
			pg++;
		} else if (b[pb].size < g[pg].size) {
			pb++;
		} else {
			pg++;
		}
	}
}
