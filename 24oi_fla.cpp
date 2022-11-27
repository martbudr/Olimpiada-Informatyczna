#include <bits/stdc++.h>

using namespace std;

int znajdz_ilosc_ruchow(vector<int>& polozenie, vector<int>& dol, vector<int>& gora)
{
    int n = polozenie.size();
    if(n == 0)
        return 0;

    int x_wynik = polozenie[n-1], y_wynik; // wartosci do liczenia wyniku na koniec

    for(int i=n-1; i>0; --i) // polozenie to teraz dlugosci drogi z jednej przeszkody do nastepnej (0-we polozenie - odleglosc od startu)
        polozenie[i] -= polozenie[i-1];

    int przedz_dol = 0, przedz_gora = 0; // granice do ktorych faktycznie da sie dojsc (w sensie przeszkody nie stoja na przeszkodzie)
        // (musza byc tej samej parzystosci co maksymalne miejsca dojscia)
    int praw_reszta = 0; // prawidlowa reszta (czy aktualne wierzcholki powinny byc parzyste czy nieparzyste)
    for(int i=0; i<n; ++i){
        int max_dol = przedz_dol - polozenie[i], // do jakich maksymalnych da sie dojsc jakby nie bylo dalszej przeszkody
            max_gora = przedz_gora + polozenie[i];

        praw_reszta = (praw_reszta + polozenie[i])%2;
        int dol_reszta = (dol[i]+1 >= 0) ? (dol[i]+1)%2 : (-(dol[i]+1))%2,
            gora_reszta = (gora[i]-1 >= 0) ? (gora[i]-1)%2 : (-(gora[i]-1))%2; // parzystosc dolu i gory kandydatow na granice przedzialu

        przedz_dol = max(dol[i] + 1 + (dol_reszta != praw_reszta), max_dol);
        przedz_gora = min(gora[i] - 1 - (gora_reszta != praw_reszta), max_gora);

        if(przedz_dol > przedz_gora) // jesli nie znaleziono prawidlowego przedzialu
            return -1;
    }

    y_wynik = przedz_dol;
    return (x_wynik + y_wynik) / 2;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, x; // n - liczba przeszkod, x - polozenie mety
    cin >> n >> x;

    vector<int> polozenie(n), dol(n), gora(n); // polozenie, dol i gora danej przeszkody
    for(int i=0; i<n; ++i)
        cin >> polozenie[i] >> dol[i] >> gora[i];

    int ilosc_ruchow = znajdz_ilosc_ruchow(polozenie, dol, gora);
    if (ilosc_ruchow == -1)
        cout << "NIE" << '\n';
    else
        cout << ilosc_ruchow << '\n';
}
