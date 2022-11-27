// program liczacy tablice z ilosciami permutacji o danym koszcie dla danego n <= 10
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e10;
long long najw_czas = 0; // najwiekszy czas jaki zajmuje posortowanie danej permutacji
vector<long long> ile_wyst(1);

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

void l_wystapien(int n) // liczba wystapien kazdego z kosztow posortowania; n - aktualna ilosc liczb w ciagu
{
    vector<int> P(n+1);
    for(int i=1; i<=n; ++i)
        P[i] = i;
    int j = n;

    ile_wyst[0]++;
    while(j > 1){
        rotacja(j, P);
        if(j != P[j]){
            long long inw = ile_inwersji(P);
            if(inw > najw_czas){
                najw_czas = inw;
                ile_wyst.resize(najw_czas+1);
            }
            ile_wyst[inw]++;

            j = n;
        }
        else j--;
    }
}

int main(void)
{
    // wersja dla jednego
    /*int n;
    cin >> n;
    l_wystapien(n);
    for(int i=0; i<=najw_czas; ++i)
        cout << ile_wyst[i] << ' ';
    cout << '\n';
    */

    // wersja dla wszystkich
    for(int i=0; i<=10; ++i){
        l_wystapien(i);
        for(int j=0; j<=najw_czas; ++j)
            cout << ile_wyst[j] << ' ';
        cout << '\n';

        ile_wyst.clear();
        ile_wyst.resize(1);
        najw_czas = 0;
    }
}
