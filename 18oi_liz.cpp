#include <iostream>
#include <vector>

using namespace std;

void Spamietaj(int lewy, int prawy, int suma, vector<int>& lewe_indeksy, vector<int>& prawe_indeksy, vector<int>& pocz_lizak)
{
    lewe_indeksy[suma] = lewy;
    prawe_indeksy[suma] = prawy;

    if(suma >= 3){
        if(pocz_lizak[lewy] == 2)
            Spamietaj(lewy+1, prawy, suma-2, lewe_indeksy, prawe_indeksy, pocz_lizak);
        else if(pocz_lizak[prawy] == 2)
            Spamietaj(lewy, prawy-1, suma-2, lewe_indeksy, prawe_indeksy, pocz_lizak);
        else Spamietaj(lewy+1, prawy-1, suma-2, lewe_indeksy, prawe_indeksy, pocz_lizak);
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k; // n - dlugosc lizaka, k - ilosc zapytan
    string lizak;
    cin >> n >> k >> lizak;

    vector<int> pocz_lizak(n);
    int suma_lizak = 0;
    for(int i=0; i<n; ++i){
        if(lizak[i] == 'T')
            pocz_lizak[i] = 2;
        else pocz_lizak[i] = 1;

        suma_lizak += pocz_lizak[i];
    }

    vector<int> lewe_indeksy(suma_lizak+1, -1),
            prawe_indeksy(suma_lizak+1, -1);
    Spamietaj(0, n-1, suma_lizak, lewe_indeksy, prawe_indeksy, pocz_lizak); // pierwsze spamietywanie (dla calego lizaka)

    // szukanie jedynek najblizej brzegow w celu znalezienia przedzialu o innej parzystosci niz caly lizak
    int lewy=-1, prawy=-1;
    for(int i=0; i<n; ++i){
        if(pocz_lizak[i] == 1){
            if(lewy == -1) lewy = i;
            prawy = i;
        }
    }
    if(lewy != -1 && lewy <= n-prawy-1) // jedynka z lewej jest blizej lub jest jedyna jedynka
        Spamietaj(lewy+1, n-1, suma_lizak - 2*lewy - 1, lewe_indeksy, prawe_indeksy, pocz_lizak);

    else if(prawy != -1) // jedynka z prawej jest blizej
        Spamietaj(0, prawy-1, suma_lizak - 2*(n-prawy-1) - 1, lewe_indeksy, prawe_indeksy, pocz_lizak);

    // wczytywanie sum i wypisywanie wynikow
    int suma_wczyt;
    for(int i=0; i<k; ++i){
        cin >> suma_wczyt;
        if(suma_wczyt <= suma_lizak && lewe_indeksy[suma_wczyt] != -1)
            cout << lewe_indeksy[suma_wczyt]+1 << ' ' << prawe_indeksy[suma_wczyt]+1 << '\n';
        else cout << "NIE\n";
    }
}
