#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const long long M = 1e18; // max nww
const int MAX_SZUKAJ = 1e5; // max wartosc dla ktorej patrzec na nww przedzialu zaczynajacego sie od niej

long long alg_Euklidesa(int a, int b)
{
    if(b > a)
        swap(a, b);

    while(b != 0){
        int c = a;
        a = b;
        b = c%b;
    }
    return a;
}

long long NWW_przedzial(int pocz, int kon)
{
    long long nww = pocz, nwd = pocz;
    for(int i=pocz+1; i<=kon; ++i){
        nwd = alg_Euklidesa(nww, i);
        nww = nww/nwd * i;
    }
    return nww;
}

void policz_przedzialy(vector<pair<int,int>>& przedzialy)
{
    // ten sam kod co nizej tylko ze dla przedzialow o dlugosci 3
    int k = 3;
    for(int i = 1; i <= 2e6; ++i){ // po poczatkach przedzialow
        long long lok_nww = NWW_przedzial(i, i+k-1);
        if(i < przedzialy[lok_nww].first) // jesli nowy przedzial zaczyna sie wczesniej
            przedzialy[lok_nww] = make_pair(i, i+k-1);
    }

    for(k = 4; k <= 50; ++k){ // dla mozliwych dlugosci przedzialow
        for(int i = 1; i <= MAX_SZUKAJ; ++i){ // po poczatkach przedzialow
            long long lok_nww = NWW_przedzial(i, i+k-1);
            if(i < przedzialy[lok_nww].first) // jesli nowy przedzial zaczyna sie wczesniej
                przedzialy[lok_nww] = make_pair(i, i+k-1);
        }
    }
}

void szukaj_dlugosc_2(const long long nww, vector<pair<int,int>>& przedzialy) // szukanie przedzialu o dlugosci 2 dla okreslonego nww
{
    // wyszukiwanie binarne w celu znalezienia x
    // jesli x jest mniejszy lub rowny aktualnemu poczatkowi przedzialu dla nww, to zamienic ten przedzial na (x, x+1)

    const int MAX_WART = 1e9;
    int lewy = 1, prawy = MAX_WART;
    while(lewy != prawy){
        int srodek = (lewy + prawy + 1)/2;
        if(srodek * (srodek+1) <= nww)
            lewy = srodek;
        else prawy = srodek - 1;
    }

    if(lewy <= przedzialy[lewy * (lewy-1)].first)
        przedzialy[lewy * (lewy-1)] = make_pair(lewy, lewy+1);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<pair<int,int>> przedzialy(M+1, make_pair(INT_MAX, INT_MAX));
    policz_przedzialy(przedzialy);

    int n;
    cin >> n;

    long long nww;
    for(int i=0; i<n; ++i){
        cin >> nww;
        szukaj_dlugosc_2(nww, przedzialy);
        if(przedzialy[nww].first == INT_MAX)
            cout << "NIE\n";
        else
            cout << przedzialy[nww].first << ' ' << przedzialy[nww].second << '\n';
    }
}
