#include <bits/stdc++.h>

using namespace std;

const int NMK_MAX = 3e5 + 1;
int n, m, k;
vector<int> stacje[NMK_MAX]; // ktore stacje naleza do danego panstwa
int ile[NMK_MAX]; // ile probek do zakonczenia badan
struct Deszcze{
    int le, ri, amt; // lewy, prawy, ilosc spadajacych
} deszcze[NMK_MAX];

// drzewo przedzialowe typu przedzial-punkt
const int LISC = 1<<19;
int drzewo[LISC<<1];

void upd(int& co, int wart)
{
    co = min(co + wart, (int)1e9);
}

void wstaw(int l, int r, int wart) // wstawianie na przedziale
{
    l += LISC;
    r += LISC;

    upd(drzewo[l], wart);
    if(l != r) upd(drzewo[r], wart);
    while(l>>1 != r>>1){
        if(l%2 == 0)
            upd(drzewo[l+1], wart);
        if(r%2 == 1)
            upd(drzewo[r-1], wart);
        l >>= 2;
        r >>= 2;
    }
}

int query(int miej) // ile w danym punkcie
{
    miej += LISC;
    int wynik = 0;
    while(miej){
        upd(wynik, drzewo[miej]);
        miej >>= 1;
    }
    return wynik;
}
// koniec drzewa


// rownolegle wyszukiwanie binarne
int le[NMK_MAX], ri[NMK_MAX], mi[NMK_MAX]; // lewe, prawe i srodkowe indeksy dla wszystkich zapytan
bool check[NMK_MAX]; // czy mi[i] to prawidlowa wartosc
vector<int> moments[NMK_MAX]; // moment sprawdzania dla danego panstwa

bool ok(int id)
{
    int spadn = 0; // ile spadlo lacznie
    for(auto i : stacje[id]) // dla stacji kontrolowanych przez panstwo o numerze id
        upd(spadn, query(i));
    return (spadn >= ile[id]);
}

void process() // sprawdzanie wszystkich wartosci dla danych midow
{
    // zerowanie drzewa przedzialowego
    for(int i=0; i<(LISC<<1); ++i)
        drzewo[i] = 0;

    for(int i=1; i<=k; ++i){
        // symulowanie deszczu
        int l = deszcze[i].le, r = deszcze[i].ri;
        if(l <= r)
            wstaw(l, r, deszcze[i].amt);
        else{
            wstaw(l, m, deszcze[i].amt);
            wstaw(1, r, deszcze[i].amt);
        }

        // sprawdzanie
        for(auto id: moments[i])
            check[id] = ok(id);

        moments[i].clear();
    }
}

void wysz_bin() // rownolegle wyszukiwanie binarne
{
    for(int i=1; i<=n; ++i){
        le[i] = 1;
        ri[i] = k;
    }

    for(int _=0; _<20; ++_){
        for(int i=1; i<=n; ++i){
            mi[i] = (le[i] + ri[i]) / 2;
            moments[mi[i]].push_back(i);
        }

        process();

        for(int i=1; i<=n; ++i){ // zmniejszanie przedzialow
            if(check[i]) ri[i] = mi[i];
            else le[i] = mi[i] + 1;
        }
    }
}
// koniec rownoleglego wyszukiwania binarnego

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    int a;
    for(int i=1; i<=m; ++i){
        cin >> a;
        stacje[a].push_back(i);
    }
    for(int i=1; i<=n; ++i)
        cin >> ile[i];

    cin >> k;
    for(int i=1; i<=k; ++i)
        cin >> deszcze[i].le >> deszcze[i].ri >> deszcze[i].amt;

    wysz_bin();
    for(int i=1; i<=n; ++i){
        if(check[i])
            cout << mi[i] << '\n';
        else cout << "NIE" << '\n';
    }
}
