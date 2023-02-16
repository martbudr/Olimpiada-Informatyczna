#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 6e4 + 1, Q = 16, LISC = 1<<Q;
int n, m, q;

int nax[LISC<<1], to_push[LISC<<1];
void chan(int x, int amt) // change value (update in a certain point)
{
    if(x < LISC)
        to_push[x] += amt;
    nax[x] += amt;
}

void push(int x)
{
    x += LISC;

    for(int i=Q; i>=1; --i){
        int _x = x>>i;
        if(to_push[_x] == 0) continue;

        chan(_x<<1, to_push[_x]);
        chan((_x<<1)+1, to_push[_x]);
        to_push[_x] = 0;
    }
}

int query(int a, int b) // max na przedziale
{
    a += LISC; b += LISC;

    int ans = max(nax[a], nax[b]);

    while(a>>1 != b>>1){
        if(a%2 == 0) ans = max(ans, nax[a+1]);
        if(b%2 == 1) ans = max(ans, nax[b-1]);

        a >>= 1; b >>= 1;
    }
    return ans;
}

void upd(int a, int b, int amt) // dorzucanie iles tam na przedziale
{
    a += LISC; b += LISC;

    chan(a, amt);
    if(a != b) chan(b, amt);
    while(a>>1 != b>>1){
        if(a%2 == 0) chan(a+1, amt);
        if(b%2 == 1) chan(b-1, amt);

        a >>= 1; b >>= 1;
    }
}

void build(int x)
{
    x += LISC;

    x >>= 1;
    while(x){
        nax[x] = max(nax[x<<1], nax[(x<<1) + 1]);

        x >>= 1;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> q;
    int a, b, amt;
    while(q--){
        cin >> a >> b >> amt;
        b--; // !

        push(a); push(b);
        if(query(a, b) + amt <= m){
            cout << "T" << '\n';
            upd(a, b, amt);
            build(a); build(b);
        }
        else cout << "N" << '\n';
    }
}
