#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5 + 1, MOD = 1e9 + 7;
int n;
vector<int> czapki(N_MAX);
vector<vector<int>> sas(N_MAX), // sasiedzi (nastepcy - czyli ci, dla ktorych dane miejsce moze ustawiac)
    odwr_sas(N_MAX); // odwrotni sasiedzi (czyli ci, ktorzy dla danego miejsca moga ustawiac)
vector<int> il_wyst_czapki(N_MAX); // ile razy dana czapka wystepuje
vector<bool> czapki_czy_ust(N_MAX), // czy dana czapka jest przypisana do konkretnego miejsca
    miejsca_czy_ust(N_MAX); // czy dane miejsce ma przypisana czapke
int niewyk_czapki; // ilosc czapek bez przypisanego miejsca
queue<int> rozw_wierz; // wierzcholki do rozwazenia
bool czy_beda = true; // czy beda jakiekolwiek ustawienia

bool ustaw(int miejsce, int nr_czapki) // ustawianie danej czapki w okreslone miejsce
{
    if(!czapki_czy_ust[nr_czapki] && !miejsca_czy_ust[miejsce]){
        miejsca_czy_ust[miejsce] = true;
        czapki_czy_ust[nr_czapki] = true;
        niewyk_czapki--;
        return true;
    }
    return false;
}

bool przejdz(int x_miej) // x_miej - pewne miejsce
{
    if(sas[x_miej].size() == 0) // jesli nastapila kolizja
        return false;
    else if(sas[x_miej].size() == 1){
        ustaw(sas[x_miej][0], czapki[x_miej]);

        // usuwanie polaczen
        int x_miej_2 = sas[x_miej][0]; // nastepnik (sasiad) x miejsce
        if(odwr_sas[x_miej_2].size() == 2){ // jesli jest dwoch ktorzy chca ustawic swojego w danym miejscu, to usun tego drugiego (a zatem zarazem obu, bo pierwszy jest usuwany pozniej)
            int x_miej_3 = (odwr_sas[x_miej_2][0] != x_miej) ? odwr_sas[x_miej_2][0] : odwr_sas[x_miej_2][1]; // nastepnik nastepnika x miejsce

            odwr_sas[x_miej_2].pop_back();

            // usuwanie krawedzi od x_miej_3 do x_miej_2
            if(sas[x_miej_3][0] == x_miej_2)
                swap(sas[x_miej_3][0], sas[x_miej_3][1]);
            sas[x_miej_3].pop_back();

            rozw_wierz.push(x_miej_3);
        }

        odwr_sas[x_miej_2].pop_back();
        sas[x_miej].pop_back();
    }
    return true;
}

int main(void) // indeksowanie od 0
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    niewyk_czapki = n;
    for(int i=0; i<n; ++i){
        cin >> czapki[i];
        il_wyst_czapki[czapki[i]]++;
    }

    // ustawianie dla skrajnych
    if(!ustaw(1, czapki[0]))
        czy_beda = false;
    if(!ustaw(n-2, czapki[n-1]))
        czy_beda = false;

    // sprawdzenie, czy nie ma za duzo danych wartosci i czy nie wystepuja w odleglosci wiekszej od siebie niz 2
    for(int i=0; i<n; ++i){
        if(il_wyst_czapki[czapki[i]] > 2) // jesli wczesniejsza ilosc wystapien czapki juz byla wieksza od 1
            czy_beda = false;
        else if(il_wyst_czapki[czapki[i]] == 2){
            if(i >= 2 && czapki[i-2] == czapki[i]){ // ustawianie juz na gotowo czapki czapki[i] na miejsce i-1 (dla np. ... 3 2 3 ...)
                if(i >= 3 && i < n-1)
                    ustaw(i-1, czapki[i]);
            }
            else
                czy_beda = false;
        }
        // reszta przypadkow jest nieinteresujaca
    }
    // tworzenie grafu
    for(int i=1; i<n; ++i){
        if(!czapki_czy_ust[czapki[i]]){ // jesli dana czapka nie jest ustawiona
            // jesli jest gdzie ja ustawic
            if(!miejsca_czy_ust[i-1]){
                sas[i].push_back(i-1);
                odwr_sas[i-1].push_back(i);
            }
            if(!miejsca_czy_ust[i+1]){
                sas[i].push_back(i+1);
                odwr_sas[i+1].push_back(i);
            }

            if(sas[i].size() == 1) // jesli jest tylko jedna krawedz (mozliwosc)
                rozw_wierz.push(i);
        }
    }

    // przechodzenie grafu
    while(!rozw_wierz.empty() && czy_beda){ // dopoki sa wierzcholki do rozwazenia rozwazaj je
        if(!przejdz(rozw_wierz.front())){ // jesli w przejsciu napotkano na kolizje
            czy_beda = false;
        }
        rozw_wierz.pop();
    }

    // policzyc ilosc przypadkow z pozostalych wolnych
    // zliczanie nieustawionych wierzcholkow
    if(czy_beda){
        long long wynik = 1;
        int ile_dowolnych = 0, z_ilu_dwie = 0, do_ilu_dod = 0; // ile_dowolnych - te, ktore nie maja zadnego narzuconego, z_ilu_dwie - z ilu dwie krawedzie wychodza, do_ilu_dod - do ilu prowadzi wiecej
                // niz 0 krawedzi
        for(int i=0; i<n; ++i){
            if(sas[i].size() == 2) // dla tych wierzcholkow, z ktorych biegna 2 krawedzie i nie da sie ustalic, ktora wziac
                z_ilu_dwie++;
            else if(sas[i].size() == 0 && !czapki_czy_ust[czapki[i]]){
                czy_beda = false;
                break;
            }
            if(!miejsca_czy_ust[i]){ // dla nieustawionych
                if(odwr_sas[i].size() == 0) // do ktorych nie prowadza zadne krawedzie
                    ile_dowolnych++;
                else // do ktorych prowadza jakies krawedzie
                    do_ilu_dod++;
            }
        }

        for(int i=0, x = ile_dowolnych + (do_ilu_dod - z_ilu_dwie); i<x; ++i) // liczenie silni
            wynik = (wynik * (i+1)) % MOD;

        // podnoszenie do potegi (przyspieszone)
        const int POT = 30;
        for(int i=z_ilu_dwie; i>0; i-=POT){
            (i >= POT) ? wynik = (wynik << POT)%MOD : wynik = (wynik << i)%MOD;
        }

        if(czy_beda)
            cout << wynik << '\n';
        else cout << 0 << '\n';
    }
    else
        cout << 0 << '\n';
}
