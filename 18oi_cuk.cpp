#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    const int wypieki=3;
    int n,i,j;
    cin>>n;
    int gabloty[n][wypieki], maximum[i];//gabloty[][0]- drozdzowki, gabloty[][1]- paczki, gabloty[][2]- rogaliki
    long long koszt=0;

    for(i=0; i<n; i++){//(1)wczytywanie, (2)obliczanie kosztu i (3)ustawianie maximow
        for(j=1; j<=wypieki; j++){
            cin>>gabloty[i][j];//(1)
            koszt+=gabloty[i][j];//(2)
        }
        maximum[i]=maks_wartosc(gabloty,i);//(3)
        koszt-=maximum[i];//(2)
    }

    int koszty[n][wypieki];
    for(i=0; i<n; i++){
        for(j=1; j<=3; j++) koszty[i][wypieki]=maximum[i]-gabloty[i][j];
    }

    for(i=0; i<n; i++){///obliczanie najmniejszych

    }
    ///dodac te cosie z potrojnej petli

    //vector<pair<int,int>> ;
}
