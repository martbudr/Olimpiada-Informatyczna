#include <bits/stdc++.h>

using namespace std;

string tekst;

vector<int> kmp(string wyraz) // zwraca tablice prefikso-sufiksow slowa wyraz
{
    int n = wyraz.size();
    vector<int> pref_suf(n+1, -1);
    for(int i=0, j=-1; i<n; ++i){
        while(j >= 0 && wyraz[i] != wyraz[j])
            j = pref_suf[j];
        pref_suf[i+1] = ++j;
    }

    return vector<int>(pref_suf.begin()+1, pref_suf.end());
}

bool czy_szablon(int dlugosc)
{
    vector<int> pref_suf = kmp(tekst.substr(0, dlugosc) + '#' + tekst);
    int ind_min = pref_suf.size() - dlugosc; // minimalny indeks, do ktorego moze zejsc iterator (i ktorego nie moze przekroczyc)
    for(int i = pref_suf.size() - 2; i > dlugosc; --i){
        if(pref_suf[i] == dlugosc)
            ind_min = i - dlugosc + 1;
        if(ind_min > i)
            return false;
    }
    return true;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> tekst;
    vector<int> pref_suf = kmp(tekst);

    vector<int> kand; // kandydaci na szablon
    for(int i=tekst.size(); i>0; i = pref_suf[i-1])
        kand.push_back(i);

    for(int i=kand.size()-1; i>=0; --i){
        if(i < kand.size()-1 && kand[i] <= 2*kand[i+1]) // warunek bezsensownosci sprawdzania (bo poprzedni pokrywa w calosci obecny - wiec jesli poprzedni nie jest, to ten tez nie) (kand[i]/2 <= kand[i+1])
            continue;
        if(czy_szablon(kand[i])){
            cout << kand[i] << '\n';
            return 0;
        }
    }
}
