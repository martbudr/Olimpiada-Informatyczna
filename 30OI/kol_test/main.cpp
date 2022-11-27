#include <bits/stdc++.h>

using namespace std;

const int M_MAX = 2e3 + 1, Q_MAX = 1e6 + 1;
int m, il_przek, q; // m - rozmiar planszy, il_przek - ilosc przekasek, q - ilosc zapytan

vector<vector<int>> tab(M_MAX, vector<int>(M_MAX, -1)), // tab - wstepna tablica zawierajaca przekaski
            pos(M_MAX, vector<int>(M_MAX, -1)); // pos - dane miejsce ktorym jest z kolei
int nr_miej = 0; // najwiekszy numer miejsca

int waz[Q_MAX];
int dl_waz = 0;

int akt_x = 0, akt_y = 0;

// do testowania
bool corr = true;

int query(int x, int y)
{
    if(pos[x][y] == -1 || (nr_miej - pos[x][y] >= dl_waz)) return -1;

    return (waz[pos[x][y] - (nr_miej - dl_waz) - 1]);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // oficjalne
    ifstream wej("C:\\Users\\marti\\Downloads\\ocen-win\\ocen-win\\in\\kol0.in");
    ifstream wyj("C:\\Users\\marti\\Downloads\\ocen-win\\ocen-win\\out\\kol0.out");

    // do tego pojedynczego z forum
    //ifstream wej("C:\\Users\\marti\\Downloads\\kol.in");
    //ifstream wyj("C:\\Users\\marti\\Downloads\\kol.out");

    // duze testy z forum
    //ifstream wej("C:\\Users\\marti\\Downloads\\kol_testy_100\\in\\kol99.in");
    //ifstream wyj("C:\\Users\\marti\\Downloads\\kol_testy_100\\out\\kol99.out");

    // wczytanie danych
    wej >> m >> il_przek >> q;

    int x, y, kol;
    for(int i=0; i<il_przek; ++i){
        wej >> x >> y >> kol;
        tab[x-1][y-1] = kol;
    }

    // inicjalizacja glowy
    waz[0] = 0;
    dl_waz = 1;
    pos[0][0] = 0;


    // obsluga zapytan
    char zap;
    while(q--){
        wej >> zap;
        if(zap == 'Z'){ // jesli zapytanie
            wej >> x >> y;
            x--; y--;

            int comp;
            wyj >> comp;

            // do testowania
            corr = (query(x, y) == comp);
            if(!corr){
                cout << "NO" << '\n';
                return 0;
            }
        } else{ // jesli przemieszczenie
            // przemieszczenie
            if(zap == 'G') akt_x--;
            else if(zap == 'D') akt_x++;
            else if(zap == 'L') akt_y--;
            else if(zap == 'P') akt_y++;

            // aktualizacja pozycji weza
            pos[akt_x][akt_y] = ++nr_miej;

            if(tab[akt_x][akt_y] != -1){ // jesli przekaska
                waz[dl_waz++] = tab[akt_x][akt_y]; // zwieksz weza
                tab[akt_x][akt_y] = -1; // usun przekaske z miejsca (zostala juz zabrana)
            }
        }
    }

    cout << "YES" << '\n'; // if it wasn't it would've been printed out earlier
}
