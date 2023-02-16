#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 1;
int n, k;
vector<pair<int,int>> sas[N_MAX];
int oj[N_MAX];
long long ans = 0;
bool powr[N_MAX]; // czy dana krawedz (od syna do ojca) jest powracajaca
long long pod[N_MAX], nad[N_MAX];
int pod_dla[N_MAX];
priority_queue<pair<long long,int>> Q; // pary {zysk, dla ktorego}

void dfs(int u=1, int p=-1)
{
    oj[u] = p;
    for(auto v : sas[u]) if(v.first != p){
        nad[v.first] = nad[u] + v.second;
        dfs(v.first, u);

        ans += 2*v.second;
        if(pod[v.first] + v.second > pod[u]){
            pod[u] = pod[v.first] + v.second;
            pod_dla[u] = v.first;
        }
    }
}

void dod_max(int x)
{
    // dodajemy w dol
    // bo z gory przyszlismy

    while(true){
        powr[x] = true;
        if(sas[x].size() == 1) break;

        for(auto v : sas[x]) if(v.first != oj[x] && v.first != pod_dla[x]){
            Q.push({pod[v.first] + v.second - nad[x], v.first});
        }

        x = pod_dla[x];
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    int a, b, c;
    for(int i=0; i<n-1; ++i){
        cin >> a >> b >> c;
        sas[a].push_back({b, c});
        sas[b].push_back({a, c});
    }

    nad[1] = 0;
    dfs();

    for(auto v : sas[1])
        Q.push({pod[v.first] + v.second, v.first});
    while(k-- && !Q.empty()){
        while(!Q.empty() && powr[Q.top().second]) Q.pop();
        if(Q.empty() || Q.top().first <= 0) break;

        pair<long long, int> curr = Q.top();
        Q.pop();
        ans -= curr.first;

        dod_max(curr.second);
    }
    cout << ans << '\n';
}
