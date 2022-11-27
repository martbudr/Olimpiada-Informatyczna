#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int max_waga, n; // n - ilosc uczestnikow
    cin >> max_waga >> n;

    vector<int> wagi_uczest(n);
    for(auto &i : wagi_uczest)
        cin >> i;
    sort(wagi_uczest.begin(), wagi_uczest.end());

    int pocz = 0, kon = n-1, wynik = 0;
    while(pocz <= kon){
        if(wagi_uczest[pocz] + wagi_uczest[kon] <= max_waga) // jesli najlzejszy i najciezszy zmieszcza sie razem to wsadzic ich razem (w przeciwnym wypadku tylko najciezszego)
            pocz++;

        kon--; // wez ostatniego
        wynik++;
    }
    cout << wynik << '\n';


}
