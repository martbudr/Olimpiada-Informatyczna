/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace w Toruniu
    martbudr5@gmail.com
*/
#include <bits/stdc++.h>

using namespace std;

const int Q_MAX = 1e6 + 1;
int q;
vector<vector<int>> sas(Q_MAX, vector<int>(1));

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    sas[1][0] = sas[2][0] = 1;
    sas[1].push_back(2);
    sas[2].push_back(1);

    cin >> q;
    char c;
    int x; // osoba wczytywana
    int akt = 3; // nowa osoba
    while(q--){
        cin >> c >> x;
        if(c == 'W'){ // osoba wybredna
            sas[akt].push_back(x);
            sas[akt][0]++;
            sas[x].push_back(akt);
            sas[x][0]++;
            akt++;
        }
        else if(c == 'Z'){ // osoba zazdrosna
            sas[akt] = sas[x];
            for(int i=1; i<(int)sas[akt].size(); ++i){
                sas[sas[akt][i]].push_back(akt);
                sas[sas[akt][i]][0]++;
            }
            akt++;
        }
        else // zapytanie
            cout << sas[x][0] << '\n';
    }
}
