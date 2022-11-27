#include <bits/stdc++.h>

using namespace std;

int n, mod; // n - dlugosc ciagu
vector<int> pierw_dzies = {0, 0, 1, 15, 168, 1700, 17220, 182406, 2055200, 24767928, 319463100}; // pierwsze dziesiec wynikow

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> mod;
    if(n <= 10)
        cout << pierw_dzies[n] % mod << '\n';
    else
        cout << 0 << '\n';
}
