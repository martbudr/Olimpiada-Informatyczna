#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // n - ilosc wierzcholkow (znajomych), m - ilosc znajacych sie par
    cin >> n >> m;

    vector<vector<bool>> czy_sasiedzi(n+1, vector<bool>(n+1, false)); // zapisywane w wartosciach odpowiadajacych, a nie o 1 mniejszych
    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        czy_sasiedzi[a][b] = true;
        czy_sasiedzi[b][a] = true;
    }

    int do_usuniecia = 2*n/3;
    vector<bool> czy_nie_usuniety(n, true); // true - nie usuniety, false - usuniety
    for(int i=1; i<=n && do_usuniecia>0; ++i){
        if(czy_nie_usuniety[i] == false) // jesli usuniety to pomin
            continue;

        for(int j=i+1; j<=n; ++j){
            if(czy_nie_usuniety[j] == false) // jesli usuniety to pomin
                continue;

            if(czy_sasiedzi[i][j] == false){ // jesli nie sa sasiadami to je usun
                czy_nie_usuniety[i] = false;
                czy_nie_usuniety[j] = false;
                do_usuniecia -= 2; // zmiejsz ilosc do usuniecia
                break;
            }
        }
    }

    int do_wypisania = n/3;
    for(int i=1; i<=n && do_wypisania>0; ++i){
        if(czy_nie_usuniety[i] == true){ // jesli nie usuniety i jeszcze trzeba cokolwiek wypisywac to wypisz
            cout << i << ' ';
            do_wypisania--;
        }
    }
    cout << '\n';
}
