#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e3;
int n, m;
int czer[N_MAX];
long long nie_jedn = 0;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        czer[a-1]++;
        czer[b-1]++;
    }

    for(int i=0; i<n; ++i){
        nie_jedn += czer[i] * (n-1 - czer[i]);
    }
    nie_jedn /= 2;

    cout << (n * 1LL * (n-1) * (n-2))/6  - nie_jedn << '\n';
}
