#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 3e6;
int n, poz_t, // poz_t - poziom tolerancji
    wynik = 0;
deque<pair<int,int>> rosn, mal; // rosnaca i malejaca kolejka - para {wartosc, indeks}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> poz_t >> n;
    int j=0, pomiar; // j - poczatek przedzialu
    for(int i=0; i<n; ++i){ // po koncach przedzialow
        cin >> pomiar;

        // wstawianie w odpowiednie miejsca
        while(rosn.size() > 0 && rosn.front().first > pomiar) // front - najmniejsze, back - najwieksze
            rosn.pop_front();
        rosn.push_front({pomiar, i});
        while(mal.size() > 0 && mal.front().first < pomiar) // front - najwieksze, back - najmniejsze
            mal.pop_front();
        mal.push_front({pomiar, i});

        while(mal.back().first - rosn.back().first > poz_t){ // usuwanie tych, ktore juz na pewno nie beda potrzebne w kolejce (bo nie beda uzyte - bo sa za duze lub za male; jak za duze to
                // usuwane z malejacej, a jak za male, to z rosnacej, bo na koncu jednej z tych kolejek sie znajduja)
            if(rosn.back().second == j)
                rosn.pop_back();
            else if(mal.back().second == j)
                mal.pop_back();
            j++;
        }

        wynik = max(wynik, i-j+1);
    }

    cout << wynik << '\n';
}
