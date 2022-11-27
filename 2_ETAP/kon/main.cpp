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
bool czy_zazdr = true;
vector<pair<char,int>> wejscie(Q_MAX); // operacja, osoba
int akt = 3; // nowa osoba

void nie_zazdr()
{
    sas[1][0] = sas[2][0] = 1;
    sas[1].push_back(2);
    sas[2].push_back(1);
    for(int i=0; i<q; ++i){
        int x = wejscie[i].second;
        if(wejscie[i].first == 'W'){ // osoba wybredna
            sas[akt].push_back(x);
            sas[akt][0]++;
            sas[x].push_back(akt);
            sas[x][0]++;
            akt++;
        }
        else if(wejscie[i].first == 'Z'){ // osoba zazdrosna
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

void zazdr()
{
    vector<int> podzbior(Q_MAX);
    podzbior[1] = 0;
    podzbior[2] = 1;
    int moc[2] = {1, 1};

    for(int i=0; i<q; ++i){
        int x = wejscie[i].second;
        if(wejscie[i].first == 'Z'){
            podzbior[akt] = podzbior[x];
            moc[!podzbior[akt]]++;
            akt++;
        }
        else
            cout << moc[podzbior[x]] << '\n';
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> q;
    for(int i=0; i<q; ++i){
        cin >> wejscie[i].first >> wejscie[i].second;
        if(wejscie[i].first == 'W')
            czy_zazdr = false;
    }

    if(czy_zazdr)
        zazdr();
    else
        nie_zazdr();
}
