#include <iostream>

using namespace std;

//funkcja rozkladajaca S na ciag jedynkowy i go wypisujaca
void Rozloz(int n,int S)
{
    int A[n+1],i,x=n+1;
    for(i=0; i<x; i++) A[i]=0;
    while(S>0){
        if(S>=n){
            A[x-n]=1;
            S-=n;
        }
        n--;
    }
    for(i=1; i<x; i++){
        if(A[i]==1) A[i]=A[i-1]+1;
        else A[i]=A[i-1]-1;
    }
    for(i=0; i<x; i++) cout<<A[i]<<endl;
}

int main()
{
    int n,S,Sn1=1,i;
    cin>>n>>S;
    for(i=2; i<n; i++) Sn1+=i;

    //przypadek graniczny
    if(n==1){
        cout<<"0"<<endl;
        return 0;

    }

    //sprawdzenie parzystosci i czy S nalezy do dopuszczalnego przedzialu
    if((S+Sn1)%2==1 || S>Sn1 || S<(-Sn1)){
        cout<<"NIE"<<endl;
        return 0;
    }

    Rozloz(n-1,(S+Sn1)/2);
    return 0;
}
