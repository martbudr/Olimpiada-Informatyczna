#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e3 + 1;
int n;
vector<int> sas[N_MAX];
int ans = 0;
bool fin; // czy znaleziono koniec sciezki
bool vis[N_MAX];

void dfs(int u)
{
    if(u == n){
        ans++;
        fin = true;
        return;
    }
    vis[u] = true;
    for(auto v : sas[u]) if(!fin && !vis[v]){
        dfs(v);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int amt, x;
    for(int i=1; i<n; ++i){
        cin >> amt;
        for(int j=0; j<amt; ++j){
            cin >> x;
            sas[i].push_back(x);
        }
    }

    for(auto v : sas[1]){
        fin = false;
        if(!vis[v]) dfs(v);
    }

    cout << ans << '\n';
}
