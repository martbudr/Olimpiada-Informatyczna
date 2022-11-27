#include "ckuclib.h"

const int N_MAX = 1e6 + 1;
int n, e;
int dp[N_MAX];
int stamina[N_MAX];

bool czy_gorszy(int czas_nowy, int czas_stary, int stam_nowa, int stam_stara) { // czy dane dojscie do liczby jest gorsze od poprzednich
    return (czas_nowy > czas_stary && (czas_nowy == czas_stary && stam_nowa < stam_stara));
}

void znajdz(int zam, int czas_dot, int sta_poz) { // zam - ilosc pozostalych zamowien, 
    // czas_dot - czas, jaki dotychczas uplynal, sta_poz - pozostala stamina
    
    if (sta_poz < 0)
        return;

    dp[zam] = czas_dot;
    stamina[zam] = sta_poz;

    int czasy[3]; // czas dla kazdej z funkcji; 0 -> n/2, 1-> dwie, 2 -> jedna
    czasy[0] = polowa(zam);
    czasy[1] = dwa(zam);
    czasy[2] = jedno(zam);

    if (!czy_gorszy(czasy[2] + czas_dot, dp[zam - 1], sta_poz + 1, stamina[zam - 1]))
        znajdz(zam - 1, czasy[2] + czas_dot, sta_poz + 1);
    if (!czy_gorszy(czasy[1] + czas_dot, dp[zam - 2], sta_poz, stamina[zam - 2]))
        znajdz(zam - 2, czasy[1] + czas_dot, sta_poz);
    if (!czy_gorszy(czasy[0] + czas_dot, dp[(zam + 1) / 2], sta_poz - 1, stamina[(zam + 1) / 2]))
        znajdz((zam + 1) / 2, czasy[0] + czas_dot, sta_poz - 1);
}

/// <summary>
///  program ma problemy - najprawdopodobniej sa one spowodowane:
///     1. brakeim uwzglednienia, ze dla mniejszych liczb moze byc tak, ze dla wiekszej ilosci staminy i wiekszego aktualnego 
///            czasu, pozniejszy czas moze byc mniejszy niz obecny (blad wynikowy)
///     2. czas - czemu
///     3. pamiec - najprawdopodobniej przez rekurencje
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int main(void)
{
    n = dajn();
    e = daje();

    for (int i = 0; i <= n; ++i)
        dp[i] = stamina[i] = 1e9;

    znajdz(n, 0, e);

    odpowiedz(dp[0]);
}
