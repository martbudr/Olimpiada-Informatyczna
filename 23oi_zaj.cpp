#include <bits/stdc++.h>

using namespace std;

const int M_MAX = 15001;
int n, m;
int A[M_MAX], B[M_MAX];
vector<int> prev_A(M_MAX), prev_B(M_MAX); // poprzednie w danym ciagu
vector<vector<int>> NWZ(2, vector<int>(M_MAX)); // najdluzsze wspolne zajakniecie
vector<int> memo(M_MAX); // przechowuje wartosci, ktore normalnie bylyby gdzies daleko w tablicy dp

int szuk_prev(int pos, int* V) // szukanie poprzedniego takiego samego
{
    for(int _pos = pos-1; _pos>=1; --_pos){
        if(V[_pos] == V[pos])
            return _pos;
    }
    return 0;
}

int szukaj() // szukanie wyniku ostatecznego
{
    for(int i=1; i<=n; ++i)
        prev_A[i] = szuk_prev(i, A);
    for(int j=1; j<=m; ++j)
        prev_B[j] = szuk_prev(j, B);

    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            if(A[i] == B[j] && prev_A[i] != 0 && prev_B[j] != 0)
                NWZ[i%2][j] = memo[prev_B[j]] + 2;
            else NWZ[i%2][j] = 0;
            NWZ[i%2][j] = max(NWZ[i%2][j], max(NWZ[(i-1)%2][j], NWZ[i%2][j-1]));
        }
        for(int j=1; j<=m; ++j)
            if(A[i] == B[j])
                memo[j] = NWZ[(i-1)%2][j-1];
    }
    return NWZ[n%2][m];
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i=1; i<=n; ++i)
        cin >> A[i];
    for(int i=1; i<=m; ++i)
        cin >> B[i];

    cout << szukaj() << '\n';
}
