#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
string outFilename;

int n;
int counter;

// аналог звичайного сортування злиттям, але
// на зовнішній пам'яті
string mergeSort(int l, int r) {
	// потрапили на один з n початкових файлів
	if (l == r) {
		return to_string(l) + ".txt";
	}
	// сортуємо обидві половини відрізка
	int mid = (l + r) / 2;
	string lName = mergeSort(l, mid);
	string rName = mergeSort(mid + 1, r);
	// відкриваємо потоки для зчитування
	ifstream lin(lName), rin(rName);
	// створюємо новий файл з назвою counter.txt
	string mergedName = to_string(counter++) + ".txt";
	ofstream mout(mergedName);
	// зливаємо масиви, слідкуючи за
	// достатністю інформації
	int ls, rs;
	lin >> ls;
	rin >> rs;
	mout << ls + rs << endl;
	bool readL = false, readR = false;
	int la, ra;
	while (ls != 0 || rs != 0) {
		if (rs == 0) {
			if (!readL) {
				lin >> la;
			}
			mout << la << " ";
			ls--;
			readL = false;
		} else if (ls == 0) {
			if (!readR) {
				rin >> ra;
			}
			mout << ra << " ";
			rs--;
			readR = false;
		} else {
			if (!readL) {
				lin >> la;
				readL = true;
			}
			if (!readR) {
				rin >> ra;
				readR = true;
			}
			if (la <= ra) {
				mout << la << " ";
				ls--;
				readL = false;
			} else {
				mout << ra << " ";
				rs--;
				readR = false;
			}
		}
	}
	// видаляємо непотрібні файли
	lin.close();
	rin.close();
	string delName = "erase " + lName;
	system(delName.c_str());
	delName = "erase " + rName;
	system(delName.c_str());
	// закриваємо файл з відсортованим відрізком l..r
	// та повертаємо його назву
	mout.close();
	return mergedName;
}

// багатофазне сортування злиттям
void polyPhaseMergeSort() {
	// розбиваємо масив a на n частин і
	// помістимо кожну частину в окремий файл
	counter = 0;
	fin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		fin >> a;
		ofstream curout(to_string(counter++) + ".txt");
		curout << 1 << endl << a << endl;
		curout.close();
	}
	// виконаємо попарне злиття необхідних файлів
	string sortedFilename = mergeSort(0, n - 1);
	// перейменуємо файл з відсортованим масивом a так,
	// як нам треба
	string renameName = "rename " + sortedFilename + " " + outFilename;
	system(renameName.c_str());
}
 
int main() {
	// зчитування назв вхідного і вихідного файлів
	cout << "Enter name of input file: ";
	string inFilename;
	cin >> inFilename;
	fin.open(inFilename);
	cout << "Enter name of output file: ";
	cin >> outFilename;
	
	// багатофазне сортування
	polyPhaseMergeSort();
}
