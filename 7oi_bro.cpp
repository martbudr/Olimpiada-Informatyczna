#include <iostream>
#include <vector>

using namespace std;

void przesun(int& prawy, int& lewy, int n, unsigned long long& lok_koszt, int& zap_po_lewej, int& zap_po_prawej,
             int& odl_po_lewej, int& odl_po_prawej,
             vector<int>& zapotrzebowania, vector<int>& odleglosci) // przesuwanie prawych i lewych granic dopoty, dopoki jest to korzystne
{
    while(odl_po_lewej > odl_po_prawej+odleglosci[prawy]){
        lok_koszt = lok_koszt + zapotrzebowania[lewy]*(odl_po_prawej + odleglosci[prawy]) - zapotrzebowania[lewy]*odl_po_lewej; // modyfikacja kosztu

        zap_po_prawej += zapotrzebowania[prawy];
        odl_po_prawej += odleglosci[prawy];
        zap_po_lewej -= zapotrzebowania[lewy];
        odl_po_lewej -= odleglosci[lewy];

        prawy = (prawy+1)%n;
        lewy = (lewy+1)%n;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // ilosc miast
    cin >> n;

    // numeracja miast od 0
    vector<int> zapotrzebowania(n), odleglosci(n); // zapotrzebowania - ile do ktorego miasta dostarczyc, odleglosci - odleglosci pomiedzy kolejnymi miastami
    for(int i=0; i<n; ++i){
        cin >> zapotrzebowania[i] >> odleglosci[i];
    }

    int lewy=1, prawy=0, zap_po_lewej=0, zap_po_prawej=0, odl_po_lewej=0, odl_po_prawej=0;
    unsigned long long koszt=0, lok_koszt;
    for(int i=n-1; i>=lewy; --i){ // liczenie poczatkowych wartosci
        zap_po_lewej += zapotrzebowania[i];
        odl_po_lewej += odleglosci[i];
        koszt += odl_po_lewej*zapotrzebowania[i];
    }
    przesun(prawy, lewy, n, koszt, zap_po_lewej, zap_po_prawej, odl_po_lewej, odl_po_prawej, zapotrzebowania, odleglosci);

    for(int i=1; i<n; ++i){ // rozwazanie kazdego miasta po zerowym jako pierwsze
        lok_koszt = koszt + (zap_po_lewej + zapotrzebowania[i-1])*odleglosci[i-1] - zap_po_prawej*odleglosci[i-1];

        zap_po_lewej += zapotrzebowania[i-1];
        zap_po_prawej -= zapotrzebowania[i];
        odl_po_lewej += odleglosci[i-1];
        odl_po_prawej -= odleglosci[i-1];

        przesun(prawy, lewy, n, lok_koszt, zap_po_lewej, zap_po_prawej, odl_po_lewej, odl_po_prawej, zapotrzebowania, odleglosci);

        if(lok_koszt < koszt) // jesli koszt w obecnym jest mniejszy od obecnie najmniejszego
            koszt = lok_koszt;
    }
    cout << koszt << '\n';
}
