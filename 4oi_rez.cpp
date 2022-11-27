#include <bits/stdc++.h>

using namespace std;

void szybkie_sort(int lewy, int prawy, vector<pair<int,int>>& przedzialy)
    // sortowanie przedzialow po koncach
{
    if(lewy == prawy) return;

    int i=lewy, j=prawy,
        pivot = przedzialy[(lewy+prawy)/2].second;
    do{
        while(przedzialy[i].second < pivot) ++i;
        while(przedzialy[j].second > pivot) --j;

        if(i<=j){
            swap(przedzialy[i], przedzialy[j]);
            ++i; --j;
        }
        else break;
    }while(i<=j);

    if(lewy < j)
        szybkie_sort(lewy, j, przedzialy);
    if(prawy > i)
        szybkie_sort(i, prawy, przedzialy);
}

int wysz_bin(int lewy, int prawy, int max_wartosc, vector<pair<int,int>>& przedzialy)
    // szukanie ostatniego konca przed poczatkiem nastepnego przedzialu (poczatek to max_wartosc)
{
    while(lewy < prawy){
        int mid = (lewy + prawy + 1)/2;
        if(przedzialy[mid].second <= max_wartosc)
            lewy = mid;
        else prawy = mid-1;
    }
    return lewy;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int,int>> przedzialy(n+1); // poczatki i konce rezerwacji sal
    przedzialy[0].first = przedzialy[0].second = 0; // ulatwiacz na pozniej
    for(int i=1; i<n+1; ++i){
        cin >> przedzialy[i].first >> przedzialy[i].second;
    }
    szybkie_sort(0, n, przedzialy);

    vector<int> czasy_do(n+1); // maksymalny czas rezerwacji do danego przedzialu wlacznie
    czasy_do[0] = 0;
    for(int i=1; i<n+1; ++i){
        // wynik bez danego przedzialu i z nim
        int wynik_bez = czasy_do[i-1],
            wynik_z = czasy_do[wysz_bin(0, i-1, przedzialy[i].first, przedzialy)] + przedzialy[i].second - przedzialy[i].first;

        czasy_do[i] = max(wynik_bez, wynik_z); // max czas jako maksimum z dwoch wynikow
    }

    cout << czasy_do[n] << '\n'; // wynik koncowy
}
