#include <bits/stdc++.h>

using namespace std;

const int L_MAX = 250;
int n, r;
int wejscie[3*L_MAX + 1][3*L_MAX + 1],
    s_prefix[3*L_MAX + 1][3*L_MAX + 1];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> r;
    for(int i=1+L_MAX; i<=n + L_MAX; ++i){
        for(int j=1+L_MAX; j<=n + L_MAX; ++j)
            cin >> wejscie[i][j];
    }

    for(int i=1+L_MAX; i<=n + 2*L_MAX; ++i){
        for(int j=1+L_MAX; j<=n + 2*L_MAX; ++j)
            s_prefix[i][j] = s_prefix[i][j-1] + s_prefix[i-1][j] - s_prefix[i-1][j-1] + wejscie[i][j];
    }

    for(int i=1+L_MAX; i<=n + L_MAX; ++i){
        for(int j=1+L_MAX; j<=n + L_MAX; ++j)
            cout << s_prefix[i+r][j+r] - s_prefix[i+r][j-r-1] - s_prefix[i-r-1][j+r] + s_prefix[i-r-1][j-r-1] << ' ';
        cout << '\n';
    }
}
