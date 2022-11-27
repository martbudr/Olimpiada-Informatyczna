#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 1;
int n, k;
vector<pair<int,int>> sas[N_MAX];
long long ans = 0;

bool ozn[N_MAX]; // czy dany oznaczony

void dfs(int u, int p = -1, long long dl = 0)
{
    if(ozn[u]) ans += 2*dl;
    for(auto v : sas[u]) if(v.first != p){
        dfs(v.first, u, dl+v.second);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    int a, b, w;
    for(int i=0; i<n-1; ++i){
        cin >> a >> b >> w;
        sas[a].push_back({b,w});
        sas[b].push_back({a,w});
    }

    ozn[1] = true;
    for(int i=0; i<k; ++i){
        cin >> a;
        ozn[a] = true;
        dfs(a);
        cout << ans << '\n';
    }
}
