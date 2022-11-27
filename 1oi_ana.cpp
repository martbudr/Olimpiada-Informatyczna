#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int LITERY=26, ASCII=97;

bool czyAnagramZKonkretnym(int nr_grupy, vector<int>& litery_wyraz, vector<vector<int>>& ile_liter_w_grupie)
{
    for(int i=1; i<=LITERY; ++i){
        if(litery_wyraz[i] != ile_liter_w_grupie[nr_grupy][i])
            return false;
    }
    return true;
}

bool czyWystapil(string wyraz, int nr_grupy, vector<vector<string>>& wyrazy_w_grupach)
{
    for(int i=0, x=wyrazy_w_grupach[nr_grupy].size(); i<x; ++i){
        if(wyraz == wyrazy_w_grupach[nr_grupy][i])
            return true;
    }
    return false;
}

bool czyAnagram(string wyraz, vector<int>& litery_wyraz, vector<vector<int>>& ile_liter_w_grupie, vector<vector<string>>& wyrazy_w_grupach)
{
    for(int j=0, x=ile_liter_w_grupie.size(); j<x; ++j){
        if(litery_wyraz[0] == ile_liter_w_grupie[j][0]){
            if(czyAnagramZKonkretnym(j, litery_wyraz, ile_liter_w_grupie)){
                if(!czyWystapil(wyraz, j, wyrazy_w_grupach))
                   wyrazy_w_grupach[j].push_back(wyraz);
                return true;
            }
        }
    }
    return false;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    vector<string> wyrazy(n); // wektor (pozniej posortowany) zawierajacy wszystkie wyrazy
    int ile_grup_obecnie = 0;
    vector<vector<string>> wyrazy_w_grupach(n); // wektor zawierajacy wyrazy pogrupowane na grupy
    vector<vector<int>> ile_liter_w_grupie(n, vector<int>(LITERY+1, 0)); // wektor zawierajacy ilosc kazdej litery w grupie

    for(int i=0; i<n; ++i)
        cin >> wyrazy[i];// wczytaj wszystkie wyrazy

    // posortuj wektor z wyrazami
    sort(wyrazy.begin(), wyrazy.end());

    for(int i=0; i<n; ++i){// dla kazdego wyrazu wykonaj ponizsze czynnosci
        vector<int> litery_wyraz(LITERY+1, 0);

        litery_wyraz[0] = wyrazy[i].size();
        for(int j=0; j<litery_wyraz[0]; ++j){ // zlicz wszystkie litery i zapisz w wektorze (a - indeks 1, bo pod 0 jest liczba liter)
            litery_wyraz[wyrazy[i][j] - ASCII + 1]++;// +1, bo numeracja od 1
        }

        // przejdz przez wszystkie grupy anagramow, jesli jest jakas o tej samej liczbie liter to sprawdz, czy wszystkich liter ma tyle samo
        // co obecny wyraz; jesli nie to przerwij, jesli tak to dodaj ten wyraz do grupy
        if(!czyAnagram(wyrazy[i], litery_wyraz, ile_liter_w_grupie, wyrazy_w_grupach)){// przy okazji sprawdzania wywolywana jest tez ta funkcja i ewentualnie dodawane do wektorow
            wyrazy_w_grupach[ile_grup_obecnie].push_back(wyrazy[i]);
            ile_liter_w_grupie[ile_grup_obecnie] = litery_wyraz;
            ile_grup_obecnie++;
        }
    }

    //wypisywanie ostatecznych grup
    for(int i=0; i<ile_grup_obecnie; ++i){
        for(int j=0, x=wyrazy_w_grupach[i].size(); j<x; ++j){
            cout << wyrazy_w_grupach[i][j] << ' ';
        }
        cout << '\n';
    }
}
