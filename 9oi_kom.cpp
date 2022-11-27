#include <bits/stdc++.h>

using namespace std;

const int MAX_POT = 16, MAX_SIZE = 3e5 + 1;
int n;
vector<vector<int>> sasiedzi(MAX_SIZE);
vector<vector<int>> lca(MAX_POT, vector<int>(MAX_SIZE));
vector<int> dystans(MAX_SIZE);

void dfs(int wierz, int ojciec)
{
    lca[0][wierz] = ojciec;
    for(auto i : sasiedzi[wierz]){
        if(i != ojciec){
            dystans[i] = dystans[wierz] + 1;
            dfs(i, wierz);
        }
    }
}

int lca_wierz(int start, int koniec)
{
    if(dystans[start] < dystans[koniec])
        swap(start, koniec);

    int log;
    for(log = 1; 1 << log <= dystans[start]; ++log);
    --log;

    for(int i = log; i >= 0; --i){
        if(dystans[start] - (1 << i) >= dystans[koniec])
            start = lca[i][start];
    }

    if(start == koniec)
        return start;

    for(int i = log; i >= 0; --i){
        if(lca[i][koniec] != -1 && lca[i][start] != lca[i][koniec])
            start = lca[i][start], koniec = lca[i][koniec];
    }

    return lca[0][start];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int a, b;
    for(int i=0; i<n-1; ++i){
        cin >> a >> b;
        sasiedzi[a].push_back(b);
        sasiedzi[b].push_back(a);
    }

    dfs(1, -1);
    for(int i=1; i<MAX_POT; ++i){
        for(int j=1; j<=n; ++j)
            lca[i][j] = lca[i-1][lca[i-1][j]];
    }

    int l_zap;
    cin >> l_zap;
    int wynik = 0,
        poprzedni = 1, do_ktorego;
    for(int i=0; i<l_zap; ++i){
        cin >> do_ktorego;

        wynik += dystans[poprzedni] + dystans[do_ktorego] - 2 * dystans[lca_wierz(poprzedni, do_ktorego)];

        poprzedni = do_ktorego;
    }

    cout << wynik << '\n';
}
