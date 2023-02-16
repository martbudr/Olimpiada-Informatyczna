#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n, q;
int tab[N_MAX];

struct S{
    int ans, wart, pos;
};

int comp_queue(int k)
{
    deque<S> Q;
    Q.push_back({0, tab[0], 0});

    for(int i=1; i<n; ++i){
        if(Q.front().pos < i-k) Q.pop_front();

        int answ = Q.front().ans + (Q.front().wart <= tab[i]);
        while(!Q.empty() && (Q.back().ans > answ || (Q.back().ans == answ && Q.back().wart <= tab[i]))) Q.pop_back();

        Q.push_back({answ, tab[i], i});
    }
    return Q.back().ans;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=0; i<n; ++i)
        cin >> tab[i];

    cin >> q;
    while(q--){
        int k;
        cin >> k;

        cout << comp_queue(k) << '\n';
    }
}
