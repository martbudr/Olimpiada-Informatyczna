#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 1e5 + 1;
int n, m;
vector<vector<int>> sas(MAX_SIZE);
vector<int> pre_ord(MAX_SIZE),
    low(MAX_SIZE),
    wlk_skl(MAX_SIZE); // wielkosc jednej z dwoch powstalych skladowych
vector<long long> rozw(MAX_SIZE);
vector<bool> czy_odw(MAX_SIZE); // czy odwiedzony
int id = 1;

void dfs(int u, int p = -1)
{
    vector<int> ile_odp;
    ile_odp.push_back(1);
    int wlk = 0;
    pre_ord[u] = id;
    low[u] = id++;
    czy_odw[u] = true;
    for(auto v : sas[u]){
        if(v != p){
            if(czy_odw[v])
                low[u] = min(low[u], pre_ord[v]);
            else{
                dfs(v, u);
                wlk_skl[u] += wlk_skl[v] + 1;
                low[u] = min(low[u], low[v]);
                if(low[v] >= pre_ord[u])
                    ile_odp.push_back(wlk_skl[v] + 1);
                else
                    wlk += wlk_skl[v] + 1;
            }
        }
    }

    wlk += n - (wlk_skl[u] + 1);
    ile_odp.push_back(wlk);

    for(auto i : ile_odp)
        rozw[u] += 1LL * i * (n-i);
}


int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        sas[a].push_back(b);
        sas[b].push_back(a);
    }

    dfs(1);

    for(int i=1; i<=n; ++i)
        cout << rozw[i] << '\n';
}
