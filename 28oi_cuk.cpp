#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 3e5 + 1, IL_GAB = 3;
int n;
pair<long long, int> gab[N_MAX][IL_GAB];
bool all_zeros[IL_GAB];

long long cost = 0;
vector<pair<long long,int>> nin_dro, nin_pac, nin_rog;

void find_nin(int st)
{
    int nin0 = st, nin1 = st, nin2 = st;
    for(int i=st+1; i<n; ++i){
        if(gab[nin0][0].first > gab[i][0].first)
            nin0 = i;
        if(gab[nin1][1].first > gab[i][1].first)
            nin1 = i;
        if(gab[nin2][2].first > gab[i][2].first)
            nin2 = i;
    }

    nin_dro.push_back(gab[nin0][0]);
    nin_pac.push_back(gab[nin1][1]);
    nin_rog.push_back(gab[nin2][2]);

    swap(gab[st][0], gab[nin0][0]);
    swap(gab[st][1], gab[nin1][1]);
    swap(gab[st][2], gab[nin2][2]);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i=0; i<IL_GAB; ++i)
        all_zeros[i] = true;

    cin >> n;
    for(int i=0; i<n; ++i){
        long long nax = 0;
        for(int j=0; j<IL_GAB; ++j){
            cin >> gab[i][j].first;
            if(gab[i][j].first != 0) all_zeros[j] = false;
            gab[i][j].second = i;

            cost += gab[i][j].first;

            nax = max(nax, gab[i][j].first);
        }

        cost -= nax;

        for(int j=0; j<IL_GAB; ++j)
            gab[i][j].first = nax - gab[i][j].first;
    }

    for(int i=0; i<IL_GAB; ++i)
        find_nin(i);

    long long zw = LLONG_MAX;
    for(int i=0; i<IL_GAB; ++i){
        for(int j=0; j<IL_GAB; ++j){
            for(int k=0; k<IL_GAB; ++k){
                if(nin_dro[i].second != nin_pac[j].second && nin_pac[j].second != nin_rog[k].second && nin_rog[k].second != nin_dro[i].second){
                    long long zw_lok = 0;
                    if(!all_zeros[0]) zw_lok += nin_dro[i].first;
                    if(!all_zeros[1]) zw_lok += nin_pac[j].first;
                    if(!all_zeros[2]) zw_lok += nin_rog[k].first;
                    zw = min(zw, zw_lok);

                    //zw = min(zw, nin_dro[i].first + nin_pac[j].first + nin_rog[k].first);
                }
            }
        }
    }

    cout << cost + zw << '\n';
}
