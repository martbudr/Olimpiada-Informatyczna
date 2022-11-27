// bledne
#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e3 + 1;
int n;
vector<int> sas[N_MAX], pre[N_MAX];
int deg[N_MAX];
vector<int> ord;
vector<bitset<N_MAX>> mom(N_MAX);

void topo_sort(int st) // st - start
{
    queue<int> Q;
    Q.push(st);
    while(!Q.empty()){
        int u = Q.front();
        ord.push_back(u);
        Q.pop();

        for(int v : sas[u]){
            deg[v]--;
            if(deg[v] == 0) Q.push(v);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int amt, b;
    for(int i=1; i<=n-1; ++i){
        cin >> amt;
        for(int j=0; j<amt; ++j){
            cin >> b;
            sas[i].push_back(b);
            pre[b].push_back(i);
            deg[b]++;
        }
    }

    topo_sort(1);

    mom[1][0] = 1;
    for(int i=1; i<n-1; ++i){
        int u = ord[i];
        for(auto v : pre[u]){
            mom[u] |= (mom[v]<<1);
        }
        cout << u << ' ' << mom[u].count() << '\n';
    }

    cout << (mom[n].count()) << '\n';
}
