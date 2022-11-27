/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace w Toruniu
    martbudr5@gmail.com
*/
#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1;
int n, k;
int agenci[N_MAX];
bool czy_agent[N_MAX];
vector<int> sas[N_MAX];
int dl[N_MAX]; // dlugosc pojedynczego przejscia do kazdego potomka danego wierzcholka
int naj_sc[N_MAX]; // najdluzsza sciezka

void licz_poddrzewa(int v, int p = -1)
{
    for(auto u : sas[v]) if(u != p){
        licz_poddrzewa(u, v);
        dl[v] += dl[u] + 1;
        naj_sc[v] = max(naj_sc[v], naj_sc[u] + 1);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    int x;
    for(int i=0; i<k; ++i){
        cin >> x;
        agenci[i] = x;
        czy_agent[x] = true;
    }

    int a, b;
    for(int i=0; i<n-1; ++i){
        cin >> a >> b;
        sas[a].push_back(b);
        sas[b].push_back(a);
    }

    licz_poddrzewa(agenci[0]);
    cout << 2 * dl[agenci[0]] - naj_sc[agenci[0]] << '\n';
}
