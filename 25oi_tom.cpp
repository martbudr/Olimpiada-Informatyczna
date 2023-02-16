#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1, S_MAX = 1e6 + 1;
int n, s;
vector<int> kt[S_MAX];
int it[S_MAX];
int amt = 0; // ile wolnych

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> s;
    int a;
    for(int i=1; i<=n; ++i){
        cin >> a;
        a = (a+1)%s;
        kt[a].push_back(i);

        it[i] = 0;
    }

    int ans[n];
    int ans_it = 0;
    for(auto i : kt[0]) ans[ans_it++] = i;

    priority_queue<pair<int,int>> Q; // ile, jakiej
    for(int i=1; i<s; ++i){
        if(kt[i].size() > 0)
            Q.push({kt[i].size(), i});
    }

    int curr = 0;
    while(!Q.empty()){
        pair<int,int> frs = Q.top();
        Q.pop();

        if((curr + frs.second)%s != s-1 || ans_it == n-1){
            curr = (curr + frs.second)%s;
            ans[ans_it++] = kt[frs.second][it[frs.second]++];

            if(frs.first > 1) Q.push({frs.first-1, frs.second});
        }
        else if((int)Q.size() != 0){
            pair<int,int> nxt = Q.top();
            Q.pop();
            curr = (curr+nxt.second)%s;
            ans[ans_it++] = kt[nxt.second][it[nxt.second]++];

            if(nxt.first > 1) Q.push({nxt.first-1, nxt.second});
            Q.push({frs.first, frs.second});
        }
        else{
            amt++;

            curr = 0;
            ans[ans_it++] = kt[frs.second][it[frs.second]++];

            if(frs.first > 1) Q.push({frs.first-1, frs.second});
        }
    }


    cout << amt << '\n';
    for(int i=0; i<ans_it; ++i) cout << ans[i] << ' ';
    cout << '\n';
}
