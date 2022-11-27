#include <iostream>
#include <vector>
#include <set>

using namespace std;

void zmianaCyfry(int pozycja, vector<int>& suma, vector<int>& dlugWewn, vector<int>& dlugZewn, set<int>& indeksyNie9)
{
    int poprz_suma = suma[pozycja];
    suma[pozycja] = dlugWewn[pozycja] + dlugZewn[pozycja];//aktualizacja sumy

    if (suma[pozycja] == 9 && poprz_suma != 9)//aktualizacja setu jesli obecna suma jest dziewiatka a poprzednia nie byla
        indeksyNie9.erase(indeksyNie9.find(pozycja));
    else if (suma[pozycja] != 9 && poprz_suma == 9)//jesli suma nie jest dziewiatka a poprzednia byla
        indeksyNie9.insert(pozycja);
}

bool czyPrzeniesienie(int n,int pozycja, vector<int>& suma, set<int>& indeksyNie9)
{
    if(pozycja + 1 > n-1) return false;//jesli nie ma juz nic dalej

    if (suma[pozycja + 1] >= 10)//suma na poprzedniej pozycji (mniej znaczacej)
        return true;
    else if (suma[pozycja + 1] == 9) {
        if (indeksyNie9.upper_bound(pozycja) != indeksyNie9.end())//jesli istnieje suma po dziewiatkach
            if (suma[*indeksyNie9.upper_bound(pozycja)] >= 10)//jesli pierwsza suma po dziewiatkach jest wieksza rowna 10
                return true;
    }
    return false;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const int ascii = 48;
    int n, t, i;//n-1 - dlugosc wyswietlacza

    cin >> n >> t;
    vector<int> dlugWewn(n), dlugZewn(n), suma(n);
    dlugWewn[0] = dlugZewn[0] = 0;//po to, aby pozniej latwiej bylo sume dla tego indeksu liczyc

    char wczyt;
    for (i = 1; i < n; ++i) {//wczytywanie dlugu wewnetrznego
        cin >> wczyt;
        dlugWewn[i] = (int)wczyt - ascii;
    }
    for (i = 1; i < n; ++i) {//wczytywanie dlugu zewnetrznego
        cin >> wczyt;
        dlugZewn[i] = (int)wczyt - ascii;
    }

    set<int> indeksyNie9;
    for (i = 0; i < n; ++i) {//obliczanie sumy i dodawanie nie-dziewiatek do setu
        suma[i] = dlugWewn[i] + dlugZewn[i];
        if (suma[i] != 9)
            indeksyNie9.insert(i);
    }

    char litera;
    int pozycja, nowa;
    while (t--) {
        cin >> litera >> pozycja;
        pozycja = n - pozycja;//n-pozycja, bo wczytywana numeracja zaczyna sie od 1 i idzie w odwrotnym kierunku
        switch (litera) {
        case 'W':
            cin >> nowa;
            dlugWewn[pozycja] = nowa;//aktualizacja cyfry

            zmianaCyfry(pozycja, suma, dlugWewn, dlugZewn, indeksyNie9);

            break;
        case 'Z':
            cin >> nowa;
            dlugZewn[pozycja] = nowa;

            zmianaCyfry(pozycja, suma, dlugWewn, dlugZewn, indeksyNie9);

            break;
        case 'S':
            bool przeniesienie = czyPrzeniesienie(n, pozycja, suma, indeksyNie9);
            cout << (suma[pozycja] + przeniesienie) % 10 << '\n';
            break;
        }
    }
}
