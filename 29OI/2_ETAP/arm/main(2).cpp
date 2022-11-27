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
long long tab[2*N_MAX];

void dp(long long x, int il_a, int il_b, long long pula)
{
    tab[x] = min(tab[x], il_a * 1LL * a + il_b *1LL * b);

    if(pula != x) dp(x, il_a+1, il_b, x);
    if(x+pula <= 2*n) dp(x+pula, il_a, il_b+1, pula);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> a >> b;
    for(int i=2; i<=2*n; ++i)
        tab[i] = LLONG_MAX - 1e6;
    dp(2, 1, 1, 1);

    cout << *min_element(tab + n + 1, tab + 2*n) << '\n';
}
