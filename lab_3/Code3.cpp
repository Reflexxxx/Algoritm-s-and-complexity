#include <iostream>

using namespace std;

const int MAXN = 1e5 + 1;


float h[MAXN];
int n, d;



void swap(float &a, float &b) {                      // ������� �������� ������
	int c = a;
	a = b;
	b = c;
}


void buildHEAP() {							        // �������� ������
	for (int i = n - 1; i >= 0; i--) {
		heapify(i);
	}
}


void printHEAP() {								    // ��������� ������
	cout << "Heap: ";
	for (int i = 0; i < n; i++) {
		cout << h[i] << " ";
	}
	cout << endl;
}


void vstavka(float v) {								// �������
	n++;
	increaseKey(n - 1, v);
}


void heapify(int i) {								// ��������� �������� �����
	int maxP = i;
	float maxV = h[i];
	for (int k = 1; k <= d; k++) {
		int p = d * i + k;
		if (p >= n) {
			break;
		}
		if (h[p] > maxV) {
			maxV = h[p];
			maxP = p;
		}
	}
	if (maxP != i) {
		swap(h[i], h[maxP]);
		heapify(maxP);
	}
}

void increaseKey(int i, float v) {					 // ��������� �������� �����
	if (i == 0) {
		h[0] = v;
		return;
	}
	int p = (i - 1) / d;
	if (h[p] < v) {
		h[i] = h[p];
		increaseKey(p, v);
	}
	else {
		h[i] = v;
	}
}

float extractMax() {								 // ��������� �� ���������� ������������� ��������
	float maxV = h[0];
	swap(h[0], h[n - 1]);
	n--;
	heapify(0);
	return maxV;
}


int main() {
	// �������� ��� �� ��������� �� ����
	cin >> n >> d;
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}
	
	// ������� ������
	buildHEAP();
	printHEAP();
	// ������������ ������ 
	string op;
	while (cin >> op) {
		if (op == "inc") {
			int i;
			float v;
			cin >> i >> v;
			increaseKey(i, v);
			cout << "Key in position " << i << " increased to " << v << endl;
		} else if (op == "ex") {
			cout << "Extracted max = " << extractMax() << endl;
		} else if (op == "ins") {
			float v;
			cin >> v;
			vstavka(v);
			cout << "Inserted element " << v << endl;
		} else {
			break;
		}
		printHEAP();
	}
}
