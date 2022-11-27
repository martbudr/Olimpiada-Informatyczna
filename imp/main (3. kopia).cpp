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

void ustaw(int miejsce, int nr_czapki) // ustawianie danej czapki w okreslone miejsce
{
    if(!czapki_czy_ust[nr_czapki]){
        miejsca_czy_ust[miejsce] = true;
        czapki_czy_ust[nr_czapki] = true;
        niewyk_czapki--;
    }
}

void przejdz(int x_miej) // x_miej - pewne miejsce
{
    if(sas[x_miej].size() == 1){
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

            przejdz(x_miej_3);
        }

        odwr_sas[x_miej_2].pop_back();
        sas[x_miej].pop_back();
    }
}

int main(void) // indeksowanie od 0
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    niewyk_czapki = n;
    for(int i=0; i<n; ++i){
        cin >> czapki[i];

        // sprawdzanie, czy mozliwe
        if(il_wyst_czapki[czapki[i]] > 1){ // jesli wczesniejsza ilosc wystapien czapki juz byla wieksza od 1
            cout << 0 << '\n';
            return 0;
        }
        else if(il_wyst_czapki[czapki[i]] == 1){
            if(i >= 2 && czapki[i-2] == czapki[i]) // ustawianie juz na gotowo czapki czapki[i] na miejsce i-1 (dla np. ... 3 2 3 ...)
                ustaw(i-1, czapki[i]);
            else{
                cout << 0 << '\n';
                return 0;
            }
        }
        il_wyst_czapki[czapki[i]]++;
    }

    // ustawianie dla skrajnych
    ustaw(1, czapki[0]);
    ustaw(n-2, czapki[n-1]);
    // tworzenie grafu
    for(int i=1; i<n; ++i){
        if(!czapki_czy_ust[czapki[i]]){ // jesli dana czapka nie jest ustawiona
            if(miejsca_czy_ust[i-1] && miejsca_czy_ust[i+1]){ /// i nie ma gdzie jej ustawic - czy aby na pewno tutaj powinno byc?
                cout << 0 << '\n';
                return 0;
            }

            // jesli jest gdzie ja ustawic
            if(!miejsca_czy_ust[i-1]){
                sas[i].push_back(i-1);
                odwr_sas[i-1].push_back(i);
            }
            if(!miejsca_czy_ust[i+1]){
                sas[i].push_back(i+1);
                odwr_sas[i+1].push_back(i);
            }
        }
    }

    // przechodzenie grafu
    for(int i=1; i<n; ++i)
        przejdz(i);

    // policzyc ilosc przypadkow z pozostalych wolnych
    // zliczanie nieustawionych wierzcholkow
    int ile_nieustawionych = 0;
    for(int i=0; i<n; ++i){
        if(!miejsca_czy_ust[i])
            ile_nieustawionych++;
    }

    for(int i=0; i<n; ++i)
        cout << miejsca_czy_ust[i] << ' ';
    cout << '\n';

    // liczenie wyniku
    // wynik = 2 ^ (ile_nieustawionych-1) (jesli ile_nieustawionych > 0)
    long long wynik = 1;
    int pot = 30; // duza potega uzywana w petli
    for(int i=ile_nieustawionych; i>0; i-=pot){
        if((i-1) >= pot)
            wynik = (wynik * (1 << pot)) % MOD; // modulo jakas duza potega dwojki (ale na tyle mala, aby miescila sie w incie lub long longu z pozostawionym miejscem) jesli taka pozostala
        else wynik = (wynik * (1 << (i-1))) % MOD; // albo pozostalosc z ile_nieustawionych jesli nie
    }

    cout << wynik << '\n';
}
