#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 201;
int n;
int tab[N_MAX][N_MAX];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j)
            cin >> tab[i][j];
    }

    for(int i=1; i<=n; ++i){
        for(int j=i+1; j<=n; ++j){
            bool sas = true;
            for(int k=1; k<=n; ++k){
                if(k != i && k != j){
                    if(tab[i][k] + tab[k][j] == tab[i][j])
                        sas = false;
                }
            }
            if(sas) cout << i << ' ' << j << '\n';
        }
    }
}
