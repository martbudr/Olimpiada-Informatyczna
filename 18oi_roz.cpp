#include <bits/stdc++.h>

using namespace std;

const int LITERY = 26;

vector<int> scal(int a, int b, vector<vector<int>>& wyst) // a, b - dla jakich liter
{
    vector<int> rozw;

    int i1 = 0, i2 = 0, n = wyst[a].size() - 1, m = wyst[b].size() - 1;
    while(i1 != n || i2 != m){
        if(wyst[a][i1] <= wyst[b][i2]){
            rozw.push_back(1);
            i1++;
        } else{
            rozw.push_back(-1);
            i2++;
        }
    }

    return rozw;
}

int policz_rozw(int n, vector<vector<int>>& wyst)
{
    int wynik = 0;
    for(int i=0; i<LITERY; ++i){
        for(int j=0; j<LITERY; ++j){
            if(wyst[i].size() == 1 || wyst[j].size() == 1) // jesli nie ma zadnych wystapien litery (w vectorze jest tylko wartownik)
                continue;

            vector<int> ciag_rozw = scal(i, j, wyst); // rozwazany ciag
            int wynik_lok = 0, suma = 0, suma_poprz = 0,
                mini = INT_MAX;
            for(int k=0, x=ciag_rozw.size(); k < x; ++k){
                suma += ciag_rozw[k];
                if(ciag_rozw[k] == -1){
                    mini = min(mini, suma_poprz);
                    suma_poprz = suma;
                }
                wynik_lok = max(wynik_lok, suma - mini);
            }

            wynik = max(wynik, wynik_lok);
        }
    }

    return wynik;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    string wejscie;
    cin >> n >> wejscie;

    vector<vector<int>> wyst(LITERY); // wystapienia poszczegolnych liter
    for(int i=0; i<n; ++i)
        wyst[wejscie[i] - 'a'].push_back(i);
    for(int i=0; i<LITERY; ++i) // dodawanie wartownikow
        wyst[i].push_back(INT_MAX);

    cout << policz_rozw(n, wyst) << '\n';
}
