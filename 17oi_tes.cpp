#include <iostream>
#include <vector>

using namespace std;

bool czyJestZKolejna(int wczyt, int& ost_index, int m, vector<vector<int>>& pocz_ciag) // czy podciag dalej jest podciagiem biorac jeszcze kolejna liczbe (np. w podciagu 1 5 5 8 6 biorac 8, kiedy wczesniejsze sa podciagiem)
{
    if(pocz_ciag[wczyt].size() == 0) return false; // jesli pierwotny nie ma elementu o okreslonej wartosci to zwroc falsz

    int lewy=0, prawy=pocz_ciag[wczyt].size()-1, mid;
    while(lewy < prawy){// wyszukiwanie binarne pierwszego elementu o danej wartosci o indexie wiekszym od ostatniego do tej pory
        mid = (lewy+prawy)/2;
        if(pocz_ciag[wczyt][mid] > ost_index)
            prawy = mid;
        else lewy = mid+1;
    }
    if(pocz_ciag[wczyt][lewy] > ost_index){// jesli taki element jest, to zmienic ostatni index i zwrocic prawde
        ost_index = pocz_ciag[wczyt][lewy];
        return true;
    }
    return false; // w przeciwnym przypadku zwrocic falsz
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    const int ZAKRES = 1e6+1;

    int m; // dlugosc poczatkowego
    cin >> m;

    vector<vector<int>> pocz_ciag(ZAKRES);// pozycje wystepowania kazdej liczby
    int wczyt;
    for(int i=0; i<m; ++i){
        cin >> wczyt;
        pocz_ciag[wczyt].push_back(i);
    }

    int n; // ile tych sprawdzanych
    cin >> n;
    for(int i=0; i<n; ++i){
        int nowe_m; // dlugosc sprawdzanego
        cin >> nowe_m;

        if(nowe_m > m){ // jesli sprawdzany ciag jest dluzszy od poczatkowego
            cout << "NIE\n";
            break;
        }

        int ost_index = -1; // najmniejszy index, do ktorego da sie wypelnic ciag
        bool jest_podciagiem = true;
        for(int j=0; j<nowe_m; ++j){ // wczytywanie nastepnych liczb i sprawdzanie, czy zgadza sie
            cin >> wczyt; // kolejna liczba w sprawdzanym ciagu

            if(jest_podciagiem && !czyJestZKolejna(wczyt, ost_index, m, pocz_ciag)){// jesli z kolejna nie spelnia, ale wczesniej spelnialo
                    //(jesli teraz nie spelnia, ale wczesniej tez nie spelnialo, to po prostu jest pominiete)
                jest_podciagiem = false;
            }
        }
        if(jest_podciagiem) cout << "TAK\n";
        else cout << "NIE\n";
    }
}
