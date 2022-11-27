#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n,i,x,y,j;
    cin>>n;
    int a[2*n];
    for(i=0; i<2*n; i++) cin>>a[i];

    vector<int>D,S,Z;
    for(i=2*n-1; i>=0; i--) S.push_back(a[i]);
    int K[n+1];
    for(i=1; i<=n; i++) K[i]=0;

    while(!S.empty()){
        x=S.back();
        S.pop_back();
        if(K[x]==0){
            D.push_back(x);
            K[x]++;
        }
        else{
            j=D.size();
            y=D.back();
            D.pop_back();
            K[y]--;
            if(x!=y){
                Z.push_back(j);
                S.push_back(y);
                S.push_back(x);
            }
        }
    }

    cout<<Z.size()<<endl;
    for(i=0; i<Z.size(); i++) cout<<Z[i]<<endl;
    return 0;
}
