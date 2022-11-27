#include <bits/stdc++.h>

using namespace std;

const int L_MAX = 3e5;
int n, m;
vector<int> os_max(L_MAX); // maksymalna osiagalna wielkosc krazka - prefiksy

int wysz_bin(int krazek)
{
    int lewy = 0, prawy = n-1;
    while(lewy < prawy){
        int mid = (lewy + prawy + 1) / 2;
        if(os_max[mid] >= krazek)
            lewy = mid;
        else prawy = mid - 1;
    }
    if(lewy <= prawy && os_max[lewy] >= krazek)
        return lewy;
    else return -1;
}

void znajdz_odp()
{
    int krazek;
    for(int i=0; i<m; ++i){
        cin >> krazek;
        int gdzie = wysz_bin(krazek); // miejsce zatrzymania sie aktualnego krazka
        if(gdzie == -1){
            n = -1;
            return;
        }
        else
            n = gdzie;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i=0; i<n; ++i)
        cin >> os_max[i];

    for(int i=1; i<n; ++i) // liczenie prefiksow
        os_max[i] = min(os_max[i-1], os_max[i]);

    znajdz_odp();

    cout << n + 1 << '\n';
}
