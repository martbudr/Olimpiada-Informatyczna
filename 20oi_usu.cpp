#include <bits/stdc++.h>

using namespace std;

void wypisz(int biale, stack<int>& wynik)
{
    while(!wynik.empty()){
        for(int i=0; i < biale+1; ++i){
            cout << wynik.top() << ' ';
            wynik.pop();
        }
        cout << '\n';
    }
}

void oblicz_rozw(int n, int biale, vector<int>& klocki)
{
    stack<int> stos, wynik;
    vector<int> sumy_stos = {0}; // sumy prefiksowe dla aktualnego stosu
    for(int i=0; i<n; ++i){
        stos.push(i+1);
        sumy_stos.push_back(sumy_stos.back() + klocki[i]);
        if(stos.size() >= biale+1 && sumy_stos.back() - sumy_stos[sumy_stos.size()-1 - biale - 1] == 0){ // jesli mozna usunac k+1 ostatnich ze stosu (czyli je wypisac)
            for(int j=0; j < biale+1; ++j){
                wynik.push(stos.top());
                stos.pop();
                sumy_stos.pop_back();
            }
        }
    }
    wypisz(biale, wynik);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, biale; // biale - ilosc bialych klockow w fragmencie usuwanym
    string wejscie;
    cin >> n >> biale >> wejscie;
    vector<int> klocki(n); // wartosc danego klocka do liczonej sumy
    for(int i=0; i<n; ++i)
        klocki[i] = (wejscie[i] == 'b') ? 1 : -biale;

    oblicz_rozw(n, biale, klocki);
}
