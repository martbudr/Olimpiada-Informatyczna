/*
Martyna Budrewicz
Uniwersyteckie Liceum Ogolnoksztalcace
ul. Szosa Chelminska 83
87-100 Torun
*/

#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,X,z,k,p,i,j;
    cin>>n>>X>>z;//liczba platform, dlugosc platform, liczba zapytan
    vector<int>Dziury[n];
    for(i=0; i<n; i++){//wczytywanie dziur
        Dziury[i].push_back(-1);//1-sza dziura na kazdej platformie- -1
        cin>>k;//ile dziur na danej platformie
        while(k--){//wczytanie numerow miejsc gdzie wystepuja dziury (-1 jako ze zaczynam numerowanie od 0)
            cin>>p;
            Dziury[i].push_back(p-1);
        }
        Dziury[i].push_back(X-1);//koncowa dziura (za platforma)
    }

    int Pozycja[n],DzPoPrawej=Dziury[n-1].size()-1,DzPoLewej,CzyZmienione;//Pozycja[]- pozycja dla danej platformy bez klikania, DzPoPrawej,DzPoLewej- ograniczniki z prawej i lewej strony, CzyZmienione- czy DzPoPrawej zmienione podczas ewentualnego pojscia w gore
    for(i=n-1; i>=0; i--){//szukanie najdalszej pozycji dla ktorej mozna zejsc bez klikania niczego
        CzyZmienione=0;//zerowanie czy zmienione
        DzPoLewej=DzPoPrawej-1;
        Pozycja[i]=Dziury[i][DzPoLewej]+1;

        for(j=0; j<Dziury[i-1].size()-1; j++){//szukanie dziury na platformie wyzej o numerze pomiedzy dziura na obecnej platformie a poprzednia dziura
            if(Dziury[i-1][j]>Dziury[i][DzPoLewej] && Dziury[i-1][j]<Dziury[i][DzPoPrawej]){//jesli jest w przedziale
                DzPoPrawej=j;//ustawienie j jako nowej prawej dziury
                CzyZmienione=1;
                break;
            }
            else if(Dziury[i-1][j]>Dziury[i][DzPoPrawej])
                break;
        }
        if(!CzyZmienione)//jesli nie ma dziury na platformie wyzej o numerze nalezacym do przedzialu
            DzPoPrawej=Dziury[i-1].size()-1;
    }

    int IleSkokow;
    while(z--){//zapytania
        cin>>p;//o jaka platforme jest zapytanie
        p--;//numeracja od 0

        IleSkokow=0;
        DzPoLewej=0; DzPoPrawej=1;
        while(Dziury[p][DzPoPrawej]<Pozycja[p]){//dopoki nie mozna po prostu zejsc w dol
            CzyZmienione=0;//zerowanie czy zmienione
            for(i=1; i<Dziury[p-1].size(); i++){//dopoki nr dziury jest nieodpowiedni
                if(Dziury[p-1][i]>Dziury[p][DzPoLewej] && Dziury[p-1][i]<Dziury[p][DzPoPrawej]){//jesli dziura na platformie wyzej miesci sie w przedziale
                    DzPoLewej=i;//zapisz jej numer w zmiennej
                    p--;//przejscie na nastepna platforme
                    IleSkokow++;
                    CzyZmienione=1;
                }
                else if(Dziury[p-1][i]>Dziury[p][DzPoPrawej])//jesli jest za przedzialem
                    break;
            }
            if(!CzyZmienione){//jesli nie ma dziury wyzej mieszczacej sie w przedziale
                DzPoLewej=DzPoPrawej;
                IleSkokow++;
            }
            DzPoPrawej=DzPoLewej+1;
        }
        cout<<IleSkokow<<"\n";
    }
}
