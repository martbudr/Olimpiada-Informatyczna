#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1;
int n;
vector<int> pocz(N_MAX), kon(N_MAX), czas(N_MAX), numery(N_MAX), brane; // kon - przed ktorym musi sie skonczyc,
//czas - czas montowania danego filmu, brane - pozycje w posortowanych tablicach kolejnych branych filmow do montowania

void sortuj(int lewy, int prawy)
{
    if (lewy == prawy) return;

    int i = lewy, j = prawy;//i, j - "iteratory"
    int pivot = kon[(lewy + prawy) / 2];
    do {//do while po to, aby o raz mniej sprawdzac warunek (na poczatku jest niepotrzebny)
        while (kon[i] < pivot) ++i;
        while (pivot < kon[j]) --j;

        if (i <= j) {//przypadek skrajny - pivot - tez swapowac, aby po tym zwiekszyc i i zmniejszyc j, i zakonczyc
            swap(kon[i], kon[j]);
            swap(czas[i], czas[j]);
            swap(numery[i], numery[j]);
            ++i; --j;//potrzebne, bo inaczej nie zawsze przerywa
        }
        else break;
    }while (i <= j);

    if(lewy < j)//instrukcja warunkowa sprawdzana dlatego, bo w niektorych przypadkach pivot jest jedna z 2 najmniejszych wartosci
        sortuj(lewy, j);
    if(i < prawy)//to samo tylko ze jedna z 2 najwiekszych
        sortuj(i, prawy);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=1; i<=n; ++i){
        cin >> czas[i] >> kon[i];
        kon[i]++;
        numery[i] = i;
    }
    sortuj(1, n);
    brane.push_back(0);
    pocz[0] = kon[0] = 1; // inicjowanie pierwszego
    int akt_kon = 0; // indeks aktualnie ostatniego elementu w ciagu branych

    for(int i=1; i<=n; ++i){
        if(czas[i] <= kon[i] - kon[brane[akt_kon]]){ // jesli miesci sie w pozostalym dostepnym czasie
            pocz[i] = kon[brane[akt_kon]];
            kon[i] = pocz[i] + czas[i];
            brane.push_back(i); // numer aktualnie rozwazanego filmu
            akt_kon++;
        }
        else if(kon[i]-czas[i] >= pocz[brane[akt_kon]] && kon[i]-czas[i] < kon[brane[akt_kon]]  &&  czas[i] < czas[brane[akt_kon]]){ // jesli zaczyna sie w trakcie montowania poprzedniego i jest krotsze od poprzedniego
            pocz[i] = pocz[brane[akt_kon]];
            kon[i] = pocz[i] + czas[i];
            brane[akt_kon] = i; // na koniec dopiero zmienianie w wektorze ktora wartosc powinna byc w wyniku
        }
    }

    // wypisywanie wyniku
    cout << akt_kon << '\n'; // ilosc mozliwych do zmontowania (o 1 mniej niz w vectorze - bo vector zawiera tez 0 na poczatku)
    for(int i=1; i<=akt_kon; ++i)
        cout << numery[brane[i]] << ' ' << pocz[brane[i]] << '\n'; // numery
}
