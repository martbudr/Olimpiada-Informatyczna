#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    const int MAX_ILOSC=45;
    int m=0,x=1,i;//licznik wartosci, zmienna do wczytywania
    vector<int>W;
    while(x){
        if(m>MAX_ILOSC){
            break;
        }
        cin>>x;
        W.push_back(x);
        m++;
    }

    sort(W.begin(),W.end());
    for(i=2; i<m; i++){
        if(W[i-2]+W[i-1]>W[i]){
            cout<<W[i-2]<<" "<<W[i-1]<<" "<<W[i]<<"\n";
            return 0;
        }
    }
    cout<<"NIE\n";
    return 0;
}
