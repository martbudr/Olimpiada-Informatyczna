#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 250001;
const int p = 19, LISC = 1 << (p-1);
int n;
vector<int> sas[N_MAX]; // synowie kazdego z wierzcholkow w drzewie wejsciowym
int pre_ord[N_MAX], // numer wierzcholka w preorderze
    pod[N_MAX], // ile potomkow kazdego z wierzcholkow
    gleb[N_MAX]; // glebokosc kazdego wierzcholka

int idx = 0; // indeks nastepnego w preorderze
void dfs(int v) // preorder
{
    pre_ord[v] = ++idx;
    for(auto u : sas[v]){
        gleb[u] = gleb[v] + 1;
        dfs(u);
        pod[v] += pod[u] + 1;
    }
}

// drzewo przedzial-punkt
int drzewo[1 << p]; // dla preorderowanych wierzcholkow (wierzcholki o kolejnych indeksach preorder - kolejne wierzcholki w drzewie przedzial-punkt)
void wstaw(int v)
{
    int lew = pre_ord[v] + LISC,
        pra = pre_ord[v] + pod[v] + LISC;

    drzewo[lew]--;
    if(lew != pra)
        drzewo[pra]--;
    while(lew/2 != pra/2){
        if(lew%2 == 0)
            drzewo[lew+1]--;
        if(pra%2 == 1)
            drzewo[pra-1]--;
        lew /= 2;
        pra /= 2;
    }
}

int suma(int v)
{
    int suma = 0;
    v += LISC;
    while(v){
        suma += drzewo[v];
        v /= 2;
    }
    return suma;
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
    }
    dfs(1);

    int m;
    cin >> m;
    char c; // znak do wczytywania
    for(int i=0; i<n+m-1; ++i){
        cin >> c;
        if(c == 'W'){ // W
            cin >> a;
            cout << gleb[a] + suma(pre_ord[a]) << '\n';
        }
        else{ // A
            cin >> a >> b;
            wstaw(b); // wstawianie do wierzcholka, do ktorego idzie
        }
    }
}
