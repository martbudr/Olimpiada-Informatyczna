#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    string napis;
    cin >> n >> napis;

    vector<int> poziomy(n+1), // poziomy[0] = 0 (punkt startowy przed jakakolwiek operacja)
        pomarancze; // indeksy wystepowania pomaranczy (dokladniej: za ktorymi indeksami poziom sie zwieksza)
    int min_poziom = 0, max_poziom = 0;
    for(int i=0; i<n; ++i){ // liczenie poziomow i minimalnego poziomu
        if(napis[i] == 'p'){
            poziomy[i+1] = poziomy[i] + 1;
            max_poziom = max(max_poziom, poziomy[i+1]);
            pomarancze.push_back(i);
        }
        else{
            poziomy[i+1] = poziomy[i] - 1;
            min_poziom = min(min_poziom, poziomy[i+1]);
        }
    }

    for(int i=0; i<n+1; ++i) // dodawanie minimalnego poziomu do kazdego poziomu, aby nie miec minusowych poziomow
        poziomy[i] -= min_poziom;
    max_poziom -= min_poziom;

    vector<int> ost_na_poz(max_poziom+1), // ostatni na danym poziomie
        ind_najw(n+1), poz_najw(n+1); // indeks najwyzszego dla danego przedzialu, poziom na ktorym ten najwyzszy sie znajduje
    for(int i=n; i>=0; --i){ // licz najwyzsze dla danych punktow
        if(i == n || napis[i] == 'j' || (ost_na_poz[poziomy[i]] == 0 && poziomy[i] > poziomy[i+1])){ // jesli koncowy element, jablko lub nieodwiedzony i wyzszy od poprzednich wczesniej poziom
            ind_najw[i] = i;
            poz_najw[i] = poziomy[i];
        }
        else{
            if(poz_najw[ost_na_poz[poziomy[i]]] >= poz_najw[i+1]){ // jesli poziom dla nastepnego na danym poziomie jest wiekszy od tego dla po prawej
                ind_najw[i] = ind_najw[ost_na_poz[poziomy[i]]];
                poz_najw[i] = poz_najw[ost_na_poz[poziomy[i]]];
            }
            else{ // w przeciwnym przypadku
                ind_najw[i] = ind_najw[i+1];
                poz_najw[i] = poz_najw[i+1];
            }
        }

        ost_na_poz[poziomy[i]] = i; // aktualizacja ostatniego na poziomie
    }

    int najdl_przedzial = 0;
    for(int i=0, x=pomarancze.size(); i<x; ++i){ // wsrod znalezionych przedzialow znajdz najdluzszy
        int akt_indeks = pomarancze[i];
        najdl_przedzial = max(najdl_przedzial, ind_najw[akt_indeks] - akt_indeks);
    }

    cout << najdl_przedzial << '\n';
}
