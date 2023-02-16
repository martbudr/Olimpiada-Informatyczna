#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 1;
int n;
int a[N_MAX];
int amt[N_MAX];
pair<int,int> ans = {0,0}; // wynik, dla ktorego
int poprz[N_MAX];

const int Q = 17, LISC = 1<<Q;
pair<int,int> tree[LISC<<1];
void ins(int x, pair<int,int> to_ins) // x - miejsce, to_ins - {ile, dla ktorego}
{
    x += LISC;

    while(x){
        if(tree[x].first < to_ins.first)
            tree[x] = to_ins;
        x >>= 1;
    }
}

pair<int,int> query(int a, int b) // max na przedziale
{
    a += LISC; b += LISC;

    pair<int,int> nax = tree[a];
    if(nax.first < tree[b].first) nax = tree[b];
    while(a>>1 != b>>1){
        if(a%2 == 0)
            if(nax.first < tree[a+1].first) nax = tree[a+1];
        if(b%2 == 1)
            if(nax.first < tree[b-1].first) nax = tree[b-1];

        a >>= 1; b >>= 1;
    }
    return nax;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q; // ile do usuniecia, dla jakiej wartosci
    for(int i=1; i<=n; ++i){
        cin >> a[i];
        Q.push({i-a[i], a[i]});
    }

    while(!Q.empty() && Q.top().first < 0) Q.pop();
    while(!Q.empty()){
        pair<int,int> curr = Q.top();
        int curr_id = curr.first + curr.second;
        Q.pop();

        pair<int,int> ne = query(1, curr.second-1); // para {ile, dla ktorego)
        ne.first++;
        poprz[curr_id] = ne.second;
        ins(curr.second, {ne.first, curr_id});

        if(ne.first > ans.first) ans = {ne.first, curr_id};
    }

    // wypisywanie wyniku
    vector<int> to_pr;
    int i = ans.second, _i = i;
    cout << i - a[i] << '\n';
    while(i){
        int j = poprz[i];
        int to_usu = i - a[i] - (j - a[j]);
        for(int _=1; _<=to_usu; ++_)
            to_pr.push_back(i-_);

        i = poprz[i];
    }
    for(int _ = _i-a[_i]-1; _>=0; --_)
        cout << to_pr[_] << ' ';
    cout << '\n';
}
