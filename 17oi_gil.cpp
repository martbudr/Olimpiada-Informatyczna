#include <iostream>
#include <vector>

using namespace std;

struct wierz {
    bool odw = false;
    vector<int> sasiedzi;
};

void wczytaj(int m, vector<wierz>& Wierz) {
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        Wierz[a - 1].sasiedzi.push_back(b - 1);
        Wierz[b - 1].sasiedzi.push_back(a - 1);
    }
}

bool pojedynczy_wierz(int start, vector<wierz>& Wierz) {// jesli istnieje pojedynczy wierzcholek w grafie to nie da sie rozmiescic filii
    if (Wierz[start].sasiedzi.size() == 0)
        return true;
    return false;
}

void dfs(int start, vector<wierz>& Wierz, vector<int>& gildie) {
    vector<int> Q;
    Q.push_back(start);
    gildie[start] = 0;
    Wierz[start].odw = true;

    while (!Q.empty()) {
        int obecny = Q.back();
        Q.pop_back();
        for (int i = 0, x = Wierz[obecny].sasiedzi.size(); i < x; ++i) {
            if (!Wierz[Wierz[obecny].sasiedzi[i]].odw) {
                Q.push_back(Wierz[obecny].sasiedzi[i]);
                gildie[Wierz[obecny].sasiedzi[i]] = !gildie[obecny];
                Wierz[Wierz[obecny].sasiedzi[i]].odw = true;
            }
        }
    }
}

bool przejdz_caly(int n, int m, vector<wierz>& Wierz, vector<int>& gildie) {
    for (int i = 0; i < n; ++i) {
        if (Wierz[i].odw == false) {
            if (pojedynczy_wierz(i, Wierz) == false)
                dfs(i, Wierz, gildie);
            else return false;
        }    
    }
    return true;
}

void wypisz(int n, int m, vector<wierz>& Wierz, vector<int>& gildie) {
    if (przejdz_caly(n, m, Wierz, gildie) == false) {
        cout << "NIE\n";
        return;
    }     

    cout << "TAK\n";
    for (int i = 0; i < n; ++i) {
        if (gildie[i] == 0)
            cout << 'K' << '\n';
        else cout << 'S' << '\n';
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<wierz> Wierz(n);
    vector<int> gildie(n, -1);

    wczytaj(m, Wierz);
    wypisz(n, m, Wierz, gildie);
}