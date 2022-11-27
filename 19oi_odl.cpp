#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 1, LIC_MAX = 1e6 + 1;

bool pierw[LIC_MAX];

const int D_SIZE = 7;
int dziel[D_SIZE] = {2, 3, 5, 7, 11, 13, 17};

int n;
int wierz[N_MAX]; // wszystkie oznaczone wierzcholki (wlacznie z powtorzeniami)
vector<int> rozw; // rozwazane wierzcholki (ich indeksy)
int odl[LIC_MAX], z_jaki[LIC_MAX], // odl - odleglosc od najblizszego zaznaczonego wierzcholka,
        // z_jaki - jaki ten zaznaczony wierzcholek jest,
    odl_bez[LIC_MAX], z_jaki_bez[LIC_MAX]; // odl_bez, z_jaki_bez - to samo, tylko ze bez pewnego okreslonego wierzcholka (jednego z zaznaczonych)

int wynik[N_MAX];

void sito()
{
    for(int i=2; i <= LIC_MAX; ++i)
        pierw[i] = true;
    for(int i=2; i <= LIC_MAX; ++i){
        if(pierw[i]){
            for(int k = i*i; k <= LIC_MAX; k += i)
                pierw[k] = false;
        }
    }
}

void zmien(int nowy, int akt, queue<int>& Q) // zmienianie wartosci dla nowego bazujac na aktualnym
{
    if(odl[nowy] == INT_MAX){
        odl[nowy] = odl[akt] + 1;
        z_jaki[nowy] = z_jaki[akt];
        Q.push(nowy);
    }
    else if(odl[nowy] == odl[akt] && z_jaki[akt] < z_jaki[nowy]){
        z_jaki[nowy] = z_jaki[akt];
    }
}

void bfs(int bez_jakiego)
{
    queue<int> Q;
    for(unordered_set<int>::iterator it = lic.begin(); it != lic.end(); ++it){
        Q.push(*it);
        wierz[*it].odl = 0;
        wierz[*it].z_jaki = *it;
    }

    while(!Q.empty()){
        int akt = Q.front(); // aktualny wierzcholek w grafie
        Q.pop();

        if(pierw[akt]){ // jesli nie da sie dalej dzielic przez typowe przejscia
            zmien(1, akt, Q);
        }

        for(int i=0; i < D_SIZE; ++i){
            if(akt % dziel[i] != 0) continue;

            zmien(akt / dziel[i], akt, Q); // aktualizowanie nowego wierzcholka, o mniejszej wartosci
        }
    }
}


int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    sito();

    cin >> n;
    vector<int> kubelki[LIC_MAX];
    for(int i=1; i<=n; ++i){
        cin >> lic[i];
        kubelki[lic[i]].push_back(i);
    }

    // usuwanie powtorzen
    for(int i=1; i<LIC_MAX; ++i){
        if(kubelki[i].size() == 1){
            rozw.push_back(i);
            continue;
        }

        wynik[kubelki[i][0]] = kubelki[i][1]; // dla pierwszego drugi
        for(int j=1; j<(int)kubelki[i].size(); ++j){ // dla pozostalych pierwszy
            wynik[kubelki[i][j]] = kubelki[i][0];
        }
    }


}
