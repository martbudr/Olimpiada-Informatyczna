#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n;
vector<int> sas[N_MAX];
int pod[N_MAX]; // ilosc wierzcholkow w poddrzewie rooted at u (wliczajac u)
int centr, centr_2 = -1;
int nax_fo; // w ktorym poddrzewie mamy najwiecej wierzcholkow dla pierwszego centroidu
long long all = 0; // wszystkie sciezki wlacznie z powrotna

void cnt_pod(int u, int p = -1)
{
    pod[u] = 1;
    for(auto v : sas[u]) if(v != p){
        cnt_pod(v, u);
        pod[u] += pod[v];
        all += 2*pod[v];
    }
}

void cen_cnt(int u)
{
    bool fnd = true;
    int nax = 0; // dla ktorego sasiada mamy maksymalna ilosc
    for(auto v : sas[u]){
        if(pod[v] > nax){
            nax = pod[v];
            nax_fo = v;
        }

        if(pod[v] > n/2){
            // aktualizacja wartosci pod, bo zmieniamy korzen drzewa z u na v
            pod[u] -= pod[v];
            pod[v] += pod[u];
            fnd = false;
            cen_cnt(v);
        }
    }
    if(fnd){
        centr = u;

        // sprawdzanie potencjalnego drugiego centroidu
        bool scnd = true;
        pod[u] -= pod[nax_fo];
        pod[nax_fo] += pod[u];
        for(auto x : sas[nax_fo]){
            if(pod[x] > n/2) scnd = false;
        }

        if(scnd) centr_2 = nax_fo;
    }
}

int cnt_longest(int u, int p) // liczenie najdluzszej sciezki z danego wierzcholka do liscia
{
    int ans = 0;
    for(auto v : sas[u]) if(v != p){
        ans = max(ans, cnt_longest(v, u)+1);
    }
    return ans;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int a, b;
    for(int i=0; i<n-1; ++i){
        cin >> a >> b;
        sas[a].push_back(b);
        sas[b].push_back(a);
    }

    if(n == 1){
        cout << 0 << '\n';
        return 0;
    }

    cnt_pod(1);
    cen_cnt(1);

    all = 0;
    cnt_pod(centr);

    bool roz = false; // czy rozwazono ten drugi
    for(int i=1; i<=n; ++i){
        if(i != centr && i != centr_2){
            cout << -1 << '\n';
            continue;
        }

        // jesli jest centroidem, czyli istnieje wynik dla niego
        long long ans = all;
        if(i == centr){
            if(roz){
                pod[centr_2] -= pod[centr];
                pod[centr] += pod[centr_2];
            }
            if(2*pod[nax_fo] == n)
                ans -= cnt_longest(nax_fo, centr) + 1;
            else ans -= cnt_longest(centr, -1);
        }
        else{
            pod[centr] -= pod[centr_2];
            pod[centr_2] += pod[centr];
            if(2*pod[centr] == n)
                ans -= cnt_longest(centr, centr_2) + 1;
            else ans -= cnt_longest(centr_2, -1);
            roz = true;
        }
        cout << ans << '\n';
    }
}
