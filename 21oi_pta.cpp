#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n, q, k;
int drzewa[N_MAX];

void wstaw(int i, list<pair<int,int>>& Q) // wstawianie wartosci do kolejki
{
    while(!Q.empty() && Q.back().first > drzewa[i]) Q.pop_back();
    Q.push_back({i, drzewa[i]});
}

int wez_max(int i, list<pair<int,int>>& Q) // zwraca indeks do najwiekszego
{
    while(Q.front().second < i-k+1) Q.pop_front();
    return Q.front().second;
}

void polacz(list<pair<int,int>>& Q, list<pair<int,int>>& P)
{
    Q.merge(P);
    P.clear();
}

int solve()
{
    int zmecz[N_MAX]; // minimalne zmeczenie na prefiksie
    int zmecz_max = 0;

    list<pair<int,int>> Q, // kolejka K-max - {indeks, wartosc} - zawiera te, ktore maja najmniejsze zmeczenie na przedziale
        P; // zawiera cala reszte

    zmecz[0] = 0;
    wstaw(0, Q);
    for(int i=1; i<n; ++i){ // liczenie kolejnych wartosci
        int najw = drzewa[wez_max(i, Q)]; // najwiekszy na przedziale
        if(najw > drzewa[i]){
            zmecz[i] = zmecz[najw];
            wstaw(i, Q);
        }
        if(zmecz[i] > zmecz_max)
            polacz(Q, P);

    }
    return zmecz[n-1];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=0; i<n; ++i)
        cin >> drzewa[i];
    cin >> q;
    for(int i=0; i<q; ++i){
        cin >> k;
        cout << solve() << '\n';
    }
}
