#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 250001;
int n;
vector<int> wys(N_MAX);
stack<int> q;
int wynik = 0;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int szer;
    q.push(-1); // wartownik
    for(int i=0; i<n; ++i){
        cin >> szer >> wys[i];
        while(q.top() > wys[i]) // dopoki poprzedni budynek jest wyzszy
            q.pop(); // usun go z rozwazanych

        if(q.top() < wys[i]) // jesli pierwszy niewiekszy od nowego jest mniejszy
            wynik++; // potrzebny kolejny plakat

        q.push(wys[i]); // wstaw ten nowy do rozwazanych
    }
    cout << wynik << '\n';
}
