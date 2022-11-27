#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 1e5 + 1;
int n, m;
vector<vector<int>> sasiedzi(MAX_SIZE);
vector<int> pre_order(MAX_SIZE),
    low(MAX_SIZE),
    wlk_skladowej(MAX_SIZE); // wielkosc jednej z dwoch powstalych skladowych
vector<long long> rozw(MAX_SIZE);
vector<bool> czy_odw(MAX_SIZE); // czy odwiedzony
int indeks = 1;

void dfs(int wierz, int ojciec = -1)
{
    vector<int> ile_odpada;
    ile_odpada.push_back(1);
    int wielkosc = 0;
    pre_order[wierz] = indeks;
    low[wierz] = indeks++;
    czy_odw[wierz] = true;
    for(auto i : sasiedzi[wierz]){
        if(i != ojciec){
            if(czy_odw[i])
                low[wierz] = min(low[wierz], pre_order[i]);
            else{
                dfs(i, wierz);
                wlk_skladowej[wierz] += wlk_skladowej[i] + 1;
                low[wierz] = min(low[wierz], low[i]);
                if(low[i] >= pre_order[wierz])
                    ile_odpada.push_back(wlk_skladowej[i] + 1);
                else
                    wielkosc += wlk_skladowej[i] + 1;
            }
        }
    }

    wielkosc += n - (wlk_skladowej[wierz] + 1);
    ile_odpada.push_back(wielkosc);

    for(auto i : ile_odpada)
        rozw[wierz] += 1LL * i * (n-i);
}


int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        sasiedzi[a].push_back(b);
        sasiedzi[b].push_back(a);
    }

    dfs(1);

    for(int i=1; i<=n; ++i)
        cout << rozw[i] << '\n';
}
