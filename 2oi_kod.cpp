#include <iostream>
#include <vector>

using namespace std;

void wypisz(vector<int>& ciag) // wypisywanie wyjscia
{
    for(auto i : ciag)
        cout << i << '\n';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // dlugosc ciagu
    cin >> n;
    vector<int> zakodowany(n), ciag(n); // zakodowany - ciag B, ciag - ciag A
    for(int i=0; i<n; ++i){
        cin >> zakodowany[i];
        if(zakodowany[i] > i){
            cout << "NIE\n";
            return false;
        }
    }

    vector<int> pozostale; // pozostale wartosci jeszcze niewykorzystane w ciagu
    for(int i=n; i>=1; --i)
        pozostale.push_back(i);

    for(int i=n-1; i>=0; --i){ // ustalanie wartosci ciagu
        ciag[i] = pozostale[zakodowany[i]];
        pozostale.erase(pozostale.begin() + zakodowany[i]);
    }

    wypisz(ciag);
}
