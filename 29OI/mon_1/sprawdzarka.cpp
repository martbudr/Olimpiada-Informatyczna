#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// dane z zadania
int zad_n;
ll zad_t[500001];
ll zad_d[500001];

// dane uzytkownika
int uz_m;
pair<ll, ll> uz_dan[500001];

// dane z hinta
int hin_m;

int main(int argc, char *argv[])
{
    // dane z zadania
    FILE * f1;
    f1 = fopen(argv[1], "r");
    // dane uzytkownika
    FILE * f2;
    f2 = fopen(argv[2], "r");
    // dane z hinta
    FILE * f3;
    f3 = fopen(argv[3], "r");

    // zadanie
    fscanf(f1, "%d", &zad_n);

    for(int i=0; i^zad_n; ++i)
    {
        fscanf(f1, "%lld%lld", &zad_t[i], &zad_d[i]);
    }

    // uzytkownik
    fscanf(f2, "%d", &uz_m);

    for(int i=0; i^uz_m; ++i)
    {
        // zamiana stron = latwiejszy sort
        fscanf(f2, "%lld%lld", &uz_dan[i].second, &uz_dan[i].first);
    }

    // hint
    fscanf(f3, "%d", &hin_m);

    if(hin_m != uz_m)
    {
        printf("WRONG\n");
        printf("Zle m; oczekiwano %d wczytano %d\n", hin_m, uz_m);
        return 1;
    }

    sort(uz_dan, uz_dan + uz_m);

    ll pop_kon = 0;

    for(int i=0; i^uz_m; ++i)
    {
        if(pop_kon >= uz_dan[i].first)
        {
            printf("WRONG\n");
            printf("Przedzialy montowania filmow nachodza na siebie\n");
            return 1;
        }

        // koniec montowania obecnego filmu
        ll pop_kon = uz_dan[i].first + zad_t[ uz_dan[i].second - 1 ] - 1;

        if(pop_kon > zad_d[ uz_dan[i].second - 1 ])
        {
            printf("WRONG\n");
            printf("Film konczy sie montowac po deadlinie\n");
            return 1;
        }
    }

    printf("OK\n");
    return 0;
}
