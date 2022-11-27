/*
Martyna Budrewicz
Uniwersyteckie Liceum Ogolnoksztalcace
ul. Szosa Chelminska 83
87-100 Torun
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n,m,z,i;
int *F,*H;//F[n]- tablica wartosci tablicy najkrotszych drog, H[n]- tablica krawedzi prowadzacych do danego wierzcholka
vector<int>*Sasiedzi,*CoDoSasiadow;//CoDoSasiadow- numer krawedzi prowadzacej do sasiada

void NajkrotszeSciezki(int x)
{
    int L[n];//czy odwiedzone
    for(i=0; i<n; i++) L[i]=0;
    queue<int>Q;
    Q.push(x);
    L[x]=1;
    F[x]=-1; H[x]=0;
    while(!Q.empty()){
        x=Q.front();
        Q.pop();
        for(i=0; i<Sasiedzi[x].size(); i++){
            if(!L[Sasiedzi[x][i]]){
                Q.push(Sasiedzi[x][i]);
                F[Sasiedzi[x][i]]=x;///dodane 1 do wypisywania, nie wiem, czy tak normalnie jest potrzebne, chociaz tak normalnie po skonczeniu obliczen to wlasnie te wartosci powinny wystepowac (usuniete)
                H[Sasiedzi[x][i]]=CoDoSasiadow[x][i];///jak powyzej (usuniete)
                L[Sasiedzi[x][i]]=1;
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>z;
    Sasiedzi= new vector<int>[n];
    CoDoSasiadow= new vector<int>[n];
    int Biciak[n];//biciak bedacy do kupienia w stacji na drodze o numerze i
    int a,b,c,x;//x- wartosc wczytywana w 2-giej czesci programu
    Biciak[0]=0;
    for(i=1; i<n; i++){
        cin>>a>>b>>c;
        Sasiedzi[a-1].push_back(b-1);
        CoDoSasiadow[a-1].push_back(i);
        Sasiedzi[b-1].push_back(a-1);
        CoDoSasiadow[b-1].push_back(i);
        Biciak[i]=c;
    }
    F=new int[n];
    H=new int[n];
    NajkrotszeSciezki(0);
    delete[]Sasiedzi;
    delete[]CoDoSasiadow;
    //for(i=0; i<n; i++) cout<<Biciak[H[i]]<<" ";///usunac
    //cout<<endl;///usunac

    ///jaka struktura danych jest w stanie pomiescic mi biciaki lezace na danej drodze dla wszystkich drog? chyba zadna
    ///wypisywanie i zmiana
    char lit;//litera wczytywana
    int JakieDoMiasta[n],s;
    while(z--){
        cin>>lit;
        if(lit=='B'){//zmiana biciaka na stacji
            cin>>x>>c;//zmiana biciaka na drodze przy x-tej stacji na biciaka nr c
            if(c!=Biciak[x]){
                Biciak[x]=c;
            }
        }
        else{//ile biciakow po drodze na jakas stacje
            cin>>x;//miasto, do ktorego sprawdzana jest ilosc biciakow
            for(i=0; i<n; i++) JakieDoMiasta[i]=0;
            s=0;
            x--;
            while(F[x]!=-1){
                JakieDoMiasta[Biciak[H[x]]]++;
                x=F[x];
            }
            for(i=0; i<n; i++){
                if(JakieDoMiasta[i]!=0) s++;
            }
            cout<<s<<"\n";
        }
    }
}
