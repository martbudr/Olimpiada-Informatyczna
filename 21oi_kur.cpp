#include <bits/stdc++.h>

using namespace std;

const int NM_MAX = 5e5 + 1, P = 25; // P - ilosc losowanych liczb
int n, m;
int wej[NM_MAX];
struct Zap{ // zapytania
    int pocz, kon;
} zap[NM_MAX];

vector<int> zap_id[NM_MAX]; // miejsca o 1 przed poczatkami zapytan i koncow zapytan
struct Kand{
    int wart, il; // wartosc i ilosc
} kand[NM_MAX];

int cnt[NM_MAX];
int wynik[NM_MAX];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    srand(time(NULL));

    cin >> n >> m;
    for(int i=1; i<=n; ++i)
        cin >> wej[i];

    for(int i=0; i<m; ++i){
        cin >> zap[i].pocz >> zap[i].kon;
        zap_id[zap[i].pocz-1].push_back(i);
        zap_id[zap[i].kon].push_back(i);
    }

    for(int _=0; _<P; ++_){
        for(int i=0; i<=n; ++i)
            cnt[i] = 0;
        for(int i=0; i<m; ++i){
            kand[i].wart = wej[rand() % (zap[i].kon - zap[i].pocz + 1) + zap[i].pocz]; // losowanie kandydatow
            kand[i].il = 0;
        }

        for(int i=0; i<=n; ++i){
            if(i) cnt[wej[i]]++;

            for(auto id : zap_id[i]){
                if(wynik[id]) continue;
                kand[id].il += (i == zap[id].pocz-1 ? -cnt[kand[id].wart] : cnt[kand[id].wart]);
            }
        }

        for(int i=0; i<m; ++i){
            if(kand[i].il > (zap[i].kon - zap[i].pocz + 1)/2)
                wynik[i] = kand[i].wart;
        }
    }

    for(int i=0; i<m; ++i)
        cout << wynik[i] << '\n';
}
