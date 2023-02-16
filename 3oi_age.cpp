#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 3e3 + 1;
int n, m, p;
vector<int> koszt(N_MAX, INT_MAX); // ile kosztuje przekupienie danej skladowej
vector<int> sas[N_MAX], tra_sas[N_MAX];
vector<int> kol_dfs;

// dsu
int dsu[N_MAX], ran[N_MAX];
int fin(int x)
{
    if(dsu[x] == x) return x;

    return dsu[x] = fin(dsu[x]);
}

void uni(int x, int y)
{
    int xx = fin(x), yy = fin(y);
    if(xx == yy) return;

    if(ran[xx] > ran[yy]){
        dsu[yy] = xx;
        koszt[xx] = min(koszt[xx], koszt[yy]);
    }
    else if(ran[xx] < ran[yy]){
        dsu[xx] = yy;
        koszt[yy] = min(koszt[yy], koszt[xx]);
    }
    else{
        dsu[yy] = xx;
        ran[xx]++;
        koszt[xx] = min(koszt[xx], koszt[yy]);
    }
}
// koniec dsu

bool vis[N_MAX];
void dfs1(int u)
{
    vis[u] = true;
    for(auto v : sas[u]) if(!vis[v]){
        dfs1(v);
    }
    kol_dfs.push_back(u);
}

void dfs2(int u)
{
    vis[u] = true;
    for(auto v : tra_sas[u]) if(!vis[v]){
        uni(u, v);
        dfs2(v);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> p;
    for(int i=1; i<=n; ++i) dsu[i] = i;
    int a, b, ile;
    for(int i=0; i<p; ++i){
        cin >> a >> ile;
        koszt[a] = ile;
    }
    cin >> m;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        sas[a].push_back(b);
        tra_sas[b].push_back(a);
    }

    for(int i=1; i<=n; ++i){
        if(!vis[i]) dfs1(i);
    }
    for(int i=1; i<=n; ++i) vis[i] = false;
    for(int i=n-1; i>=0; --i){
        if(!vis[kol_dfs[i]]) dfs2(kol_dfs[i]);
    }

    // graf scc
    vector<int> scc[N_MAX];
    int deg[N_MAX];
    for(int i=1; i<=n; ++i){
        for(auto v : sas[i]){
            int ii = fin(i), vv = fin(v);
            if(ii != vv){
                scc[ii].push_back(vv);
                deg[vv]++;
            }

        }
    }

    int sum = 0;
    set<int> skl;
    for(int i=1; i<=n; ++i){
        int ii = fin(i);
        if(deg[ii] == 0){
            if(skl.find(ii) != skl.end()) continue;

            if(koszt[ii] == INT_MAX){
                cout << "NIE" << '\n' << i << '\n';
                return 0;
            }

            sum += koszt[ii];
            skl.insert(ii);
        }
    }
    cout << "TAK" << '\n' << sum << '\n';
}
