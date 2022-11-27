#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 2e5 + 1, M_MAX = 4e5;
int n, m;
int trzym[N_MAX][2];
vector<int> ktory(N_MAX); // ktory zbior dla danej malpki
vector<int> zbiory[N_MAX]; // vector zawierajacy wszystkie zbiory
vector<pair<int,int>> puszcz(M_MAX); // dla kazdej chwili: {malpka puszczajaca, malpka ktora jest puszczana}
bool czy_puszcz[N_MAX][2]; // czy dana malpka puszcza dana reke
vector<int> upadek(N_MAX); // moment upadku kazdej z malpek - domyslnie nie upada (-1)

void tworz() // tworzenie zbiorow
{
    for(int i=1; i<=n; ++i){
        zbiory[i].push_back(i);
        ktory[i] = i;
    }
}

void zlacz(int a, int b, int czas)
{
    if(ktory[a] == ktory[b])
        return;
    if(ktory[b] == 1 || (ktory[a] != 1 && (zbiory[ktory[a]].size() < zbiory[ktory[b]].size())))
        swap(a, b);

    int id_a = ktory[a],
        id_b = ktory[b]; // bo pozniej moga ulec zmianie przy zmianie ktory[v]
    for(auto v : zbiory[id_b]){
        zbiory[id_a].push_back(v);
        ktory[v] = id_a;
        if(ktory[v] == 1)
            upadek[v] = czas;
    }
    zbiory[id_b].clear();
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i=1; i<=n; ++i)
        cin >> trzym[i][0] >> trzym[i][1];
    tworz();

    int malpka, reka;
    for(int i=0; i<m; ++i){
        cin >> malpka >> reka;
        puszcz[i] = {malpka, trzym[malpka][reka-1]};
        czy_puszcz[malpka][reka-1] = true;
    }

    for(int i=1; i<=n; ++i){ // laczenie wszystkich tych, pomiedzy ktorymi jedna z dwoch malpek nie pusci lapki
        for(int j=0; j<2; ++j){
            if(trzym[i][j] != -1 && !czy_puszcz[i][j])
                zlacz(i, trzym[i][j], -1);
        }
    }


    for(int i=m-1; i>=0; --i){ // laczenie puszczanych w odwrotnej kolejnosci
        zlacz(puszcz[i].first, puszcz[i].second, i);
    }

    upadek[1] = -1;
    for(int i=1; i<=n; ++i)
        cout << upadek[i] << '\n';
}
