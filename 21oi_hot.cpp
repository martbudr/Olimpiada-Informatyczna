#include <iostream>
#include <vector>

using namespace std;

long long wzor(int ilosc_sasiadow)
{
    return (ilosc_sasiadow * (ilosc_sasiadow - 1) * (ilosc_sasiadow - 2))/6;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> ilosc_sasiadow(n);
    int a, b;
    for(int i=0; i < n-1; ++i){ // wczytywanie krawedzi
        cin >> a >> b;
        ilosc_sasiadow[a-1]++;
        ilosc_sasiadow[b-1]++;
    }

    long long ilosc_rozw = 0;
    for(int i=0; i<n; ++i){ // dla kazdego wierzcholka ktory ma co najmniej 3 sasiadow obliczyc ze wzoru ilosc rozwiazan z tymi sasiadami i dodac ja do ilosci wszystkich rozwiazan
        if(ilosc_sasiadow[i] >= 3)
            ilosc_rozw += wzor(ilosc_sasiadow[i]);
    }
    cout << ilosc_rozw << '\n';
}
