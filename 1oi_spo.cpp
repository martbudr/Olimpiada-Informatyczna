//nie przechodzi wszystkich testow
#include <iostream>
#include <vector>

using namespace std;

int wyszBinarne(int lewy, int prawy, vector<float>& wartosci, float wyniki_i) {// szukanie najmniejszego za ktorego (w sensie o 1 dalej) moge wstawic aktualna wartosc 
	// (ostatniego wiekszego lub rownego podanej liczbie)
	int srodek;
	while (lewy < prawy) {
		srodek = (lewy + prawy + 1) / 2;
		if (wartosci[srodek] >= wyniki_i)
			lewy = srodek;
		else prawy = srodek - 1;
	}
	return lewy;
}

int dlugoscCiagu(vector<float>& wyniki, int n) {
	if (n < 1) return 0;

	vector<float> wartosci(min(n, 10001));// wartosci na koncach ciagow danych dlugosci-1; 10001- maksymalna dlugosc maksymalnego malejacego podciagu
	int dlugosc = 1;

	wartosci[0] = wyniki[0];
	for (int i = 1; i < n; ++i) {
		if (wyniki[i] > wartosci[0])// nowa najwieksza
			wartosci[0] = wyniki[i];
		else if (wyniki[i] < wartosci[dlugosc - 1])// nowa najmniejsza
			wartosci[dlugosc++] = wyniki[i];
		else// gdzies pomiedzy
			wartosci[wyszBinarne(0, dlugosc - 1, wartosci, wyniki[i]) + 1] = wyniki[i];
	}
	return dlugosc;
}

int main(void) {
	int n; cin >> n;
	vector<float> wyniki(n);
	for (int i = 0; i < n; ++i)
		cin >> wyniki[i];

	cout << dlugoscCiagu(wyniki, n) * 100 << '\n';
}