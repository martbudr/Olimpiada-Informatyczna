#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6;
int n;
long long m;
vector<int> gleb(N_MAX), gleb_przyg(N_MAX); // gleb_przyg - glebokosc po przygotowaniu terenu do
int koszt_pocz = 0, koszt_dzi = 0, wys_max = 0;
int miej, nach;

void przygotuj(int nach) // wyrownanie terenu tak, aby nie bylo zadnych zbocz wyzszych niz nach
{
    gleb_przyg = gleb;
    for(int i=0; i<n-1; ++i){
        if(gleb_przyg[i+1] > gleb_przyg[i] + nach)
            gleb_przyg[i+1] = gleb_przyg[i] + nach;
    }
    for(int i=n-1; i>=1; --i){
        if(gleb_przyg[i-1] > gleb_przyg[i] + nach)
            gleb_przyg[i-1] = gleb_przyg[i] + nach;
    }
}

bool czy_moz(int nach) // czy mozliwe jest zmieszczenie sie w ustalonej ilosci wykopanych jednostek przy danym nachyleniu
{
    przygotuj(nach);

    // szukanie miejsca do wykopania dolu
    /// jedyna rzecz, ktora zostala do uzupelnienia

    /// zwrocic, czy da sie wykopac dol przy danym nachyleniu
}

void wysz_bin() // wyszukanie minimalnego nachylenia
{
    // sprawdzenie dla zerowego nachylenia - czy mozna usunac wszystko
    for(int i=0; i<n; ++i){
        koszt_pocz += gleb[i];
        wys_max = max(wys_max, gleb[i]);
    }
    if(koszt_pocz <= m)
        return 0;

    koszt_pocz = 0;
    int lewy = 1, prawy = wys_max;
    while(lewy < prawy){
        int mid = (lewy + prawy + 1)/2;

        if(czy_moz(mid))
            lewy = mid;
        else prawy = mid-1;
    }
    nach = lewy;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i=0; i<n; ++i)
        cin >> gleb[i];

    wysz_bin();
    cout << miej << ' ' << nach << '\n';
}
