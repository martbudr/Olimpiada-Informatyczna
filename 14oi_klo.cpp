#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6;
int n;
int wart_wej[N_MAX], wart[N_MAX], indeksy[N_MAX], ind_min_wart[N_MAX]; // wart[i] - a[i] z zadania, ind_min_wart - indeks minus wartosc
int poprzednicy[N_MAX]; // indeks poprzedniego klocka zostawianego dla kazdego z klockow

void quick_sort(int lewy, int prawy)
{
    if (lewy == prawy) return;

    int i = lewy, j = prawy;//i, j - "iteratory"
    int pivot = ind_min_wart[(lewy + prawy) / 2];
    do {//do while po to, aby o raz mniej sprawdzac warunek (na poczatku jest niepotrzebny)
        while ((ind_min_wart[i] < pivot) || (ind_min_wart[i] == pivot && wart[i] < wart[(lewy + prawy)/2])) ++i;
        while ((pivot < ind_min_wart[j]) || (ind_min_wart[j] == pivot && wart[(lewy + prawy)/2] < wart[j])) --j;

        if (i <= j) {//przypadek skrajny - pivot - tez swapowac, aby po tym zwiekszyc i i zmniejszyc j, i zakonczyc
            swap(ind_min_wart[i], ind_min_wart[j]);
            swap(indeksy[i], indeksy[j]);
            swap(wart[i], wart[j]);
            ++i; --j;//potrzebne, bo inaczej nie zawsze przerywa
        }
        else break;
    }while (i <= j);

    if(lewy < j)//instrukcja warunkowa sprawdzana dlatego, bo w niektorych przypadkach pivot jest jedna z 2 najmniejszych wartosci
        quick_sort(lewy, j);
    if(i < prawy)//to samo tylko ze jedna z 2 najwiekszych
        quick_sort(i, prawy);
}

class IntervalTree {
    static const int rozm = (1 << 21), LISC = (1 << 20); // rozmiar, miejsce pierwszego liscia

    void aktualizuj(pair<int,int>& curr, pair<int,int> wart) { // curr - current, wart - nowy kandydat
        if(wart.first > curr.first){
            curr = wart;
        }
    }

public:
     pair<int,int> drzewo[rozm]; // wartosc i z jakiego indeksu pochodzi

    void wstaw(pair<int,int> wart, int miej) {
        miej += LISC;
        while(miej){
            aktualizuj(drzewo[miej], wart);
            miej /= 2;
        }
    }

    pair<int,int> nax(int l, int p) {
        l += LISC;
        p += LISC;

        pair<int,int> ans = drzewo[l];
        if(l != p) aktualizuj(ans, drzewo[p]);

        while(l/2 != p/2){
            if(l%2 == 0) aktualizuj(ans, drzewo[l+1]);
            if(p%2 == 1) aktualizuj(ans, drzewo[p-1]);
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

    cin >> n;
    for(int i=0; i<n; ++i){
        cin >> wart_wej[i];
        wart[i] = wart_wej[i];
        indeksy[i] = i;
        ind_min_wart[i] = i - wart[i];
    }

    quick_sort(0, n-1);
    for(int i=0; i<n; ++i){
        cout << ind_min_wart[i] << ' ' << wart[i] << '\n';
    }

    for(int i=0; i<n; ++i){ // dla posortowanego arrayu
        if(ind_min_wart[i] >= 0){
            pair<int,int> poprz = drzewo.nax(1, wart[i]-1),
                do_wst;
            if(poprz.first >= 1){
                do_wst = make_pair(poprz.first+1, indeksy[i]);
                poprzednicy[i] = poprz.second;
            } else{
                do_wst = make_pair(1, indeksy[i]);
                poprzednicy[i] = 0;
            }

            cout << do_wst.first << ' ' << do_wst.second << ' ' << wart[i] << '\n';
            drzewo.wstaw(do_wst, wart[i]);
        }
    }

    // wypisywanie odpowiedzi
    ///for(int i=(1 << 20); i<((1 << 20) + 100); ++i){ /// do usuniecia
    ///    cout << drzewo.drzewo[i].first << ' ';
    ///}

    int wierz = drzewo.nax(1, N_MAX).second;
    while(){

    }


    cout << n - drzewo.nax(0, N_MAX).first << '\n';


}
