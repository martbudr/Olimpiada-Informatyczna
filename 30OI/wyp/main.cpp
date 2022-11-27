/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace
    87-100 Torun
*/
#include <bits/stdc++.h>

#define LL long long
#define ppair pair<pair<LL,LL>, int>

using namespace std;

const int N_MAX = 1e5 + 1;
const LL X_MAX = 1e15;
int n, pol[N_MAX], dlu[N_MAX], lic[N_MAX], mia[N_MAX]; // polozenie, dlugosc, licznik i mianownik predkosci
int wynik = 1; // co najmniej raz, poniewaz bedziemy wyprzedzac co najmniej 1 auto

int zlacz[N_MAX]; // z jakim zlaczone
int ost = 1; // ostatnie do tej pory rozwazane auto

LL NWD(LL a, LL b)
{
    if(a < b) swap(a, b);
    LL c;
    while(b != 0){
        c = a; a = b; b = c%b;
    }
    return a;
}

bool frs_faster(int i, int j) // wczesniejszy szybszy niz pozniejszy
{
    return (mia[j] * 1LL * lic[i] > mia[i] * 1LL * lic[j]);
}

pair<LL,LL> calc_mom(int i, int j) // tylko jesli pierwszy jest szybszy od drugiego (jesli ich predkosci sa rowne to to nie zadziala)
{
    if(i == n) return make_pair(X_MAX,1);

    LL Lic = mia[i] * 1LL * mia[j] * (pol[j] - dlu[j] - pol[i]),
        Mia = mia[j] * 1LL * lic[i] - mia[i] * 1LL * lic[j],
        Nwd = NWD(Lic, Mia);

    return make_pair(Lic/Nwd, Mia/Nwd);
}

pair<LL,LL> calc_pier_mom(int i) // liczenie momentu wyprzedzenia i-tego przez pierwszy
{
    LL Lic = mia[i] * 1LL * mia[0] * (dlu[0] + pol[i]),
        Mia = lic[0] * 1LL * mia[i] - mia[0] * 1LL * lic[i],
        Nwd = NWD(Lic, Mia);

    return make_pair(Lic/Nwd, Mia/Nwd);
}

struct comp{ // compare for Q
    public:
    bool operator()(ppair& a, ppair& b){
      return a.first.first * 1LL * b.first.second >= a.first.second * 1LL * b.first.first;
   }
};

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> dlu[0] >> lic[0] >> mia[0];
    for(int i=1; i<=n; ++i){
        cin >> pol[i] >> dlu[i] >> lic[i] >> mia[i];
        int nwd = NWD(lic[i], mia[i]);
        lic[i] /= nwd;
        mia[i] /= nwd;
        zlacz[i] = i; // zawiera siebie - niezlaczone z zadnym
    }

    priority_queue<ppair, vector<ppair>, comp> Q;
    for(int i=1; i<=n-1; ++i){
        if(frs_faster(i, i+1)){
            Q.push(make_pair(calc_mom(i, i+1), i));
        }
    }
    Q.push(make_pair(make_pair(X_MAX,1), n));

    while(!Q.empty()){
        ppair curr = Q.top();
        Q.pop();

        if(zlacz[curr.second] <= curr.second && ost <= curr.second){ // jesli dany nie zostal jeszcze zlaczony z nastepnym
                // oraz jesli nie jest wczesniej od miejsca, w ktore juz dojechal Bajtazar
            // dopoki ostatni rozwazany nie jest wiekszy od n oraz dla tego ostatniego da sie dotrzec do jego konca przed czasem
            // nastepnego zderzenia

            while(true){
                if(ost == n) break;
                while(!(zlacz[ost] <= ost && zlacz[zlacz[ost]] == ost)){
                    if(zlacz[ost] > ost && zlacz[ost] != INT_MAX) ost = zlacz[ost];
                    else ost++;
                }
                pair<LL,LL> ost_mom = calc_pier_mom(ost);
                if(ost == n || ost_mom.first * 1LL * curr.first.second > ost_mom.second * 1LL * curr.first.first) break; // jesli jest juz zlaczony lub Bajtazar nie zdazy wyprzedzic kolejnego

                pair<LL,LL> miej_ost, miej_next;// miejsce dla pierwszego i kolejnego
                miej_ost = make_pair(pol[ost] * 1LL * ost_mom.second + ost_mom.first / mia[ost] * 1LL * lic[ost],
                                     ost_mom.second);
                miej_next = make_pair(ost_mom.second * 1LL * mia[zlacz[ost+1]] * (pol[zlacz[ost+1]] - dlu[zlacz[ost+1]]) + ost_mom.first * 1LL * lic[zlacz[ost+1]],
                                      ost_mom.second * 1LL * mia[zlacz[ost+1]]);

                if(miej_next.first * 1LL * miej_ost.second / ost_mom.second >=
                   miej_next.second / ost_mom.second * 1LL * (dlu[0] * 1LL * miej_ost.second + miej_ost.first)) wynik++;

                ost++;
            }

            // laczenie
            // curr.second - ten, dla ktorego sie laczy
            // zlacz[curr.second+1] - ostatni z dalszego auta (bo przechowywany w poczatku)
            if(curr.second != n){
                dlu[zlacz[curr.second+1]] += dlu[curr.second]; // aktualizowanie dlugosci

                int a = zlacz[curr.second]; // zmienna pomocnicza, bo mozliwe ze w trakcie pierwszego obliczenia zmienimy te wartosc
                zlacz[zlacz[curr.second]] = zlacz[curr.second+1]; // aktualizowanie wartosci w poczatku
                zlacz[zlacz[curr.second+1]] = a; // aktualizowanie wartosci w koncu
                if(zlacz[zlacz[curr.second]] != curr.second)
                    zlacz[curr.second] = INT_MAX;
            }

            // recalculate moment zderzenia dla i-1go (bo nastapi to wczesniej)
            if(curr.second > 1 && zlacz[curr.second] != INT_MAX && frs_faster(curr.second-1, zlacz[curr.second]))
                Q.push(make_pair(calc_mom(curr.second-1, zlacz[curr.second]), curr.second-1));
        }
    }
    cout << wynik << '\n';
}
