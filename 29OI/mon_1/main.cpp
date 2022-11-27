#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1;
int n;
vector<int> kon(N_MAX), czas(N_MAX), numery(N_MAX); // kon - przed ktorym musi sie skonczyc, czas - czas montowania danego filmu
vector<pair<int,int>> brane = {make_pair(INT_MAX, INT_MAX)};
vector<bool> czy_brane(N_MAX); /// PO NUMERACH NORMALNYCH, NIE W POSORTOWANEJ
int il_wzietych = 0, calk_czas = 0;

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

int wysz_bin(int wart) // indeks najmniejszego wiekszego od danego
{
    int lewy = 0, prawy = il_wzietych;
    while(lewy < prawy){
        int mid = (lewy + prawy) / 2;
        if(brane[mid].first <= wart)
            lewy = mid+1;
        else prawy = mid;
    }
    return lewy;
}

int wysz_bin_2(int wart) // wyszukiwanie indeksu najmniejszej wartosci, ktora moznaby usunac zeby wstawic nowa
{
    int lewy = 0, prawy = brane.size()-2; // brane.size()-2 - bo bez ostatniego (nieskonczonosci)
    while(lewy < prawy){
        int mid = (lewy + prawy) / 2;
        if(brane[mid].first < wart)
            lewy = mid+1;
        else prawy = mid;
    }

    return lewy;
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

    // szukanie, ktore wziac
    for(int i=1; i<=n; ++i){
        if(kon[i] - czas[i] - 1 >= calk_czas){ // jesli miesci sie na koncu
            brane.insert(brane.begin() + wysz_bin(czas[i]), make_pair(czas[i], i));
            czy_brane[i] = true;
            calk_czas += czas[i];
            il_wzietych++;
        }
        else if(brane.size() >= 2 && czas[i] < brane[brane.size()-2].first){ // jesli mozna wstawic zakladajac niewybranie wczesniej aktualnie najdluzszego
            int do_usuniecia = wysz_bin_2(czas[i]);
            calk_czas = calk_czas - czas[brane[do_usuniecia].second] + czas[i];

            czy_brane[brane[do_usuniecia].second] = false;
            czy_brane[i] = true;

            brane.erase(brane.begin() + do_usuniecia);
            brane.insert(brane.begin() + wysz_bin(czas[i]), make_pair(czas[i], i));
        }
    }

    // wypisywanie
    cout << il_wzietych << '\n';
    int moment_rozp = 1; // moment rozpoczecia kazdego z kolejnie branych przedzialow
    for(int i=1; i<=n; ++i){
        if(czy_brane[i]){ // jesli jest brany
            cout << numery[i] << ' ' << moment_rozp << '\n';
            moment_rozp += czas[i];
        }
    }
}
