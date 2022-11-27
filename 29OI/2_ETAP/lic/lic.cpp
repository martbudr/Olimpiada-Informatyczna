/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace w Toruniu
    martbudr5@gmail.com
*/
#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
long long n, k;
int c;
vector<int> pierwsze; // pierwsze niedzielace n
int V[N_MAX]; // czy juz byla rozwazona
set<int> wzgl_pierwsze;

void sito()
{
    for(long long i=2; i <= n; i++){
        if(V[i] == 0){
            if(n % i != 0)
                pierwsze.push_back(i);
            for(int k=i*i; k <= n; k += i)
                if(V[k] == 0)
                    V[k] = i;
        }
    }
}

void generuj(int akt = 1)
{
    for(int i=0; i<(int)pierwsze.size(); ++i){
        int lok_akt = akt;
        while(lok_akt * pierwsze[i] <= n){
            int nowa = lok_akt * pierwsze[i];

            if(wzgl_pierwsze.find(nowa) == wzgl_pierwsze.end())
                wzgl_pierwsze.insert(nowa);

            generuj(nowa);

            lok_akt *= pierwsze[i];
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k >> c;
    sito();
    wzgl_pierwsze.insert(1);
    generuj();

    set<int>::iterator it = wzgl_pierwsze.begin();
    for(int i=0; i<k-1; ++i)
        it++;

    for(int i=0; i<c; ++i){
        cout << *it << ' ';
        it++;
    }
}
