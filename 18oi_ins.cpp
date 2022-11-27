#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n;
vector<int> sas[N_MAX]; // sasiedzi
int pod[N_MAX]; // ilosci wierzcholkow w poddrzewie z korzeniem w danym wierzcholku
vector<long long> wynik(N_MAX, -1);
pair<int,int> nast = {1, -1}; // nastepny wierzcholek do rozwazenia
long long sciezki[N_MAX];
long long calk; // czas calkowity
int najw; // najwieksze poddrzewo z korzeniem w danym

void dfs1(int v, int p = -1)
{
    pod[v] = 1;
    for(auto u : sas[v]) if(u != p){
        dfs1(u, v);
        pod[v] += pod[u];
    }
}

void dfs2(int v, int p = -1, int dlu = 0) // szukanie dl wszystkich sciezek i zapisanie maksymalnych dla danego poddrzewa w tablicy
{
    sciezki[v] = dlu;
    calk += sciezki[v];
    for(auto u : sas[v]) if(u != p){
        dfs2(u, v, dlu+1);
        sciezki[v] = max(sciezki[v], sciezki[u]);
    }
}

long long znajdz(int v, int dl_akt = 0) // szukanie najdluzszej sciezki - kolejny dfs (dl_akt - dlugosc sciezki od korzenia do aktualnego wierzcholka)
{
    calk = 0;
    dfs2(v);
    long long nax = 0; // jak daleko jest najdalszy w najwiekszym poddrzewie
    int ile_pod = 0; // rozmiar poddrzewa
    for(auto u : sas[v]){
        if(pod[u] > ile_pod){
            najw = u;
            nax = sciezki[u];
            ile_pod = pod[u];
        }
        else if(pod[u] == ile_pod)
            nax = max(nax, sciezki[u]);
    }

    return 2*calk - nax;
}

void sprawdz(int v, int p)
{
    // aktualizowanie, aby aktualny v faktycznie byl korzeniem
    if(p != -1){
        pod[p] -= pod[v];
        pod[v] = n;
    }
    for(auto u : sas[v]) if(2*pod[u] > n){
        if(u != p)
            nast = {u, v};
        else
            nast = {0, 0};
        return;
    }
    // jesli nie bylo zadnego rozm > (n/2)
    wynik[v] = znajdz(v);
    nast = make_pair(najw, v);
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

    dfs1(1);
    while(nast.first != 0)
        sprawdz(nast.first, nast.second);

    for(int i=1; i<=n; ++i)
        cout << wynik[i] << '\n';
}
