/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace w Toruniu
    martbudr5@gmail.com
*/
#include <bits/stdc++.h>

using namespace std;

const long long N_MAX = 1e5 + 1;
long long n;
int a, b;
long long dp[2*N_MAX];

int main(void) // podzadanie 2 i 3
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> a >> b;
    for(int i=2; i<=2*n; ++i)
        dp[i] = LLONG_MAX;
    for(int k=1; k<=n; ++k){
        for(int i=2; i*k<=2*n; ++i)
            dp[i*k] = min(dp[i*k], dp[k] + a + (i-1)*b);
    }

    cout << *min_element(dp + n + 1, dp + 2*n) << '\n';
}
