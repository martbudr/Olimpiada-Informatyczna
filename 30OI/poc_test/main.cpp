// bledne (nie przechodzi np. poc26)
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

int ans[N_MAX]; // supposed-to-be
bool same = true;

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

    // oficjalne (od poc3 moje)
    ifstream wej("C:\\Users\\marti\\Downloads\\ocen-win\\ocen-win\\in\\poc2.in");
    ifstream wyj("C:\\Users\\marti\\Downloads\\ocen-win\\ocen-win\\out\\poc2.out");

    // z forum
    //ifstream wej("C:\\Users\\marti\\Downloads\\POC-20221102T212549Z-001\\POC\\poc26.in");
    //ifstream wyj("C:\\Users\\marti\\Downloads\\POC-20221102T212549Z-001\\POC\\poc26.out");

    wej >> n >> m >> k;
    for(int i=0; i<n; ++i){
        wej >> dl[i];
    }
    for(int i=0; i<m; ++i){
        wej >> kr[i];
        wyst[kr[i]].push_back(i);
    }
    for(int i=0; i<n; ++i){
        wyj >> ans[i];
    }

    find_frs();
    if(!exists){
        for(int i=0; i<n; ++i)
            if(ans[i] != 0) same = false;

        cout << (same ? "YES" : "NO") << '\n';
        return 0;
    }

    find_lst();

    // iteracja w celu sprawdzania
    for(int i=0; i<n; ++i){
        int ty = dl[i]; // which type

        while(its[ty] < (int)wyst[ty].size() &&
              (frs[wyst[ty][its[ty]]] == INT_MAX || lst[wyst[ty][its[ty]]] < i)) its[ty]++;

        if(its[ty] < (int)wyst[ty].size()
            && frs[wyst[ty][its[ty]]] <= i && i <= lst[wyst[ty][its[ty]]]) same = (ans[i] == 1);
        else same = (ans[i] == 0);

        if(same == false){
            cout << i << ' ';
            break;
        }
    }
    cout << (same ? "YES" : "NO") << '\n';
}
