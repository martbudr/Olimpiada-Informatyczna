/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace w Toruniu
    martbudr5@gmail.com
*/
#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e3;
int n;
char grid[N_MAX][N_MAX];
int dist[N_MAX][N_MAX];
bool czy_odw[N_MAX][N_MAX];
pair<int,int> pocz, kon;

int zm_x[4] = {1, -1, 0, 0},
    zm_y[4] = {0, 0, 1, -1}; // zmiany

bool czy_pole(int x, int y)
{
    return (0 <= x) && (x < n) && (0 <= y) && (y < n);
}

void dfs(int x, int y)
{
    czy_odw[x][y] = true;
    for(int i=0; i<4; ++i){
        int nx = x + zm_x[i], ny = y + zm_y[i];
        if(czy_pole(nx, ny) && (grid[nx][ny] == '.' || grid[nx][ny] == 'K') && !czy_odw[nx][ny]){
            dist[nx][ny] = min(dist[nx][ny], dist[x][y] + 1);
            dfs(nx, ny);

        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin >> grid[i][j];
            if(grid[i][j] == 'P')
                pocz = {i, j};
            else if(grid[i][j] == 'K')
                kon = {i, j};

            dist[i][j] = INT_MAX;
        }
    }

    dist[pocz.first][pocz.second] = 0;
    dfs(pocz.first, pocz.second);

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            cout << dist[i][j] << ' ';
        cout << '\n';
    }

    int wynik = dist[kon.first][kon.second];
    if(wynik != INT_MAX)
        cout << wynik << '\n';
    else cout << "NIE" << '\n';
}
