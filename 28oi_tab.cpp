#include <iostream>
#include <vector>

using namespace std;

void zmien(int x, int y, int& ile_ostatnich, vector<vector<short>>& czy_ostatnie)
{
    if(czy_ostatnie[x][y])
        ile_ostatnich -= 1;
    else ile_ostatnich += 1;

    czy_ostatnie[x][y] ^= 1; // zmiana wartosci w tablicy
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q; // n - wymiar pionowy, m - wymiar poziomy, q - ile zmian
    cin >> n >> m >> q;

    // numeracja od 1
    vector<vector<short>> czy_ostatnie(n+1, vector<short>(m+1)); // czy dane pole jest ostatnie z danego koloru
    int ile_ostatnich = 0; // i jednoczesnie ile zmian
    int x1, y1, x2, y2; // wspolrzedne
    for(int i=0; i<q; ++i){
        cin >> x1 >> y1 >> x2 >> y2;
        zmien(x2, y2, ile_ostatnich, czy_ostatnie);
        if(x1 != 1)
            zmien(x1-1, y2, ile_ostatnich, czy_ostatnie);
        if(y1 != 1)
            zmien(x2, y1-1, ile_ostatnich, czy_ostatnie);
        if(x1 != 1 && y1 != 1)
            zmien(x1-1, y1-1, ile_ostatnich, czy_ostatnie);

        cout << ile_ostatnich << '\n';
    }
}
