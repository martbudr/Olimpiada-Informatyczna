#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e10;

void rotacja(int j, vector<int>& P) // przenoszenie na poczatek liczby o danym indeksie
{
    for(int i=j; i>1; --i)
        swap(P[i], P[i-1]);
}

int znajdz(int akt_szuk, vector<int>& P)
{
    for(int i=2, x = P.size(); i<x; ++i){
        if(P[i] == akt_szuk)
            return i;
    }
    return 0;
}

long long ile_inwersji(vector<int> P) // szukanie ilosci koniecznych do wykonania inwersji
{
    int lok_wynik = 0;
    vector<int> pods(P.size()); // podstawowa rotacja
    for(int i=1, x = P.size(); i<x; ++i)
        pods[i] = i;
    while(P != pods){
        int akt_szuk = (P[1] == 1) ? P.size()-1 : P[1]-1; // aktualnie szukany
        int poz_akt_szuk = znajdz(akt_szuk, P); // pozycja aktualnie szukanego

        lok_wynik += poz_akt_szuk - 1;
        rotacja(poz_akt_szuk, P);
    }
    return lok_wynik;
}

long long l_perm(int n) // n - aktualna ilosc liczb w ciagu
{
    int wynik = 0;

    vector<int> P(n+1);
    for(int i=1; i<=n; ++i)
        P[i] = i;
    int j = n;

    // generowanie permutacji
    while(j > 1){
        rotacja(j, P);
        if(j != P[j]){
            wynik = (wynik + ile_inwersji(P)) % MOD;
            j = n;
        }
        else j--;
    }
    return wynik;
}

int main(void)
{
    ofstream wyjscie("wyjscie.txt");
    for(int i=1; i<=10; ++i){
         wyjscie << i << ": " << l_perm(i) << '\n';
    }
}
