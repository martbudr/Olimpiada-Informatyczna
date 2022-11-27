#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e3;
int n, m;
vector<string> tablica(N_MAX);
vector<int> wynik;

void licz_1D(string& napis) // ile_takich_samych - ilosc takich samych
{
    vector<int> l_pierw = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
        103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
        239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383,
        389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499}; // liczby pierwsze
    int il_l_pierw=l_pierw.size(), n_lok = napis.size();

    bool jedna_lit = true; // jesli napis sklada sie z tylko jednej litery
    for(int i=1; i<n_lok; ++i){
        if(napis[i-1] != napis[i]){
            jedna_lit = false;
            break;
        }
    }
    if(jedna_lit){
        int x=sqrt(n_lok);
        for(int i=1; i<=x; ++i){ // od 1 do sqrt
            if(n_lok%i == 0)
                wynik.push_back(i);
        }
        if(x*x == n_lok) // jesli x jest dokladnie pierwiastkiem to zmniejszyc x, aby nie wypisywac tego samego dzielnika dwukrotnie
            x--;
        for(int i=x; i>=2; --i){ // od sqrt do konca
            if(n_lok%i == 0)
                wynik.push_back(n_lok/i);
        }
        wynik.push_back(n_lok);
        return;
    }

    // szukanie rozkladu
    vector<int> rozklad(il_l_pierw); // rozklad - ile kazdej liczby
    vector<pair<int,int>> l_rozk; // l_rozk - rozne liczby w rozkladzie
    int n_lok_kopia = n_lok, i=0;
    while(n_lok_kopia > 1){
        while(n_lok_kopia % l_pierw[i] == 0){
            if(rozklad[i] == 0)
                l_rozk.push_back(make_pair(l_pierw[i], i));
            rozklad[i]++;
            n_lok_kopia /= l_pierw[i];
        }
        ++i;
    }

    int akt_pierw; // liczba ktora jest wzorcem
    for(int i=0, x=l_rozk.size(); i<x; ++i){
        bool czy_wzorzec = true;
        akt_pierw = l_rozk[i].first; // aktualnie rozwazana liczba pierwsza

        for(int j=akt_pierw; j<n_lok && czy_wzorzec; j += akt_pierw){ // iterujac po kolejnych potencjalnych miejscach wystapien
            if(napis.substr(j-akt_pierw, akt_pierw) != napis.substr(j, akt_pierw)){
                czy_wzorzec = false;
                akt_pierw = -1;
            }
        }

        if(czy_wzorzec){
            akt_pierw = l_rozk[i].second; // akt_wzorzec - indeks liczby pierwszej w tablicy wszystkich l pierwszych
            break;
        }
    }

    int wart = 1;
    if(akt_pierw != -1){ // jesli istnieje jakis wzorzec
        for(int i=0; i<rozklad[akt_pierw]; ++i){
            wart *= l_pierw[akt_pierw];
            wynik.push_back(wart);
        }
    }
    if(wart != n_lok)
        wynik.push_back(n_lok);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i=0; i<n; ++i)
        cin >> tablica[i];

    if(n == 1) // jesli tablica jest jednowymiarowa
        licz_1D(tablica[0]);
    else if(m == 1){
        string kolumna;
        for(int i=0; i<n; ++i)
            kolumna.push_back(tablica[i][0]);
        licz_1D(kolumna);
    }
    else{ // w przeciwnym wypadku - jesli wiersze lub kolumny sa rowne (dla innych przypadkow nie dziala)
        bool czy_wiersze_rowne = true;
        for(int i=1; i<n; ++i){
            if(tablica[i-1] != tablica[i]){
                czy_wiersze_rowne = false;
                break;
            }
        }
        if(czy_wiersze_rowne)
            licz_1D(tablica[0]);
        else{
            bool czy_kolumny_rowne = true;
            for(int i=1; i<m; ++i){ // dla kazdej kolumny
                for(int j=0; j<n; ++j){ // w kazdym wierszu
                    if(tablica[j][i-1] != tablica[j][i]){
                        czy_kolumny_rowne = false;
                        break;
                    }
                }
            }
            if(czy_kolumny_rowne){
                string kolumna;
                for(int i=0; i<n; ++i)
                    kolumna.push_back(tablica[i][0]);
                licz_1D(kolumna);
            }
        }
    }

    int x = wynik.size();
    cout << x << '\n';
    for(int i=0; i<x; ++i)
        cout << wynik[i] << ' ';
    cout << '\n';
}
