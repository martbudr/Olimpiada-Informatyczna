#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1;
int n, m;
vector<int> G[N_MAX], traG[N_MAX]; // graf i graf transponowany
int deg[N_MAX];

set<int> sas[N_MAX]; // dla grafu scc
vector<int> tra_sas[N_MAX];

// scc
vector<int> kol_dfs;
bool vis[N_MAX];
void dfs1(int u)
{
    vis[u] = true;
    for(auto v : G[u]) if(!vis[v]){
        dfs1(v);
    }
    kol_dfs.push_back(u);
}

int nr = 0; // ilosc skladowych
int scc[N_MAX];
void dfs2(int u)
{
    scc[u] = nr;
    for(auto v : traG[u]) {
        if(scc[v] == 0){
            dfs2(v);
        }
        else if(scc[v] != scc[u] && sas[scc[v]].count(scc[u]) == 0){
            sas[scc[v]].insert(scc[u]);
            tra_sas[scc[u]].push_back(scc[v]);
            deg[scc[u]]++;
        }
    }
}

void cnt_scc()
{
    for(int i=1; i<=n; ++i) if(!vis[i]) dfs1(i);
    for(int i=1; i<=n; ++i) scc[i] = 0;
    for(int i=n-1; i>=0; --i){
        if(scc[kol_dfs[i]] == 0){
            nr++;
            dfs2(kol_dfs[i]);
        }
    }
}
// end of scc

set<int> good;
void fin_ans()
{
    queue<int> Q;
    for(int i=1; i<=nr; ++i){
        if(deg[i] == 0) Q.push(i);
    }

    set<int> anc; // ancestors
    int proc = 0; // processed
    while(!Q.empty()){
        int siz = Q.size();
        if(siz == 1){ // skladowa moze byc dobra tylko i wylacznie jesli jest jedna o zerowym stopniu wchodzacych po usunieciu ilus tam poprzednich
                // (czyli jest max jedna na jednej warstwie)
                // ale bedzie dobra tylko jesli ilosc sprocesowanych jest taka sama jak ilosc poprzednikow (bo jesli z ktoregos nie wchodzi
                                                                                                            // do niej krawedz, to nie bedzie sie
                                                                                                            // dalo przejsc miedzy nimi)
                // musimy rozwazac tylko ten fragment przed aktualnie rozwazana skladowa, poniewaz do wszystkich dalszych trywialnie da sie przejsc
                // zgodnie z sortowaniem topologicznym
            for(auto v : tra_sas[Q.front()])
                anc.insert(v);

            if((int)anc.size() == proc)
                good.insert(Q.front());
        }

        while(siz--){
            int curr = Q.front();
            Q.pop();

            // aktualizacje dla wszystkich procesowanych przed usunieciem tej warstwy
            for(auto v : tra_sas[curr])
                anc.insert(v);
            for(auto v : sas[curr]){
                deg[v]--;
                if(deg[v] == 0) Q.push(v);
            }

            proc++;
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        G[a].push_back(b);
        traG[b].push_back(a);
    }

    cnt_scc();
    fin_ans();

    // te bedace w dobrych skladowych wrzucamy do vectora
    vector<int> ans;
    for(int i=1; i<=n; ++i){
        if(good.find(scc[i]) != good.end())
            ans.push_back(i);
    }
    cout << (int)ans.size() << '\n';
    for(auto i : ans) cout << i << ' ';
    cout << '\n';
}
