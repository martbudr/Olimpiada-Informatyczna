#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 602, K_MAX = 51;
int n, k;
vector<vector<int>> suf(N_MAX, vector<int>(N_MAX)),
    dp(K_MAX, vector<int>(N_MAX)),
    poprz(K_MAX, vector<int>(N_MAX)); // poprzedni brany przy dp
int wart_max = 0, dla_ktorego; // maksymalna ilosc biletow i pierwszy brany przy najwiekszym wyniku

void licz_suf() // liczenie sufiksow
{
    for(int i=1; i<=n-1; ++i)
        for(int j=n-1; j>=i; --j)
            suf[i][j] += suf[i-1][j] + suf[i][j+1] - suf[i-1][j+1];
}

void szuk() // liczenie dp
{
    dla_ktorego = n-1;
    for(int i=1; i<=n-1; ++i)
        dp[1][i] = suf[i][i];
    for(int _k=2; _k <= k; ++_k){
        for(int i=n-_k; i>=1; --i){
            for(int j=i+1; j<=n-_k+1; ++j){ // mozliwi kandydaci na bezposrednio poprzedniego
                if(dp[_k][i] < dp[_k-1][j] + suf[i][i] - suf[i][j]){
                    dp[_k][i] = dp[_k-1][j] + suf[i][i] - suf[i][j];
                    poprz[_k][i] = j;
                    if(dp[_k][i] > wart_max || dla_ktorego > n-_k){
                        wart_max = dp[_k][i];
                        dla_ktorego = i;
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

    cin >> n >> k;
    for(int i=1; i<=n-1; ++i){ // pion (kolumny)
        for(int j=i; j<=n-1; ++j) // poziom (wiersze)
            cin >> suf[i][j];
    }
    licz_suf();
    szuk();

    // wypisywanie (kolejnych poprzednich)
    int _k=k;
    while(_k != 0){
        cout << dla_ktorego << ' ';
        dla_ktorego = poprz[_k][dla_ktorego];
        _k--;
    }
    cout << '\n';
}
