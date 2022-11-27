#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 2e3 + 1;
int n;
bool dzialka[N_MAX][N_MAX];
vector<vector<int>> pion(N_MAX, vector<int>(N_MAX)); // jak daleko siegaja klocki w pionie (dane miejsce jest ktorym z rzedu)
stack<pair<int,int>> S; // {wartosc, pozycja}

int najw_pole(vector<int>& wiersz)
{
    vector<int> lewe(n+1), prawe(n+1);
    S.push({-1, 0}); // poczatkowy
    for(int i=1; i<=n; ++i){
        while(S.top().first >= wiersz[i]) S.pop();
        lewe[i] = S.top().second;
        S.push({wiersz[i], i});
    }
    while(S.size() > 1) S.pop(); // oproznianie dla odwrotnego przejscia
    for(int i=n; i>=1; --i){
        while(S.top().first >= wiersz[i]) S.pop();
        prawe[i] = S.top().second;
        S.push({wiersz[i], i});
    }

    int lok_wynik = 0;
    for(int i=1; i<=n; ++i)
        lok_wynik = max(lok_wynik, wiersz[i] * (prawe[i] - lewe[i] - 1));
    return lok_wynik;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            cin >> dzialka[i][j];
            pion[i][j] = (dzialka[i][j] == 1) ? 0 : pion[i-1][j] + 1; // liczenie pionow
        }
    }

    int wynik = 0;
    for(int i=1; i<=n; ++i)
        wynik = max(wynik, najw_pole(pion[i]));
    cout << wynik << '\n';
}
