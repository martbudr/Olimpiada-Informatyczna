#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5;
int n;
struct film{
    int kon, czas, numer;
    bool operator < (film x) const{
        return kon < x.kon;
    }
};

vector<film> przedz(N_MAX); // przedzialy

set<pair<int,int>> kandydaci; // kandydaci do branych
vector<film> wynik;

void szukaj()// szukanie tych, ktore wziac
{
    for(int i=n-1; i>=0; --i){
        int dost_czas = przedz[i].kon; // czas pomiedzy aktualna czynnoscia a poprzednia (jesli istnieje)
        if(i > 0)
            dost_czas -= przedz[i-1].kon;

        kandydaci.insert(make_pair(przedz[i].czas, i)); // i jest numerem w posortowanym vectorze (dzieki temu pozniej mozna odwolywac sie do przedz[i])
        while(dost_czas != 0 && !kandydaci.empty()){
            auto it = kandydaci.begin();
            if(it->first <= dost_czas){ // jesli miesci sie w calosci
                dost_czas -= it->first;
                wynik.push_back(przedz[it->second]); // wrzucenie do vectora zawierajacego wszystkie wynikowe
            }
            else{ // jesli tylko czesc wchodzi
                kandydaci.insert(make_pair(it->first - dost_czas, i));
                dost_czas = 0;
            }
            kandydaci.erase(it);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=0; i<n; ++i){
        cin >> przedz[i].czas >> przedz[i].kon;
        przedz[i].numer = i;
    }
    sort(przedz.begin(), przedz.begin() + n); // sortowanie vectora po koncach

    szukaj();

    // sortowanie po koncowych vectora wyjsciowego
    sort(wynik.begin(), wynik.end());

    // wypisywanie
    cout << wynik.size() << '\n';
    int moment_rozp = 1; // moment rozpoczecia kazdego z kolejnie branych przedzialow
    for(int i=0, x=wynik.size(); i<x; ++i){
        cout << wynik[i].numer+1 << ' ' << moment_rozp << '\n';
        moment_rozp += wynik[i].czas;
    }
}
