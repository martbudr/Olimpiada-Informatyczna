/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace
    87-100 Torun
*/
#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 3e5 + 1;
int n, m, k;
int dl[N_MAX], kr[N_MAX];

vector<int> wyst[N_MAX]; // occurrences of a certain type of coach (wagonu)
int its[N_MAX]; // iterators to a certain type of coach (which one from a certain type we're considering right now)

vector<int> frs(N_MAX, INT_MAX), // closest possible (to the beginning)
            lst(N_MAX, INT_MIN); // furthest possible for a certain occurrence in a shorter one
bool exists = true;

void find_frs()
{
    int it = 0;
    for(int i=0; i<n; ++i){
        if(dl[i] == kr[it]){
            frs[it] = min(frs[it], i);
            it++;
            if(it == m) break;
        }
    }

    if(it < m) exists = false;
}

void find_lst()
{
    int it = m-1;
    for(int i=n-1; i>=0; --i){
        if(dl[i] == kr[it]){
            lst[it] = max(lst[it], i);
            it--;
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> k;
    for(int i=0; i<n; ++i){
        cin >> dl[i];
        its[dl[i]] = 0;
    }
    for(int i=0; i<m; ++i){
        cin >> kr[i];
        wyst[kr[i]].push_back(i);
    }

    find_frs();
    if(!exists){
        for(int i=0; i<n; ++i)
            cout << 0 << ' ';
        cout << '\n';
        return 0;
    }

    find_lst();

    // iteracja w celu sprawdzania
    for(int i=0; i<n; ++i){
        int ty = dl[i]; // which type

        while(its[ty] < (int)wyst[ty].size() &&
              (frs[wyst[ty][its[ty]]] == INT_MAX || lst[wyst[ty][its[ty]]] < i)) its[ty]++;

        if(its[ty] < (int)wyst[ty].size()
            && frs[wyst[ty][its[ty]]] <= i && i <= lst[wyst[ty][its[ty]]]) cout << 1 << ' ';
        else cout << 0 << ' ';
    }
    cout << '\n';
}
