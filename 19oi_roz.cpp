#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int p,r,i=1;
    long long k;
    long long fib[100];
    fib[0]=0;
    fib[1]=1;
    cin>>p;
    while(p--){
        cin>>k;
        while(fib[i]<=k){
            fib[i+1]=fib[i]+fib[i-1];
            i++;
        }
        r=0;
        while(k>0){
            if(k-fib[i-1]<=fib[i]-k) k-=fib[i-1];
            else k=fib[i]-k;
            r++;
            while(fib[i-1]>k) i--;
        }
        cout<<r<<'\n';
    }
    return 0;
}
