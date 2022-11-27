#include <iostream>
#include <string>

using namespace std;

int policz_pierwsza_sume(string wejscie) {
    int suma = 0, pomoc;
    for (int i = 0, n = wejscie.size(); i < n; ++i) {// obliczanie sumy cyfr liczby z wejscia
        pomoc = wejscie[i] - '0';
        suma += pomoc * pomoc;
    }
    return suma;
}

void wypisz_ciag(string wejscie) {// obliczanie sum po kolei zaczynajac od pierwszej ktora jest troche inna od pozostalych (korzysta z innych danych wejsciowych)
    cout << wejscie << ' ';// wypisywanie pierwszego elementu
    if (wejscie == "1" || wejscie == "4") {// kiedy wejscie jest przypadkiem koncowym
        cout << '\n';
        return;
    }

    int suma = policz_pierwsza_sume(wejscie);

    cout << suma << ' ';
    while (suma != 1 && suma != 4) {// dopoki suma powinna sie zmieniac
        int suma_sumy = 0;
        while (suma != 0) {
            int pomoc = suma % 10;
            suma_sumy += pomoc * pomoc;
            suma /= 10;
        }
        suma = suma_sumy;

        cout << suma << ' ';
    }
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;// ilosc przypadkow testowych
    cin >> t;
    while (t--) {
        string wejscie;
        cin >> wejscie;

        wypisz_ciag(wejscie);
    }
}
