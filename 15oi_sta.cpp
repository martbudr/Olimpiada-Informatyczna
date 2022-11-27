#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n;
vector<int> sas[N_MAX];
long long wierz_pod[N_MAX], // ile wierzcholkow w poddrzewie o korzeniu w danym wierz
    sum_odl[N_MAX], // suma odleglosci do wierzcholkow pod
    wynik[N_MAX];
int dla_ktorego = 1;

void dfs1(int wierz, int ojciec = -1)
{
    wierz_pod[wierz] = 1;
    sum_odl[wierz] = 0;
    for(auto syn : sas[wierz]) if(syn != ojciec){
        dfs1(syn, wierz);
        wierz_pod[wierz] += wierz_pod[syn];
        sum_odl[wierz] += sum_odl[syn] + 1;
    }
}

void dfs2(int wierz, int ojciec = -1)
{
    if(ojciec == -1)
        wynik[wierz] = sum_odl[wierz];

    for(auto syn : sas[wierz]) if(syn != ojciec){
        wynik[syn] = wynik[wierz] + n - 2*wierz_pod[syn];
        if(wynik[syn] > wynik[dla_ktorego])
            dla_ktorego = syn;
        dfs2(syn, wierz);
    }
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
    dfs2(1);
    cout << dla_ktorego << '\n';
}
