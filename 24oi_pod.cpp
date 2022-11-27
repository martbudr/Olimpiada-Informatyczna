#include <iostream>
#include <vector>

using namespace std;

int wyszBin(long long nr_cyfry, int zakres, vector<long long>& ile_do_kazdej) // szukanie pierwszej wiekszej od szukanej cyfry (dzieki temu znajdziemy, jaka to jest cyfra)
{
    int lewy=0, prawy=zakres, mid;
    while(lewy < prawy){
        mid = (lewy + prawy)/2;
        if(ile_do_kazdej[mid] > nr_cyfry) // jesli warunek jest spelniony
            prawy = mid; // w przeciwnym razie zmien prawy i szukaj w nizszych
        else lewy = mid + 1; // zmien lewy i szukaj w wyzszych
    }
    if(ile_do_kazdej[lewy] <= nr_cyfry) return -1;
    return lewy;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int podst_systemu, l_zapytan; // podstawa systemu
    cin >> podst_systemu >> l_zapytan;

    vector<int> ile_ktorej(podst_systemu);
    for(int i=0; i<podst_systemu; ++i)
        cin >> ile_ktorej[i];

    // liczenie sumy wszystkich, aby dowiedziec sie, ile nalezy odjac (jaka liczbe usunac)
    long long suma_wszystkich_mozliwych = 0;
    for(int i=0; i<podst_systemu; ++i){
        suma_wszystkich_mozliwych += ile_ktorej[i]*i; // i odpowiada kazdej liczbie po kolei
    }
    if(suma_wszystkich_mozliwych % (podst_systemu-1) != 0) // jesli ze wszystkimi cyframi nie dzieli sie przez podstawe systemu-1
        --ile_ktorej[suma_wszystkich_mozliwych%(podst_systemu-1)]; // usunac reszte z dzielenia (to naprawi problem niepodzielnosci)

    // ile_do_kazdej przetrzymuje wiadomosc o tym, ile liczb jest do pewnego momentu
    // (np. ile_ktorej[3] przetrzymuje ile jest liczb od 0 do 3 wlacznie)
    vector<long long> ile_do_kazdej(podst_systemu);
    ile_do_kazdej[0] = ile_ktorej[0];
    for(int i=1; i<podst_systemu; ++i)
        ile_do_kazdej[i] = ile_do_kazdej[i-1] + ile_ktorej[i];

    // wczytuj cyfry po kolei i wyszukuj binarnie ich pozycje
    long long nr_cyfry;
    for(int i=0; i<l_zapytan; ++i){
        cin >> nr_cyfry;
        cout << wyszBin(nr_cyfry, podst_systemu-1, ile_do_kazdej) << '\n';
    }
}
