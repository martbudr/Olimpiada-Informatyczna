#include <bits/stdc++.h>

using namespace std;

void dodaj(int kolor, vector<int>& ile_do_dodania, set<int>& niezerowe) // dodawanie koloru
{
    if(ile_do_dodania[kolor] == 0)
        niezerowe.insert(kolor);
    else if(ile_do_dodania[kolor] == 1)
        niezerowe.erase(kolor);

    ile_do_dodania[kolor]--;
}

void usun(int kolor, vector<int>& ile_do_dodania, set<int>& niezerowe) // usuwanie koloru
{
    if(ile_do_dodania[kolor] == 0)
        niezerowe.insert(kolor);
    else if(ile_do_dodania[kolor] == -1)
        niezerowe.erase(kolor);

    ile_do_dodania[kolor]++;
}

int zlicz_wyst(long long dl_ladny, int n, vector<int>& lancuch, vector<int>& ile_do_dodania, set<int>& niezerowe)
{
    if(dl_ladny > n)
        return 0;

    int wynik = 0, i = 0;
    for(; i < dl_ladny; ++i) // pierwszy kandydat na ladnego, ktory bedzie pozniej modyfikowany
        dodaj(lancuch[i], ile_do_dodania, niezerowe);

    if(niezerowe.empty()) // jesli pierwszy kandydat jest ladny
        wynik++;

    for(; i < n; ++i){
        int poprz_pocz = i - dl_ladny; // poprz_pocz - poczatek poprzedniego (do usuniecia); i - koniec nowego (do dodania)
        usun(lancuch[poprz_pocz], ile_do_dodania, niezerowe); // usuwanie poczatku
        dodaj(lancuch[i], ile_do_dodania, niezerowe); // dodawanie konca

        if(niezerowe.empty()) // jesli kandydat jest ladny
            wynik++;
    }
    return wynik;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m; // dl lancucha i dl opisu ladnego lancucha
    cin >> n >> m;

    vector<int> ladny_ilosc(m), ladny_kolor(m), lancuch(n), ile_do_dodania(n + 1); // ile_do_dodania - o ile jest za duzo lub za malo danego koloru w kandydacie na ladnego
    set<int> niezerowe; // ktore jeszcze musza byc dodane lub usuniete z ladnego
    long long dl_ladny = 0; // dlugosc ladnego fragmentu
    for(auto &i : ladny_ilosc){
        cin >> i;
        dl_ladny += i;
    }
    for(int i=0; i<m; ++i){
        cin >> ladny_kolor[i];
        ile_do_dodania[ladny_kolor[i]] = ladny_ilosc[i];
        niezerowe.insert(ladny_kolor[i]);
    }
    for(auto &i : lancuch)
        cin >> i;

    cout << zlicz_wyst(dl_ladny, n, lancuch, ile_do_dodania, niezerowe) << '\n';
}
