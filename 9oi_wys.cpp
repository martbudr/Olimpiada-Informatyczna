#include <iostream>

using namespace std;

int n,A=0,rekord,i,s,x,y,pol_obwodu,t;//s- dlugosc drogi zgodnie ze wskazowkami zegara

int Odleglosc(int *D)
{
    rekord=A;
    s=0;
    x=0; y=0;
    pol_obwodu=A/2;
    while(y<n){
        if(s<pol_obwodu){
            s+=D[y];
            y++;
        }
        else{
            s-=D[x];
            x++;
        }
        t=pol_obwodu-s;
        if(t<0) t*=(-1);
        if(t<rekord) rekord=t;
    }
    return pol_obwodu-rekord;
}

int main()
{
    cin>>n;
    int D[n];
    for(i=0; i<n; i++){
        cin>>D[i];
        A+=D[i];
    }

    cout<<Odleglosc(D)<<endl;
    return 0;
}
