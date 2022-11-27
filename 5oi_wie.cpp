#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e3 + 1;
int n;

int przek[N_MAX][N_MAX]; // przekatne
vector<int> sas[N_MAX-2];
int h[N_MAX], // max dla jednego liscia w poddrzewie
    d[N_MAX], // max dla dwoch lisci w poddrzewie
    t[N_MAX]; // max dla trzech lisci w poddrzewie

void ustaw(int x, int y, int nr) // wstawianie krawedzi dla nowego trojkata
{
    if(!przek[x][y])
        przek[x][y] = przek[y][x] = nr;
    else{
        sas[nr].push_back(przek[x][y]);
        sas[przek[x][y]].push_back(nr);
    }
}

void dfs(int u, int p = -1)
{
    h[u] = 1;
    int ile = 0, synowie[3]; // synowie wierzcholka u (ile i jacy)
    for(auto v : sas[u]) if(v != p){
        dfs(v, u);
        synowie[ile++] = v;
        h[u]= max(h[u], h[v]+1);
        d[u]= max(d[u], d[v]+1);
        t[u]= max(t[u], t[v]);
    }

    if(ile == 2){
        int x = synowie[0], y = synowie[1];
        d[u] = max(d[u], h[x] + h[y] + 1);
        if(d[x] != 0)
            t[u] = max(t[u], d[x] + h[y] + 1);
        if(d[y] != 0)
            t[u] = max(t[u], h[x] + d[y] + 1);
    }
    else if(ile == 3){
        int x = synowie[0], y = synowie[1], z = synowie[2];
        d[u] = max(d[u], max(h[x] + h[y], max(h[y] + h[z], h[z] + h[x])) + 1);
        if(d[x] != 0)
            t[u] = max(t[u], d[x] + max(h[y], h[z]) + 1);
        if(d[y] != 0)
            t[u] = max(t[u], d[y] + max(h[x], h[z]) + 1);
        if(d[z] != 0)
            t[u] = max(t[u], d[z] + max(h[x], h[y]) + 1);
        t[u] = max(t[u], h[x] + h[y] + h[z] + 1);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int a, b, c;
    for(int i=1; i<=n-2; ++i){ // wierzcholki trojkatow indeksowane od 1, a trojkaty - maja numery od 1
        cin >> a >> b >> c;
        ustaw(a, b, i);
        ustaw(b, c, i);
        ustaw(c, a, i);
    }

    dfs(1);
    cout << max(h[1], max(d[1], t[1])) << '\n'; // dla korzenia, czyli jednoczesnie dla calego drzewa - max globalne
}
