#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 1;
int n, k;
vector<pair<int,int>> sas[N_MAX];
bool ozn[N_MAX];

int il_pod[N_MAX], dl_pod[N_MAX];

void cnt_pod(int u, int p = -1)
{
    il_pod[u] = (ozn[u] ? 1 : 0); dl_pod[u] = 0;
    for(auto v : sas[u]) if(v.first != p){
        cnt_pod(v.first, u);
        il_pod[u] += il_pod[v.first];
        dl_pod[u] += v.second * il_pod[v.first] + dl_pod[v.first];
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
        sas[a].push_back({b, w});
        sas[b].push_back({a, w});
    }

    for(int i=1; i<=k; ++i){
        cin >> a; // wierzcholek oznaczany
        ozn[a] = true;
    }
}
