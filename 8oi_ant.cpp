#include <bits/stdc++.h>

using namespace std;

int n;
int l_p[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23}; // liczby pierwsze
vector<pair<int,int>> kand; // kandydaci ({ilosc dzielnikow, liczba})

void gen(int ind, int ile, int liczba, int dziel) // indeks aktualnie dodawanej l pierwszej, ile jeszcze teoretycznie mozna wziac liczb, dotychczasowa liczba, ilosc dzielnikow
{
    kand.push_back({dziel, liczba});
    for(int i=1; i<=ile; ++i){
        if(l_p[ind] > n/liczba) return;
        liczba *= l_p[ind];
        gen(ind+1, i, liczba, dziel*(i+1));
    }
}

int znajdz()
{
    int ind_wynik = 0;
    for(int i=1; i<(int)kand.size(); ++i){
        if(kand[ind_wynik].first != kand[i].first || kand[ind_wynik].second > kand[i].second)
            ind_wynik = i;
    }

    return kand[ind_wynik].second;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    gen(1, 30, 1, 1);
    sort(kand.begin(), kand.end());

    cout << znajdz() << '\n';
}
