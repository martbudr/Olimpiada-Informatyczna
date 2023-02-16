#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n, m;
pair<int,int> kraw[N_MAX];
vector<pair<int,int>> sas[N_MAX], tra_sas[N_MAX];
char dir[N_MAX];

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

    if(ran[xx] < ran[yy])
        dsu[xx] = yy;
    else if(ran[xx] > ran[yy])
        dsu[yy] = xx;
    else{
        dsu[yy] = xx;
        ran[xx]++;
    }
}
// end of dsu

vector<int> ord_dfs;
bool vis[N_MAX], trav[N_MAX];
void dfs1(int u, int p = -1)
{
    vis[u] = true;
    for(auto v : sas[u]){
        if(trav[v.second]) continue;
        dir[v.second] = (kraw[v.second].first == u ? '>' : '<');
        trav[v.second] = true;
        tra_sas[v.first].push_back({u,v.second});
        if(!vis[v.first]){
            dfs1(v.first);
        }
    }
    ord_dfs.push_back(u);
}

void dfs2(int u)
{
    vis[u] = true;
    for(auto v : tra_sas[u]) if(!vis[v.first]){
        uni(u, v.first);
        dfs2(v.first);
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for(int i=1; i<=n; ++i) dsu[i] = i;
    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        kraw[i].first = a;
        kraw[i].second = b;

        sas[a].push_back({b,i});
        sas[b].push_back({a,i});
    }
    for(int i=1; i<=n; ++i){
        if(!vis[i]) dfs1(i);
    }
    for(int i=1; i<=n; ++i) vis[i] = false;
    for(int i=n-1; i>=0; --i){
        if(!vis[ord_dfs[i]]) dfs2(ord_dfs[i]);
    }

    set<int> ans;
    for(int i=1; i<=n; ++i){
        int skl = fin(i);
        if(ans.find(skl) == ans.end()) ans.insert(skl);
    }
    cout << (int)ans.size() << '\n';
    for(int i=0; i<m; ++i) cout << dir[i];
    cout << '\n';
}
