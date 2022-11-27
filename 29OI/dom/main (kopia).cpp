#include <bits/stdc++.h>

using namespace std;

long long m;
const int FIB = 88;
vector<long long> fib(FIB+1), wyniki;

void licz_fib() // licz liczby z ciagu fibonacciego
{
    fib[0] = fib[1] = 1;
    for(int i=2; i<=FIB; ++i)
        fib[i] = fib[i-1] + fib[i-2];
}

int wysz_bin(long long m, int gorna_gran)
{
    int lewy = 1, prawy = gorna_gran;
    while(lewy < prawy){
        int mid = (lewy + prawy + 1)/2;
        if(fib[mid] <= m)
            lewy = mid;
        else prawy = mid - 1;
    }
    return lewy;
}

void przejdz(long long m, long long wynik, long long z_ilu, int gorna_gran) // rekurencyjna funkcja szukajaca wszystkich rozwiazan
{
    if(m == 1){
        wyniki.push_back(wynik + (z_ilu-1));
        return;
    }

    int pier_fib = wysz_bin(m, gorna_gran); // ostatnia liczba Fibonacciego mniejsza rowna pozostalosci z wejsciowej liczby
    for(int i=pier_fib; i>1; --i){
        if(m % fib[i] == 0){
            przejdz(m/fib[i], wynik+i, z_ilu+1, pier_fib+1);
        }
    }
}

/*void sito_eratostenesa() // binarny algorytm do liczenia liczb pierwszych (zwykly nie dzialalby na takich liczbach, jakich potrzebuje)
{
    vector<char> tab(M_MAX/8 + 1);
    for(long long i=2; i*i<=M_MAX; i++) {
    	if(!(((int)tab[i>>3]>>(i&7))&1)){
            for(long long j=i*i; j<=M_MAX; j+=i)
                tab[j>>3] |= (1<<(j&7)); //ustawienie odpowiedniego bitu na 1
    	}
    }

    for(long long i=2; i<=M_MAX; i++){ // wrzucanie do tablicy pierwsze liczb pierwszych
        if(!(((long long)tab[i>>3]>>(i&7))&1))
      		pierwsze.push_back(i);
  	}
}

/// poki co vector czynniki zawiera wszystkie wystapienia danych czynnikow - nie wiem, czy aby na pewno tak powinno byc
void rozloz(long long liczba, vector<long long>& czynniki) // rozloz dana liczbe na czynniki pierwsze
{
    for(int i=1, x=sqrt(liczba); i<=liczba; ++i){
        if(n % i == 0){
            czynniki.push_back(i);
            if(n / i != i)
                czynniki.push_back(i);
        }
    }
}*/

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> m;
    if(m == 1)
        cout << 1 << '\n';
    else{
        przejdz(m, 0, 0, FIB);
        if(wyniki.empty())
            cout << 0 << '\n';
        else{
            // znajdz najmniejszy ze wszystkich w wyniki i go wypisz
            long long wynik_min = wyniki[0];
            for(int i=1, x=wyniki.size(); i<x; ++i)
                wynik_min = min(wynik_min, wyniki[i]);
            cout << wynik_min << '\n';
        }
    }
}
