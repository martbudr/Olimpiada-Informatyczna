#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n,i,s;
    char MINUS='-',OTW='(',ZAMKN=')';
    vector<char>Wyjscie;
    cin>>n;
    char Znak[n-1];
    cin>>Znak[0]; //czytanie pierwszego znaku, ale bez sprawdzania czy jest minusem, bo musi nim byc
    for(i=1; i<n-1; i++){ //czytanie reszty znakow
        cin>>Znak[i];
        Wyjscie.push_back(MINUS);
        if(Znak[i-1]=='-' && Znak[i]=='+'){
            Wyjscie.push_back(OTW);
        }
        else if(Znak[i-1]=='+' && Znak[i]=='-'){
            Wyjscie.push_back(ZAMKN);
        }
    }
    Wyjscie.push_back(MINUS);
    if(Znak[--i]=='+'){
        Wyjscie.push_back(ZAMKN);
    }

    s=Wyjscie.size();
    for(i=0; i<s; i++){
        cout<<Wyjscie[i];
    }
    cout<<endl;
    return 0;
}
