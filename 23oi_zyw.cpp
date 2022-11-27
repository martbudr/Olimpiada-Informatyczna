#include <bits/stdc++.h>

using namespace std;

const int L_MAX = 1e3;
int n, m;
vector<vector<char>> pionowe(L_MAX, vector<char>(L_MAX)), // pionowe granice; najpierw - wczytane rodzaje zywoplotow, pozniej - wynik
    poziome(L_MAX, vector<char>(L_MAX)),
    wynik_pion(L_MAX, vector<char>(L_MAX)),
    wynik_poz(L_MAX, vector<char>(L_MAX));

vector<int> podzbior(L_MAX*L_MAX); // poprzednie pole w podzbiorze

vector<int> wynik(2, 0); // wynik[0] - tuje, wynik[1] - cisy

inline int nr_pola(int i, int j) {return i*m + j;}

int pocz_podzbioru(int pole)
{
    if(podzbior[pole] == pole)
        return pole;
    podzbior[pole] = pocz_podzbioru(podzbior[pole]);
    return podzbior[pole];
}

void polacz(int pole_1, int pole_2)// polacz podzbiory
{
    podzbior[podzbior[pole_2]] = podzbior[pole_1];
}

void rozwiaz()
{
    char lit[] = {'T', 'C'};

    for(int i=0; i<n*m; ++i)
        podzbior[i] = i;

    for(int _=0; _<2; ++_){
        for(int i=0; i<n; ++i){ // dla pionowych
            for(int j=0; j<m-1; ++j){
                if(pionowe[i][j] == lit[_]){
                    int pole_1 = nr_pola(i, j),
                        pole_2 = pole_1 + 1;
                    if(pocz_podzbioru(pole_1) != pocz_podzbioru(pole_2)){
                        polacz(pole_1, pole_2);
                        wynik_pion[i][j] = '.';
                    } else{
                        wynik[_]++;
                        wynik_pion[i][j] = 'Z';
                    }
                }
            }
        }

        for(int i=0; i<n-1; ++i){ // dla poziomych
            for(int j=0; j<m; ++j){
                if(poziome[i][j] == lit[_]){
                    int pole_1 = nr_pola(i, j),
                        pole_2 = pole_1 + m;
                    if(pocz_podzbioru(pole_1) != pocz_podzbioru(pole_2)){
                        polacz(pole_1, pole_2);
                        wynik_poz[i][j] = '.';
                    } else{
                        wynik[_]++;
                        wynik_poz[i][j] = 'Z';
                    }
                }
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m-1; ++j)
            cin >> pionowe[i][j];
    }
    for(int i=0; i<n-1; ++i){
        for(int j=0; j<m; ++j)
            cin >> poziome[i][j];
    }

    rozwiaz();

    cout << wynik[0] + wynik[1] << ' ' << wynik[1] << '\n';
    for(int i=0; i<n; ++i){
        for(int j=0; j<m-1; ++j)
            cout << wynik_pion[i][j];
        cout << '\n';
    }
    for(int i=0; i<n-1; ++i){
        for(int j=0; j<m; ++j)
            cout << wynik_poz[i][j];
        cout << '\n';
    }
}
