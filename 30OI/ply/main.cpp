/*
    Martyna Budrewicz
    Uniwersyteckie Liceum Ogolnoksztalcace
    87-100 Torun
*/
#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6 + 1;
int n, m_gle;
string naw;

int wy = 0;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m_gle;
    cin >> naw;

    stack<int> miej;
    for(int i=0; i<n; ++i){
        if(miej.size() == 0){
            if(naw[i] == ')')
                wy++;
            miej.push(i);
        } else{
            if(naw[i] == '('){
                if((int)miej.size() == m_gle){
                    wy++;
                    miej.pop();
                } else{
                    miej.push(i);
                }
            } else{
                miej.pop();
            }
        }
    }
    cout << wy + (int)miej.size()/2 << '\n';
}
