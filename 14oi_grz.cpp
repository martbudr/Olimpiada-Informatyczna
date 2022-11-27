#include <bits/stdc++.h>

using namespace std;

const int M_ROZM = 1e3 + 1;
vector<int> kier_x = {-1, -1, -1, 0, 0, 1, 1, 1},
            kier_y = {-1, 0, 1, -1, 1, -1, 0, 1};

int n;
vector<vector<int>> tab(M_ROZM, vector<int>(M_ROZM));
vector<vector<bool>> czy_odw(M_ROZM, vector<bool>(M_ROZM));
int nin, nax;

int grzbiety = 0, doliny = 0;

bool pole(int x, int y) // czy jest polem
{
    return (1 <= x && x <= n && 1 <= y && y <= n);
}

bool ta_sama_wys(int nx, int ny, int akt_wart)
{
    if(tab[nx][ny] == akt_wart)
        return true;

    nin = min(nin, tab[nx][ny]);
    nax = max(nax, tab[nx][ny]);
    return false;
}

void bfs(int x, int y)
{
    int akt_wart = nin = nax = tab[x][y];

    queue<pair<int,int>> Q; // kolejka wierzcholkow do odwiedzenia
    Q.push({x, y});
    czy_odw[x][y] = true;

    while(!Q.empty()){
        x = Q.front().first,
        y = Q.front().second;
        Q.pop();

        for(int i=0; i<8; ++i){ // po wszystkich sasiadach
            int nx = x + kier_x[i],
                ny = y + kier_y[i];

            if(pole(nx, ny)){
                if (ta_sama_wys(nx, ny, akt_wart)){
                    if(!czy_odw[nx][ny]){
                        Q.push({nx, ny});
                        czy_odw[nx][ny] = true;
                    }
                }
            }
        }
    }

    if(nin == akt_wart) // jesli aktualna wysokosc jest lokalnym minimum (dolina)
        doliny++;
    if(nax == akt_wart) // jesli jest lokalnym maximum (grzbietem)
        grzbiety++;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j)
            cin >> tab[i][j];
    }

    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            if(!czy_odw[i][j])
                bfs(i, j);
        }
    }

    cout << grzbiety << ' ' << doliny << '\n';
}
