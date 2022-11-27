#include <iostream>

using namespace std;

int n,a,b,c;

bool CzyJedenRuch()
{
    if((a<c && c<b) || (c<a && a<b)) swap(b,c);
    else if(b<a && a<c) swap(a,b);
    else if(b<c && c<a){
        swap(a,b);
        swap(c,a);
    }
    else if(c<b && b<a) swap(a,c);

    if((c-b==1) && (b-a==1)) return 1;
    else if((a==0) && (c==n-1) && (b==1 || b==n-2)) return 1;
    else return 0;
}

int main()
{
    cin>>n;
    cin>>a>>b>>c;

    if(CzyJedenRuch()) cout<<"TAK"<<endl;
    else if(n%2==0) cout<<"TAK"<<endl;
    else cout<<"NIE"<<endl;
    return 0;
}
