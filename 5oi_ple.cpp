#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e3+1, T_MAX = 21+1, A_MAX = 79+1, NAX = 1e9;
int n, T, A; // ile butli, potrzebny tlen, potrzebny azot
struct but{
    int t, a, w; // tlen, azot, waga
}B[N_MAX];
int dp[T_MAX][A_MAX];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> T >> A >> n;
    for(int i=1; i<=n; ++i){
        cin >> B[i].t >> B[i].a >> B[i].w;
    }

    for(int j=0; j<=T; ++j){
        for(int k=0; k<=A; ++k)
            dp[j][k] = NAX;
    }
    dp[0][0] = 0;
    for(int i=1; i<=n; ++i){
        for(int j=T; j>=0; --j){
            for(int k=A; k>=0; --k){
                int jj = min(T, j + B[i].t),
                    kk = min(A, k + B[i].a);
                dp[jj][kk] = min(dp[jj][kk], dp[j][k] + B[i].w);
            }
        }
    }

    cout << dp[T][A] << '\n';
}
