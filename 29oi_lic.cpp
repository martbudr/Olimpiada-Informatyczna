#include <bits/stdc++.h>

using namespace std;

const long long Z_MAX = 8e14;
long long n, k, c;
vector<long long> rozkl;
int ile_rozkl;

void rozlaz() // rozlazenie liczby n na czynniki pierwsze
{
    long long _n = n;
    for(int i=2; i<=1e7; ++i){
        if(_n%i == 0){
            rozkl.push_back(i);
            while(_n%i == 0) _n /= i;
            if(_n == 1) break;
        }
    }
    if(_n != 1) rozkl.push_back(_n);

    ile_rozkl = (int)rozkl.size();
}

long long przed(long long z)
{
    long long wy = 0;
    for(int i=1; i<=(1<<ile_rozkl); ++i){
        long long dziel = 1;
        int amt = 0;

        for(int j=0; j<ile_rozkl; ++j){
            if(i & (1<<j)){
                dziel *= rozkl[j];
                amt++;
            }
        }

        if(amt&1) wy -= z/dziel;
        else wy += z/dziel;
    }
    return wy;
}

long long pier; // pierwsza liczba do wypisania
void wysz_bin()
{
    long long l = 1, r = Z_MAX;
    while(l < r){
        long long mi = (l + r) / 2;
        if(przed(mi) < k) l = mi+1;
        else r = mi;
    }
    pier = l;
}

bool wzgl(long long a, long long b) // czy wzglednie pierwsze
{
    if(b > a) swap(a, b);
    long long c;
    while(b != 0){
        c = b;
        b = a%b;
        a = c;
    }
    return (a == 1);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k >> c;
    rozlaz();

    wysz_bin();

    cout << pier << ' ';
    int kt = 1;
    for(long long i = pier+1; kt < c; ++i){
        if(wzgl(n, i)){
            cout << i << ' ';
            kt++;
        }
    }
    cout << '\n';
}
