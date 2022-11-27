#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e5, MOD = 1e9 + 7;
int n;
vector<int> czapki(N_MAX), // wejscie
        czap_wyst(N_MAX); // ile razy dana czapka wystapila wczesniej
vector<vector<int>> sas(N_MAX), odwr_sas(N_MAX); // sasiedzi (od narzucajacych - czyli ci, ktorym dany wierzcholek narzuca) i odwrotni sasiedzi (ci, ktorzy narzucaja danemu wierzcholkowi)
vector<bool> czapki_czy_ust(N_MAX), // czy dana czapka jest przypisana do konkretnego miejsca
        miejsca_czy_ust(N_MAX); // czy dane miejsce ma przypisana czapke
queue<int> rozw_wierz; // wierzcholki do rozwazenia
int wol_czap; // wolne czapki - czyli te, ktore nie beda chcialy byc nigdzie ustawione
long long wynik = 1;

void ustaw(int miejsce, int czapka)
{
    czapki_czy_ust[czapka] = true;
    miejsca_czy_ust[miejsce] = true;
}

void przejdz(int x_miej) // x_miej - pewne miejsce
{
    if(sas[x_miej].size() == 1){
        ustaw(sas[x_miej][0], czapki[x_miej]);
        int x_miej_2 = sas[x_miej][0]; // nastepnik (sasiad) x miejsce

        // usuwanie polaczen
        sas[x_miej].pop_back();
        if(odwr_sas[x_miej_2].size() == 2){ // jesli jest dwoch ktorzy chca ustawic swojego w danym miejscu, to usun tego drugiego (a zatem zarazem obu, bo pierwszy jest usuwany pozniej)
            int x_miej_3; // odwrotny sasiad sasiada x_miej
            if(odwr_sas[x_miej_2][0] == x_miej) // jesli pierwszy z dwoch jest tym, z ktorego przyszlo sie
                x_miej_3 = odwr_sas[x_miej_2][1];
            else x_miej_3 = odwr_sas[x_miej_2][0];
            odwr_sas[x_miej_2].pop_back();

            // usuwanie krawedzi od x_miej_3 do x_miej_2
            if(sas[x_miej_3].size() == 2 && sas[x_miej_3][0] == x_miej_2){
                swap(sas[x_miej_3][0], sas[x_miej_3][1]);
            }
            sas[x_miej_3].pop_back();
            rozw_wierz.push(x_miej_3); // pushuj zarowno kiedy sas[x_miej_3].size() rowne jest 2 jak i 1, gdyz jesli bedzie rowne 2 to ustawi sie w to drugie miejsce (jesli nadal bedzie dostepne),
                // a jesli bedzie rowne 1 to nie bedzie gdzie ustawic i bedzie trzeba zwrocic 0
        }
        odwr_sas[x_miej_2].pop_back();
    }
    else
        wynik = 0;
}

void zlicz() // zliczanie wszystkich przypadkow
{
    if(wynik == 0) // jesli juz na wejsciu wiadomo, ze zadnych przypadkow nie bedzie
        return;

    vector<int> parz, n_parz; // wierzcholki do ktorych wchodzi jedna krawedz i ich indeksy sa: parz - parzyste, n_parz - nieparzyste
    for(int i=0; i<n; ++i){
        if(sas[i].size() == 0 && !czapki_czy_ust[czapki[i]]){ // jesli dana czapka jest nieustawiona i nie moze byc ustawiona
            wynik = 0;
            return;
        }

        if(odwr_sas[i].size() == 1) // jesli skrajny
            (i%2 == 0) ? parz.push_back(i) : n_parz.push_back(i);
    }

    for(int i=0, x=parz.size(); i<x; i+=2) // liczenie ilosci wierzcholkow nalezacych do kazdej skladowej i aktualizowanie o nia wyniku - dla parzystych indeksow
        wynik = (wynik * ((parz[i+1] - parz[i])/2 + 1)) % MOD;
    for(int i=0, x=n_parz.size(); i<x; i+=2) // to samo dla nieparzystych indeksow
        wynik = (wynik * ((n_parz[i+1] - n_parz[i])/2 + 1)) % MOD;

    //liczenie silni z ilosci wolnych czapek
    for(int i=0; i<wol_czap; ++i)
        wynik = (wynik * (i+1)) % MOD;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    wol_czap = n;
    for(int i=0; i<n; ++i){
        cin >> czapki[i];
        czap_wyst[czapki[i]]++;

        if(czap_wyst[czapki[i]] > 2){ // wiecej niz 2 wystapienia danej czapki - niemozliwe
            wynik = 0;
            break;
        }
        else if(czap_wyst[czapki[i]] == 2){ // dla podwojnych wystapien
            if(i>=2 && czapki[i-2] == czapki[i]){
                ustaw(i-1, czapki[i]);
            }
            else{
                wynik = 0;
                break;
            }
        }
        else if(czap_wyst[czapki[i]] == 1) // dla pojedynczych (przynajmniej poki co) wystapien
            wol_czap--;
    }

    // ustawianie skrajnych
    if(!miejsca_czy_ust[1]) // pierwszego
        ustaw(1, czapki[0]);

    if(!miejsca_czy_ust[n-2]) // drugiego
        ustaw(n-2, czapki[n-1]);
    else if(n-1 == 1 && czapki[n-1] != czapki[0]) // jesli miejsce, w ktore chcemy ustawic dla pierwszego skrajnego jest to samo co dla drugiego, a chca one narzucic rozne czapki
        wynik = 0;

    // tworzenie grafu
    for(int i=1; i<n-1; ++i){
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
            else if(sas[i].size() == 0){ // jesli nie ma gdzie ustawic
                wynik = 0;
                break;
            }
        }
    }

    // przechodzenie grafu
    while(!rozw_wierz.empty() && wynik != 0){
        przejdz(rozw_wierz.front());
        rozw_wierz.pop();
    }

    zlicz();
    cout << wynik << '\n';
}
