#include <bits/stdc++.h>

using namespace std;

const int L_MAX = 5e4;
int n, m;
vector<int> nast[L_MAX], // nast - nastepcy
            odwr_nast[L_MAX],
            kolej_dfs, // kolejnosc dfs (do drugiego przejscia)
            ktora_skl(L_MAX), // do ktorej skladowej nalezy dany wierzcholek
            wielk_skl(L_MAX + 1), // ile wierzcholkow zawiera dana skladowa (wielkosc skladowej) - pozniej : wynik
            stopnie(L_MAX + 1); // ile wierzcholkow wychodzi z danego wierzcholka

set<int> sss_nast[L_MAX + 1]; // nastepcy w grafie silnie spojnych skladowych

int nr_sss = 1; // nr silnie spojnej skladowej - pozniej : ile ich jest

void dfs_1(int current) // rekurencyjny
{
    ktora_skl[current] = true;

    for(int i : nast[current]){
        if(!ktora_skl[i])
            dfs_1(i);
    }

    kolej_dfs.push_back(current);
}

void dfs_2(int current, int nr_sss)
{
    ktora_skl[current] = nr_sss;
    wielk_skl[nr_sss]++;

    for(int i : odwr_nast[current]){
        if(!ktora_skl[i])
            dfs_2(i, nr_sss);
    }
}

void stworz_nowy() // tworzenie nowego grafu silnie spojnych skladowych
{
    for(int i=0; i<n; ++i){
        for(int& j : nast[i]){
            if(ktora_skl[i] != ktora_skl[j] && sss_nast[ktora_skl[j]].find(ktora_skl[i]) == sss_nast[ktora_skl[j]].end()){ // jesli rozne skladowe i ich sasiedztwo nie zostalo pokazane w grafie
                sss_nast[ktora_skl[j]].insert(ktora_skl[i]); // do nastepnego wloz aktualny (bo wchodzi on tam)
                stopnie[ktora_skl[i]]++;
            }
        }
    }
}

void przejdz_top() // przejscie topologicznie
{
    queue<int> Q;
    for(int i=1; i<=nr_sss; ++i){
        if(stopnie[i] == 0)
            Q.push(i);
    }

    while(!Q.empty()){
        int current = Q.front();
        Q.pop();

        for(auto& i : sss_nast[current]){
            wielk_skl[i] += wielk_skl[current];

            stopnie[i]--;
            if(stopnie[i] == 0)
                Q.push(i);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    int a, b;
    for(int i=0; i<m; ++i){
        cin >> a >> b;
        nast[a-1].push_back(b-1);
        odwr_nast[b-1].push_back(a-1);
    }

    for(int i=0; i<n; ++i){ // pierwsze przejscie
        if(!ktora_skl[i])
            dfs_1(i);
    }

    for(int i=0; i<n; ++i)
        ktora_skl[i] = 0;

    // drugie przejscie
    for(int i=n-1; i>=0; --i){
        if(!ktora_skl[kolej_dfs[i]])
            dfs_2(kolej_dfs[i], nr_sss++);
    }
    nr_sss--;

    stworz_nowy();
    przejdz_top();

    for(int i=0; i<n; ++i){
        cout << wielk_skl[ktora_skl[i]] - 1 << '\n';
    }
}
