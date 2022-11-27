#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 3e5 + 1;
int n;
vector<int> sas[N_MAX];
int dp[N_MAX];

void dfs(int curr, int u, int p = -1)
{
    dp[u] = 0;

    for(auto v : sas[u]) if(v != p){
        dfs(curr, v, u);
        dp[u] += dp[v] + 1;
    }

    dp[u] = max(dp[u]-curr, 0);
}

int wysz_bin()
{
    int l = (int)sas[1].size(), r = n-1;

    while(l < r){
        int mi = (l + r) / 2;

        dfs(mi, 1);

        if(dp[1] == 0) r = mi;
        else l = mi+1;
    }
    return l;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int a, b;
    for(int i=0; i<n-1; ++i){
        cin >> a >> b;
        sas[a].push_back(b);
        sas[b].push_back(a);
    }

    cout << wysz_bin() << '\n';
}
