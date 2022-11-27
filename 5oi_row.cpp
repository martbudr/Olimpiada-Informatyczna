// wchodzi na 45
#include <bits/stdc++.h>

using namespace std;

const int SI_MAX = 2e6 + 1, LI_MAX = 26;
int t, li, n, m;// li - ilosc liter
string le, ri;
int dl[LI_MAX];

long long le_len, ri_len;
vector<char> wha; // what on position
vector<int> wyst[LI_MAX]; // wystapienia danej litery
vector<vector<int>> sas;
vector<bool> vis;

int bfs(int i)
{
    // -1 jak sie nie da
    // 0 jak nieustalone
    // 1 jak ustalone
    int is_set = 0;
    char set_to = '.';

    queue<int> Q;
    Q.push(i);
    while(!Q.empty()){
        int curr = Q.front();
        vis[curr] = true;
        Q.pop();

        if(curr < le_len && !vis[curr + le_len]) Q.push(curr + le_len);
        else if(curr > le_len && !vis[curr - le_len]) Q.push(curr - le_len);
        if(wha[curr] != '1' && wha[curr] != '0'){
            for(auto ne : sas[curr]) if(!vis[ne]) Q.push(ne);
        }
        else{
            if(is_set == 1 && wha[curr] != set_to) return -1;
            set_to = wha[curr];
            is_set = 1;
        }
    }

    return (is_set == 0);
}

void cle()
{
    for(int i=0; i<2*le_len; ++i)
        sas[i].clear();
    for(int i=0; i<li; ++i)
        wyst[i].clear();
}

long long find_ans()
{
    le_len = 0, ri_len = 0;
    for(int i=0; i<n; ++i){
        if(le[i] != '1' && le[i] != '0') le_len += dl[le[i]-'a'];
        else le_len++;
    }
    for(int i=0; i<m; ++i){
        if(ri[i] != '1' && ri[i] != '0') ri_len += dl[ri[i]-'a'];
        else ri_len++;
    }
    if(le_len != ri_len) return 0;

    wha.assign(2*le_len, '-');
    sas.resize(2*le_len);

    int akt = 0;
    for(int i=0; i<n; ++i){
        wha[akt] = le[i];

        if(le[i] != '1' && le[i] != '0'){
            int len = dl[le[i]-'a'];
            if((int)wyst[le[i]-'a'].size() > 0){
                int poprz = wyst[le[i]-'a'].back();
                for(int j=0; j<len; ++j){
                    sas[akt + j].push_back(poprz + j);
                    sas[poprz + j].push_back(akt + j);
                }
            }

            wyst[le[i]-'a'].push_back(akt);
            akt += len;
        }
        else akt++;
    }
    for(int i=0; i<m; ++i){
        wha[akt] = ri[i];

        if(ri[i] != '1' && ri[i] != '0'){
            int len = dl[ri[i]-'a'];

            if((int)wyst[ri[i]-'a'].size() > 0){
                int poprz = wyst[ri[i]-'a'].back();
                for(int j=0; j<len; ++j){
                    sas[akt + j].push_back(poprz + j);
                    sas[poprz + j].push_back(akt + j);
                }
            }

            wyst[ri[i]-'a'].push_back(akt);
            akt += len;
        }
        else akt++;
    }

    vis.resize(2*le_len);
    int amt_of_comp = 0;
    for(int i=0; i<2*le_len; ++i){
        if(!vis[i]){
            int ne = bfs(i);
            if(ne == -1) return 0;
            amt_of_comp += ne;
        }
    }

    return (1 << amt_of_comp);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> t;
    while(t--){
        cin >> li;
        for(int i=0; i<li; ++i) cin >> dl[i];
        cin >> n >> le >> m >> ri;

        cout << find_ans() << '\n';

        cle();
    }
}
