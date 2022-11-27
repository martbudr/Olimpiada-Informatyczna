#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// stopnie sa przekopiowane i przez to zmiany nie wplywaja na glowna funkcje
vector<int> sortTopologiczne(int n, vector<int> stopnie, vector<vector<int>>& nastepcy)
{
    vector<int> wynik;
    queue<int> Q; // kolejka zawierajaca przetwarzane wierzcholki
    vector<bool> czy_odwiedzony(n+1, false);
    for(int i=1; i<=n; ++i){
        if(stopnie[i] == 0){ // jesli wierzcholka nie poprzedzaja zadne wierzcholki
            Q.push(i);
            czy_odwiedzony[i] = true;
            wynik.push_back(i);
        }
    }

    while(!Q.empty()){ // dopoki sa jakies wierzcholki do przetwarzania
        int obecny = Q.front();
        Q.pop();

        for(int i=0, x=nastepcy[obecny].size(); i<x; ++i){
            stopnie[nastepcy[obecny][i]]--;
            if(stopnie[nastepcy[obecny][i]] == 0){
                Q.push(nastepcy[obecny][i]);
                wynik.push_back(nastepcy[obecny][i]);
            }
        }
    }

    if(wynik.size() < n) // jesli wynik nie zawiera wszystkich wierzcholkow
        return {-1};
    return wynik;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // ile czynnosci - wierzcholkow
    cin >> n;

    // numeracja czynnosci (wierzcholkow) od 1
    vector<int> czasy(n+1), stopnie(n+1);
    vector<vector<int>> poprzednicy(n+1), nastepcy(n+1);
    int wczyt_poprz; // jeden z poprzednikow danego wierzcholka
    for(int i=1; i<=n; ++i){
        cin >> czasy[i] >> stopnie[i];
        for(int j=0; j<stopnie[i]; ++j){
            cin >> wczyt_poprz;
            poprzednicy[i].push_back(wczyt_poprz);
            nastepcy[wczyt_poprz].push_back(i);
        }
    }

    vector<int> sort_topo = sortTopologiczne(n, stopnie, nastepcy);
    if(sort_topo[0] == -1)
        cout << "CYKL" << '\n';
    else{
        vector<int> max_do(n+1, 0), max_po(n+1, 0);
        int max_sciezka=0;

        for(int i=0; i<n; ++i){ // szukanie sciezek do (wlacznie z obecnym wierzcholkiem)
            int obecny = sort_topo[i]; // obecny wierzcholek
            for(int j=0; j<stopnie[obecny]; ++j){ // przechodzac po wszystkich poprzednikach obecnego
                max_do[obecny] = max(max_do[obecny], max_do[poprzednicy[obecny][j]]);
            }
            max_do[obecny] += czasy[obecny]; // doliczanie obecnego wierzcholka do sciezki do
            max_sciezka = max(max_sciezka, max_do[obecny]);
        }
        for(int i=n-1; i>=0; --i){ // szukanie sciezek po (bez obecnego wierzcholka)
            int obecny = sort_topo[i];
            for(int j=0, x=nastepcy[obecny].size(); j<x; ++j){ // przechodzac po wszystkich nastepcach obecnego
                max_po[obecny] = max(max_po[obecny], max_po[nastepcy[obecny][j]] + czasy[nastepcy[obecny][j]]);
            }
        }
        cout << max_sciezka << '\n';

        int k; // ilosc zapytan
        cin >> k;
        int wierz, o_ile; // wierz - czas w ktorym wierzcholku (jakiej czynnosci), o_ile - o ile zwiekszony
        for(int i=0; i<k; ++i){
            cin >> wierz >> o_ile;
            if(max_sciezka - (max_do[wierz] + max_po[wierz]) >= o_ile) // jesli zapas jest wiekszy lub rowny ilosci zwiekszanej
                cout << "NIE" << '\n';
            else cout << "TAK" << '\n';
        }
    }
}
