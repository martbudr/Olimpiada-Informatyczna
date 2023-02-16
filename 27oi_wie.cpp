#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 2e5 + 1;
int n;
long long miej[N_MAX];
int he[N_MAX];

int dzi[N_MAX]; // wielkosc dziury

long long N1, N2;
int H1, H2;

long long nin_big = 0, nin_sma = 0; // ile co najmniej duzych i malych
priority_queue<pair<int,int>> Q; // ile malych w kazdej dziurze
bool too_much(int len, int pocz)
{
    if(nin_big <= N1 && nin_sma <= N2)
        return false;
    else if(nin_big > N1 && nin_sma <= N2){
        int to_ch = nin_big-N1;
        nin_sma += (H1/H2) * to_ch;
        nin_big -= to_ch;

        if(nin_sma <= N2)
            return false;
    }
    else if(nin_sma > N2 && nin_big <= N1){
        int to_ch = nin_sma-N2;
        int chan = (to_ch + (H1/H2)-1) / (H1/H2);
        nin_big += chan;
        for(int i=0; i<chan && !Q.empty(); ){
            pair<int,int> curr = Q.top();
            Q.pop();
            if(curr.second >= pocz){
                nin_sma -= curr.first;
                ++i;
            }
        }

        if(nin_big <= N1 && nin_sma <= N2 && nin_big+nin_sma >= len)
            return false;
    }

    return true;
}

long long calc_ans()
{
    if(H1 < H2){
        swap(N1, N2); swap(H1, H2);
    }
    int amt_dz = n-1; // ilosc dziur

    long long ans = N1 + N2 + 1;
    int pocz = 0; // gdzie zaczyna sie gasienica
    for(int i=0; i<amt_dz; ++i){ // iterujemy po wszystkich dziurach
        // dodajemy koniec
        nin_big += dzi[i]/H1;
        nin_sma += (dzi[i]%H1 + H2-1)/H2;
        Q.push({(dzi[i]%H1 + H2-1)/H2, i});

        // usuwamy z poczatku tak dlugo jak trzeba
        while(too_much(i-pocz+1, pocz)){
            nin_big -= dzi[pocz]/H1;
            nin_sma -= (dzi[pocz]%H1 + H2-1)/H2;
            pocz++;
        }
        // aktualizujemy odpowiedz
        if(pocz <= i)
            ans = max(ans, N1+N2+1 + i-pocz+1);
    }
    return ans;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=0; i<n; ++i){
        cin >> miej[i] >> he[i];

        if(i != 0){
            dzi[i-1] = miej[i] - he[i] - miej[i-1];
        }
    }
    cin >> N1 >> H1 >> N2 >> H2;

    cout << calc_ans() << '\n';
}
