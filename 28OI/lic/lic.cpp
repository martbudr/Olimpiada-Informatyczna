/*
Martyna Budrewicz
Uniwersyteckie Liceum Ogolnoksztalcace
ul. Szosa Chelminska 83
87-100 Torun
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

short Potega(short x)
{
    switch(x){
    case 0:
        return 1;
    case 1:
        return 10;
    case 2:
        return 100;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,z,i,a,c=0;
    cin>>n>>z;
    string wew,zew;//dlugi wewnetrzny i zewnetrzny
    cin>>wew>>zew;
    vector<short>W,Z,S;
    //zamienienie stringow na klase vector<short> zawierajaca liczby pogrupowane po 3 cyfry (chociaz moze lepiej jednak zrobic po 4...?)
    for(i=n-2; i>=0; i-=3){
        if((i+1)/3>0 || (i+1)%3==0)//kiedy wiecej niz 1 liczba do dodania do wektora lub liczba jest trzycyfrowa
            W.push_back(100*(wew[i-2]-'0')+10*(wew[i-1]-'0')+wew[i]-'0');
        else if((i+1)%3==2)//kiedy liczba jest dwucyfrowa
            W.push_back(10*(wew[i-1]-'0')+wew[i]-'0');
        else//kiedy liczba jest jednocyfrowa
            W.push_back(wew[i]-'0');
    }
    for(i=n-2; i>=0; i-=3){
        if((i+1)/3>0 || (i+1)%3==0)
            Z.push_back(100*(zew[i-2]-'0')+10*(zew[i-1]-'0')+zew[i]-'0');
        else if((i+1)%3==2)
            Z.push_back(10*(zew[i-1]-'0')+zew[i]-'0');
        else
            Z.push_back(zew[i]-'0');
    }

    ///zapytania
    char lit;
    int x;
    bool su=0;//czy bylo ostatnio sumowane(1) czy zmieniane(0)
    while(z--){
        cin>>lit>>x;
        switch(lit){
        case 'W'://zmiana x-tej cyfry dlugu wewnetrznego na c
            cin>>c;
            a=(W[(x-1)/3]/Potega((x-1)%3))%10;//liczba na pozycji liczby zmienianej
            if(a!=c){//jesli liczba na jaka mam zmienic jest rozna od juz bedacej na miejscu
                W[(x-1)/3]+=(c-a)*Potega((x-1)%3);//zamiana cyfry
            }
            su=0;
            break;
        case 'Z':
            cin>>c;
            a=(Z[(x-1)/3]/Potega((x-1)%3))%10;
            if(a!=c){
                Z[(x-1)/3]+=(c-a)*Potega((x-1)%3);
            }
            su=0;
            break;
        default://wypisanie x-tej cyfry sumarycznego ciagu
            if(!su){//jesli ostatnio bylo zmieniane
                S.clear();
                c=0;
                for(i=0; i<n/3+1; i++){
                    S.push_back((W[i]+Z[i]+c)%1000);
                    c=(W[i]+Z[i]+c)/1000;
                }
            }
            cout<<(S[(x-1)/3]/Potega((x-1)%3))%10<<"\n";
            su=1;
            break;
        }
    }
}
