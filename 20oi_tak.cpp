#include <bits/stdc++.h>

using namespace std;

const int T_MAX = 5e5;
long long n, m;
int t;
vector<long long> tax;

long long comp;

int ans()
{
    long long le = 0, ri = m;
    comp = m;
    for(int i=0; i<t; ++i){
        if(m-le >= n-ri){
            if(tax[i] <= m-le) break;

            le += tax[i] - (m-le);
        }
        else{
            if(tax[i] < n-ri) break;

            comp -= (tax[i]-(n-m))/2;
            ri = n;
        }

        if((le >= n) || (le >= comp && ri == n)) return i+1;
    }

    return 0;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> t;
    tax.resize(t);
    for(int i=0; i<t; ++i)
        cin >> tax[i];

    sort(tax.rbegin(), tax.rend());

    cout << ans() << '\n';
}
