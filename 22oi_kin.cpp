#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1, p = 21, LISC = (1 << (p-1));
int n, m; // liczba dni promocji; liczba filmow
vector<int> ciag(N_MAX), wagi(N_MAX); // ciag filmow wystepujacych po kolei; fajnosc kazdego z filmow
vector<long long> drzewo(1 << p), na_pozniej(1 << p);

void lok_wstaw(int nr_wierz, long long wart) // wstawianie w dane miejsce
{
    drzewo[nr_wierz] += wart;
    if(nr_wierz < LISC)
        na_pozniej[nr_wierz] += wart;
}

void spr_akt(int nr_wierz) // idac od gory sprawdzanie, czy zaden nie chcial aktualizowac swoich synow (aby uzyskac pozniej wlasciwa wartosc dla nr_wierz)
{
    for(int i=p-1; i > 0; --i){
        int akt_wierz = nr_wierz >> i; // aktualny wierzcholek
        if(na_pozniej[akt_wierz] != 0){
            lok_wstaw(2*akt_wierz, na_pozniej[akt_wierz]);
            lok_wstaw(2*akt_wierz + 1, na_pozniej[akt_wierz]);
            na_pozniej[akt_wierz] = 0;
        }
    }
}

void zbuduj(int nr_wierz) // poprawianie biorac pod uwage nowe wartosci
{
    nr_wierz >>= 1; // bierzemy ojca
    while(nr_wierz){
        drzewo[nr_wierz] = max(drzewo[2*nr_wierz], drzewo[2*nr_wierz + 1]) + na_pozniej[nr_wierz];
        na_pozniej[nr_wierz] = 0;
        nr_wierz >>= 1;
    }
}

void wstaw(int lewy, int prawy, int wart)
{
    int lewy_kop = lewy += (LISC-1), prawy_kop = prawy += (LISC-1); // lewy kopia, prawy kopia
    spr_akt(lewy);
    spr_akt(prawy);

    lok_wstaw(lewy, wart);
    if(lewy != prawy) lok_wstaw(prawy, wart);
    while((lewy>>1) != (prawy>>1)){
        if(lewy%2 == 0) lok_wstaw(lewy+1, wart);
        if(prawy%2 == 1) lok_wstaw(prawy-1, wart);
        lewy >>= 1; prawy >>= 1;
    }

    zbuduj(lewy_kop);
    zbuduj(prawy_kop);
}

long long przedz_max() // max na przedziale
{
    return drzewo[1];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i=1; i<=n; ++i)
        cin >> ciag[i];
    for(int i=1; i<=m; ++i)
        cin >> wagi[i];

    vector<int> nast(N_MAX), // nastepny film tego samego rodzaju co ten na pozycji o indeksie i
            ost(N_MAX); // ostatni film danego rodzaju
    for(int i=n; i>=1; --i){
        int film = ciag[i]; // rodzaj aktualnie rozwazanego filmu

        nast[i] = (ost[film] == 0) ? n+1 : ost[film];
        ost[film] = i;

        if(nast[i] != n+1)
            wstaw(nast[i], nast[nast[i]]-1, -wagi[film]);
        wstaw(i, nast[i]-1, wagi[film]);
    }

    long long wynik = przedz_max();
    for(int i=1; i<n; ++i){ // usuwanie kolejnych poczatkowych
        int film = ciag[i]; // rodzaj aktualnie rozwazanego filmu

        wstaw(i, nast[i] - 1, -wagi[film]);
        if(nast[i] != n+1)
            wstaw(nast[i], nast[nast[i]]-1, wagi[film]);

        wynik = max(wynik, przedz_max());
    }

    cout << wynik << '\n';
}
