#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<double, int>> cost; // a[i] / b[i]

bool compare(pair<double,int> left, pair<double,int> right)
{
    return ((left.first > right.first) || (left.first == right.first && left.second < right.second));
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    cost.reserve(n);
    double a, b;
    for(int i=0; i<n; ++i){
        cin >> a >> b;
        if(b == 0){
            if(a == 0)
                cost[i].first = -DBL_MAX;
            else cost[i].first = DBL_MAX;
        }
        else cost[i].first = a/b;
        cost[i].second = i+1;
    }

    sort(cost.begin(), cost.begin()+n, compare);

    for(int i=0; i<n; ++i)
        cout << cost[i].second << '\n';
}
