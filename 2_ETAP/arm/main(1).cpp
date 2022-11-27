/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace w Toruniu
    martbudr5@gmail.com
*/
#include <bits/stdc++.h>

using namespace std;

const long long N_MAX = 1e6 + 1;
long long n;
int a, b;
long long dp[N_MAX];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> a >> b;
    dp[0] = dp[1] = 0;
    dp[3] = a;
    for(long long i=2; i<=2*n; ++i){
        if(i%2 == 1)
            dp[i%n] = dp[(i-2)%n] + 2*b;
        else{
            dp[i%n] = dp[(i-1)%n] + b;
            if(dp[(i/2)%n] + a + b > dp[i%n])
                dp[i%n] = dp[(i/2)%n] + a + b;
        }
    }

    cout << *min_element(dp, dp + n-1) << '\n';
}
