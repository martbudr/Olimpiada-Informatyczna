#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 1, LOGN = 17+1;
int n, m, logn;
string tab;
int num[N_MAX][LOGN];
int num_amt[(1<<LOGN) + 1][LOGN];
int amt[LOGN]; // ile roznych kazdej dlugosci

void ini_set()
{
    for(int i=1; i<=logn; ++i){
        for(int j=0; j<n-i+1; ++j){
            int x = 0;
            for(int k=0; k<i; ++k){
                x += tab[j + k]-'0';
                x <<= 1;
            }
            x >>= 1;
            num[j][i] = x;
            if(num_amt[x][i] == 0) amt[i]++;
            num_amt[x][i]++;
        }
    }
}

void ins(int x) // aktualizowanie
{
    for(int i=logn; i>=1; --i){
        int frs = max(x - i + 1, 0), lst = min(x, n-i);
        for(int j=frs; j <= lst; ++j){
            int prev = num[j][i];
            num_amt[prev][i]--;
            if(num_amt[prev][i] == 0) amt[i]--;

            if(tab[x] == '0') num[j][i] += (1<<(i - (x-j) - 1));
            else num[j][i] -= (1<<(i - (x-j) - 1));

            int curr = num[j][i];
            if(num_amt[curr][i] == 0) amt[i]++;
            num_amt[curr][i]++;
        }
    }
}

bool check(int x) // czy istnieja wszystkie kombinacje danego rozmiaru
{
    return (amt[x] == (1<<x));
}

int wysz_bin()
{
    int l = 1, r = logn+1;
    while(l < r){
        int mi = (l+r) / 2;
        if(check(mi)) l = mi+1;
        else r = mi;
    }
    return l;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> tab;
    logn = log2(n);

    ini_set();

    int x;
    cout << wysz_bin() << '\n';
    while(m--){
        cin >> x;
        ins(x-1);
        tab[x-1] = (tab[x-1] == '0' ? '1' : '0');

        cout << wysz_bin() << '\n';
    }
}
