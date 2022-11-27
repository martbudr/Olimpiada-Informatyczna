/*
Martyna Budrewicz
Uniwersyteckie Liceum Ogolnoksztalcace
ul. Szosa Chelminska 83
87-100 Torun
*/

#include <iostream>

using namespace std;

short LRODZ=3;
int n,i,j;
long long s=0;
int *IleKazdego;
long long **Gabloty;

void Szukaj(int a)//szukanie dwoch najmniejszych wartosci; a-kolumna, l-lewa wartosc, p-prawa wartosc
{
    int min1,min2;//2 najmniejsze wartosci w kolumnie; min1<=min2
    if(Gabloty[0][a]<=Gabloty[1][a]){
        min1=Gabloty[0][a]; min2=Gabloty[1][a];
    }
    else{
        min1=Gabloty[1][a]; min2=Gabloty[0][a];
    }
    for(i=2; i<n; i++){
        if(Gabloty[i][a]<min2){
            if(Gabloty[i][a]<min1){
                min2=min1;
                min1=Gabloty[i][a];
            }
            else min2=Gabloty[i][a];
        }
    }
    s+=min1+min2;
}

void Wybieranie(int a,int b,int c)//a,b- gabloty z najmniejszymi wartosciami, c- gablota z najwieksza wartoscia
{
    if(IleKazdego[a]<n-1){//jesli liczba w kolumnie jest mniejsza od dozwolonej
        s+=Gabloty[i][a];
        if(Gabloty[i][a]) IleKazdego[a]++;
        if(IleKazdego[b]<n-1){//jesli liczba w kolumnie jest mniejsza od maksymalnej dozwolonej
            s+=Gabloty[i][b];
            if(Gabloty[i][b]) IleKazdego[b]++;
        }
        else{
            s+=Gabloty[i][c];
            if(Gabloty[i][c]) IleKazdego[c]++;
        }
    }
    else if(IleKazdego[b]<n-1 && IleKazdego[c]<n-1){//jesli liczba w rozpatrywanej kolumnie jest rowna dozwolonej, ale w pozostalych kolumnach jest mniejsza
        s+=Gabloty[i][b]+Gabloty[i][c];
        if(Gabloty[i][b]) IleKazdego[b]++;
        if(Gabloty[i][c]) IleKazdego[c]++;
    }
    else if(IleKazdego[b]<n-1){//jesli liczba zarowno w rozpatrywanej, jak i w 1-szej z pozostalych kolumnie jest rowna dozwolonej, to przejdz przez 2-ga kolumne, znajdz najmniejsze 2 wartosci ktore w niej sa i dodaj je do sumy
        Szukaj(b);//szukanie najmniejszej wartosci w kolumnie b
    }
    else{//jesli liczba zarowno w rozpatrywanej, jak i w 2-giej z pozostalych kolumnie jest rowna dozwolonej, to przejdz przez 1-sza kolumne, znajdz najmniejsze 2 wartosci ktore w niej sa i dodaj je do sumy
        Szukaj(c);//szukanie najmniejszej wartosci w kolumnie c
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    Gabloty=new long long*[n];
    for(i=0; i<n; i++) Gabloty[i]=new long long[LRODZ];
    for(i=0; i<n; i++){
        for(j=0; j<LRODZ; j++) cin>>Gabloty[i][j];
    }
    IleKazdego=new int[LRODZ];
    for(i=0; i<LRODZ; i++) IleKazdego[i]=0;

    for(i=0; i<n; i++){
        if(Gabloty[i][0]<=Gabloty[i][1]){//porownanie wartosci w celu znalezienia dwoch najmniejszych (nie sa posortowane- pierwsza przekazywana do funkcji potrafi byc wieksza od drugiej)
            if(Gabloty[i][1]<=Gabloty[i][2])
                Wybieranie(0,1,2);
            else Wybieranie(0,2,1);
        }
        else{
            if(Gabloty[i][0]<=Gabloty[i][2])
                Wybieranie(1,0,2);
            else Wybieranie(1,2,0);
        }
    }
    cout<<s<<"\n";
    for(i=0; i<LRODZ; i++) delete[]Gabloty[i];
    delete[]IleKazdego;
}
