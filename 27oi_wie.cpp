#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 2e5 + 1;
int n, calk_ile = 1; // calk_ile - ile wszystkich przedzialow (dziur o jedna mniej)
pair<int,int> przedz[N_MAX]; // przedzialy, ktore na pewno upadaja razem (bo sa podane tak na wejsciu); first - poczatek, second - koniec
int ile_w_przedz[N_MAX]; // ile w danym przedziale

int il_1, wys_1, il_2, wys_2; // opis wstawianych

int sumy_1[N_MAX], sumy_2[N_MAX];
pair<int, int> ile_potrz[N_MAX-1]; // ile potrzebnych z danego rodzaju do wypelnienia danej dziury

int dp[N_MAX][N_MAX];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int a, b;
    cin >> przedz[1].first >> przedz[1].second;
    ile_w_przedz[1] = 1;
    for(int i=2; i<=n; ++i){ // wczytywanie i merge'owanie tych, ktore upadna razem
        cin >> a >> b;
        if(przedz[calk_ile] >= a){
            przedz[calk_ile].second = max(przedz[calk_ile].second, a+b);
            ile_w_przedz[calk_ile]++;
        } else{
            przedz[++calk_ile] = make_pair(a, a+b);
            ile_w_przedz[calk_ile] = 1;
        }
    }
    cin >> il_1 >> wys_1 >> il_2 >> wys_2;

    // liczenie potrzebnych dla przedzialow
    for(int i=1; i<=calk_ile-1; ++i){
        int dl = przedz[i+1].first - przedz[i].second + 1;
        ile_potrz[i] = make_pair(dl / wys_1, (dl%wys_1 + (((dl%wys_1) % wys_2 == 0) ? 0 : wys_2))/wys_2);
    }

    // dp - maksimum na przedziale biorac pierwsze k dziur, z czego ostatnia to ta o numerze i
    for(int k=1; k<=calk_ile-1; ++k){ // po ilosci dziur
        for(int i=1; i<=calk_ile-1; ++i){ // po dziurze bedacej ostatnia rozwazana

        }
    }
}
