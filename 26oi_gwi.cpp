#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1;
int n, start;
vector<int> lewe(N_MAX), prawe(N_MAX); // koszty przejscia w dana strone
vector<long long> lewe_prefix(N_MAX), prawe_prefix(N_MAX),
        opt_sufix(N_MAX); // opt - optymalny
vector<int> opt_il_lewych(N_MAX);
list<int> gwiazdy; // aktualnie dostepne do wziecia gwiazdy
long long wynik = LLONG_MAX;
int ile_pocz = 0; // ile L lub R w postaci LLL...R lub RRR...L
bool czy_w_lewa = true; // czy postaci LLL...R

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> start;
    for(int i=1; i<n; ++i){
        cin >> lewe[i] >> prawe[i];

        // liczenie prefixow
        lewe_prefix[i] = lewe_prefix[i-1] + lewe[i];
        prawe_prefix[i] = prawe_prefix[i-1] + prawe[i];
        gwiazdy.push_back(i);
    }
    gwiazdy.push_back(n);

    for(int i=n-1; i>=1; --i){ // liczenie sufixow
        opt_sufix[i] = opt_sufix[i+1] + min(lewe[i], prawe[i]);
        opt_il_lewych[i] = opt_il_lewych[i+1] + (lewe[i] <= prawe[i]);
    }

    for(int i=1; i<start; ++i){
        if(lewe_prefix[i] + prawe[i+1] + opt_sufix[i+2] < wynik){
            wynik = lewe_prefix[i] + prawe[i+1] + opt_sufix[i+2];
            ile_pocz = i;
        }
    }
    for(int i=1; i<=n-start; ++i){
        if(prawe_prefix[i] + lewe[i+1] + opt_sufix[i+2] < wynik){
            wynik = prawe_prefix[i] + lewe[i+1] + opt_sufix[i+2];
            ile_pocz = i;
            czy_w_lewa = false; // w prawa jest bardziej optymalnie
        }
    }

    // ustawianie iteratora do usuwania odpowiednich gwiazd
    list<int>::iterator gwiazda = gwiazdy.begin(); // aktualna gwiazda do wypisania, po czym usuniecia
    for(int i=1; i<start; ++i)
        gwiazda++;

    // wypisanie
    cout << wynik << '\n';
    for(int i=0; i<ile_pocz; ++i){ // poczatkowe (ile_pocz-1 skokow, bo pierwszy usuwany to startowy)
        cout << (*gwiazda) << ' ';
        auto do_usu = gwiazda;
        if(czy_w_lewa)
            gwiazda--;
        else gwiazda++;

        gwiazdy.erase(do_usu);
    }

    // poprzedni - usuniety (zostaly tylko te, ktore sa do usuniecia)
    // pojedynczy - najdalej w kierunku, w ktorym wczesniej bylo skakane - ile_pocz-ty skok w dana strone
    gwiazda = (czy_w_lewa) ? gwiazdy.begin() : --gwiazdy.end();
    cout << (*gwiazda) << ' ';
    gwiazdy.erase(gwiazda);

    //optymalny sufix
    // ustawianie w miejsce, z ktorego teraz bedziemy usuwac (R w LLL...R lub L w RRR...L)
    gwiazda = gwiazdy.begin();
    for(int i=0; i<opt_il_lewych[ile_pocz + 2]; ++i) // ustawiamy na opt_il_lewych[ile_pocz+2], ktory pozniej jest usuwany
        gwiazda++;

    for(int i=ile_pocz + 2; i<n; ++i){
        cout << (*gwiazda) << ' ';
        auto do_usu = gwiazda;
        if(lewe[i] <= prawe[i])
            gwiazda--;
        else gwiazda++;

        gwiazdy.erase(do_usu);
    }
    if(!gwiazdy.empty()) // jesli cokolwiek pozostalo
        cout << (*gwiazda) << '\n';
}
