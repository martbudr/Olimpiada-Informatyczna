#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n;
string napis;
vector<int> pref_suf(N_MAX, -1), pref_min(N_MAX); // indeksowane od 1; najpierw maksymalne, potem minimalne

void kmp()
{
    for(int i=0, j=-1; i<n; ++i){
        while(j>=0 && napis[i] != napis[j]) j = pref_suf[j];
        pref_suf[i+1] = ++j;
    }
}

long long suma_okresow() // w celu spojrzenia do napisu : i-1, do pref_suf : i
{
    long long wynik = 0;
    for(int i=2; i<=n; ++i){ // rozwazanie kolejnych prefikso-sufiksow i szukanie dla nich tych okresow
        // poprzez szukanie najkrotszego prefikso-sufiksu obecnego slowa i zwracanie i-(najkrotszy prefikso-sufiks tego slowa)
        if(pref_suf[i] == 0 || pref_min[pref_suf[i]] == 0) // jesli najdluzszy prefiks lub prefiks dla najdluzszego prefiksu nie istnieje
            pref_min[i] = pref_suf[i]; // ustaw prefiks dla i jako min prefiks dla i
        else // jesli istnieja
            pref_min[i] = pref_min[pref_suf[i]]; // ustaw min prefiks dla max prefiksu dla i jako min prefiks dla i

        wynik += (pref_min[i] != 0 ? (i - pref_min[i]) : 0);
    }
    return wynik;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> napis;
    kmp();
    cout << suma_okresow() << '\n';
}
