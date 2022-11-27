#include <bits/stdc++.h>

using namespace std;

const int ALF = 26; // wielkosc alfabetu
int n;
string A, B;
vector<int> wyst_w_b[ALF];

int p = 21,
    LISC = 1 << (p-1); // przesuniecie dla lisci
vector<int> przes(1 << p);

int suma_przedz(int lewy, int prawy)
{
    lewy += LISC;
    prawy += LISC;

    int wynik_lok = przes[lewy];
    if(lewy != prawy)
        wynik_lok += przes[prawy];

    while(lewy/2 != prawy/2){
        if(lewy%2 == 0)
            wynik_lok += przes[lewy + 1];
        if(prawy%2 == 1)
            wynik_lok += przes[prawy - 1];

        lewy /= 2;
        prawy /= 2;
    }
    return wynik_lok;
}

void wstaw(int pos)
{
    pos += LISC;
    while(pos){
        przes[pos]++;
        pos /= 2;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> A >> B;
    for(int i=n-1; i>=0; --i){
        wyst_w_b[B[i] - 'A'].push_back(i);
    }

    long long wynik = 0;
    for(int i=0; i<n; ++i){
        int pos = wyst_w_b[A[i] - 'A'].back();
        wyst_w_b[A[i] - 'A'].pop_back();

        wynik += pos - i + suma_przedz(pos+1, n+1);

        wstaw(pos);
    }

    cout << wynik << '\n';
}
