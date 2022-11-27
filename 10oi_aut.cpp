#include <bits/stdc++.h>

using namespace std;

const int NK_MAX = 2e4;
int n, k;
bool czy_poludnie[NK_MAX]; // 1-N, 0-S
struct Autostrady
{
    int pocz, kon;
};
Autostrady kraw[NK_MAX];
int prawy_kon[NK_MAX], lewy_kon[NK_MAX]; // prawy_kon - najbardziej na prawo polozony z zaczynajacych sie w danym miejscu
bool czy_odw[NK_MAX]; // czy dana krawedz zostala rozwazona

class IntervalTree {
    int rozm, LISC = 1; // rozmiar, miejsce pierwszego liscia
    vector<int> drzewo;

    void szuk_rozm() {
        while(n > LISC) LISC <<= 1;
        rozm = LISC<<1;

        drzewo.reserve(rozm+1);
    }

public:
    void wstaw(int wart, int miej) {
        miej += LISC;
        while(miej){
            drzewo[miej] += wart;
            miej /= 2;
        }
    }

    int suma(int l, int p) {
        l += LISC;
        p += LISC;

        int ans = drzewo[l];
        if(l != p) ans += drzewo[p];

        while(l/2 != p/2){
            if(l%2 == 0) ans += drzewo[l+1];
            if(p%2 == 1) ans += drzewo[p-1];
            l /= 2;
            p /= 2;
        }
        return ans;
    }
};

IntervalTree drzewo;


int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for(int i=0; i<n; ++i) lewy_kon[i] = INT_MAX;
    for(int i=0; i<n; ++i){
        cin >> kraw[i].pocz >> kraw[i].kon;
        prawy_kon[kraw[i].pocz] = max(koniecPrawy[kraw[i].pocz], kraw[i].kon);
        lewy_kon[kraw[i].kon] = min(koniecLewy[kraw[i].kon], kraw[i].pocz);
    }

    for(int i=0; i<k; ++i){

    }
}
