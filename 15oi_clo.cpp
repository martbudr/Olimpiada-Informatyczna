#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 1e6 + 1;
vector<vector<int>> sasiedzi(MAX_SIZE);
vector<int> ojcowie(MAX_SIZE);
vector<bool> czy_odw(MAX_SIZE);
vector<int> rozw(MAX_SIZE);
int zmiana = -1; // wierzcholek dla ktorego brana jest krawedz spoza drzewa dfs

void dfs(int wierz, int ojciec = -1)
{
    ojcowie[wierz] = ojciec;
    czy_odw[wierz] = true;
    for(auto i : sasiedzi[wierz]){
        if(i != ojciec){
            if(czy_odw[i]){
                if(zmiana == -1){
                    zmiana = i;
                    rozw[i] = wierz;
                }
            } else{
                rozw[i] = wierz;
                dfs(i, wierz);
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        sasiedzi[a].push_back(b);
        sasiedzi[b].push_back(a);
    }

    for(int i=1; i<=n; ++i){
        if(czy_odw[i])
            continue;

        dfs(i);
        if(zmiana == -1){
            cout << "NIE" << '\n';
            return 0;
        }

        while(zmiana != i){
            rozw[ojcowie[zmiana]] = zmiana;
            zmiana = ojcowie[zmiana];
        }
        zmiana = -1;
    }

    cout << "TAK" << '\n';
    for(int i=1; i <= n; ++i)
        cout << rozw[i] << '\n';
}
