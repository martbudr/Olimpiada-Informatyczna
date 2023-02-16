#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1, LOGN = 18;
int n, m;
struct kraw{
    int a, b, len;
};
vector<kraw> rozp; // krawedzie wchodzace w sklad drzewa rozpinajacego
vector<pair<int,int>> sas[N_MAX];

void build(int nax) // nax - maksymalne len
{
    for(int i=1; i<N_MAX; ++i) sas[i].clear();
    vector<kraw> pom_rozp; // zawiera tylko te krawedzie, ktore sa krotsze niz nax (zeby dopiero pozniej dorzucic te, ktore sa w drzewie rozpinajacym)
    for(auto x : rozp){
        if(x.len > nax){
            sas[x.a].push_back({x.b, nax});
            sas[x.b].push_back({x.a, nax});
            sas[x.a+x.len-nax].push_back({x.b+x.len-nax, nax});
            sas[x.b+x.len-nax].push_back({x.a+x.len-nax, nax});
        }
        else if(x.len == nax){
            sas[x.a].push_back({x.b, nax});
            sas[x.b].push_back({x.a, nax});
        }
        else{
            pom_rozp.push_back({x.a, x.b, x.len});
        }
    }
    rozp = pom_rozp;
}

int ans; // ile skladowych (liczone dla kazdego, ale interesuje nas tylko dla k=0)
vector<bool> odw(N_MAX);
void dfs(int u)
{
    odw[u] = true;
    for(auto v : sas[u]) if(!odw[v.first]){
        rozp.push_back({u, v.first, v.second});
        dfs(v.first);
    }
}

void find_rozp()
{
    ans = 0;
    odw.clear();
    odw.resize(n+1, false);
    for(int i=1; i<=n; ++i){
        if(!odw[i]){
            dfs(i);
            ans++;
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    int a, b, len;
    for(int i=0; i<m; ++i){
        cin >> a >> b >> len;
        rozp.push_back({a, b, len});
    }

    for(int i=LOGN; i>=0; --i){
        build(1<<i);
        find_rozp();
    }

    cout << ans << '\n';
}
