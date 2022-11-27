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

    int n,X,z,k,m,p,i,j;
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

    int Pozycja[n];//pozycja bez klikania dla danej platformy
    p=X-1;//ogranicznik z lewej strony do ktorej pozycji (szukac dziury na wyzszej platformie)
    m=-1;//dziura na platformie wyzej
    for(i=n-1; i>=0; i--){//szukanie najdalszej pozycji dla ktorej mozna zejsc bez klikania niczego
        if(Dziury[i].size()==2){//jesli nie ma zadnych dziur na platformie
            Pozycja[i]=0;
            continue;
        }
        for(j=Dziury[i].size()-2; j>=0; j--){//wyznaczanie dziury na obecnej platformie
            if(Dziury[i][j]<p){
                k=Dziury[i][j];//k- dziura na obecnej platformie
                Pozycja[i]=k+1;
                break;
            }
        }

        for(j=Dziury[i-1].size()-2; j>=0; j--){//szukanie dziury na platformie wyzej o numerze pomiedzy dziura na obecnej platformie a poprzednia dziura
            if(Dziury[i-1][j]<k){//jesli jest za dziura na obecnej platformie
                break;//przerwij
            }
            else if(Dziury[i-1][j]<p){//jesli jest za poprzednia dziura
                m=Dziury[i-1][j];
            }
        }
        if(m==-1) p=X-1;//jesli nie ma zadnej dziury na platformie
        else p=m;
    }
    for(i=0; i<n; i++) cout<<Pozycja[i]<<" ";
    cout<<endl;

    int IleSkokow,DziuraWyzej;
    while(z--){//zapytania
        cin>>p;//o jaka platforme jest zapytanie
        p--;//numeracja od 0
        if(Pozycja[p]==0 || Dziury[p].size()==1){//jesli nie trzeba skakac
            cout<<"0\n";
            continue;
        }
        IleSkokow=DziuraWyzej=0;
        m=0; k=1;//m- lewy koniec przedzialu przeszukiwanego, k- prawy koniec przedzialu przeszukiwanego
        while(Dziury[p][k]<Pozycja[p]){//dopoki nie mozna po prostu zejsc w dol
            for(i=1; i<Dziury[p-1].size(); i++){//dopoki nr dziury jest nieodpowiedni
                if(Dziury[p-1][i]>Dziury[p][m] && Dziury[p-1][i]<Dziury[p][k]){//jesli dziura na platformie wyzej miesci sie w przedziale
                    DziuraWyzej=i;//zapisz jej numer w zmiennej
                }
                else if(Dziury[p-1][i]>Dziury[p][k] && DziuraWyzej!=0){//jesli wykroczylo poza zakres, a istnieje dziura wyzej mieszczaca sie w przedziale (wskocz przez ta dziure wyzej)
                    m=DziuraWyzej;//lewa granica- poprzednia dziura (ta, ktora sie weszlo na dana platforme)
                    k=DziuraWyzej+1;//prawa granica- nastepna dziura
                    IleSkokow++;
                    p--;//mniejszy numer platformy
                    break;
                }
                else if(Dziury[p-1][i]>Dziury[p][k]){//jesli wykroczylo poza zakres i nie istnieje dziura wyzej mieszczaca sie w przedziale (przeskocz dziure na obecnej platformie)
                    m=k;//lewa granica- poprzednia dziura (ta przeskoczona)
                    k++;//prawa granica- nastepna dziura
                    IleSkokow++;
                    break;
                }
            }
        }
        cout<<IleSkokow<<"\n";
    }
}
