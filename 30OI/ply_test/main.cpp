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

    // oficjalne
    //ifstream wej("C:\\Users\\marti\\Downloads\\ocen-win\\ocen-win\\in\\ply1.in");
    //ifstream wyj("C:\\Users\\marti\\Downloads\\ocen-win\\ocen-win\\out\\ply1.out");

    // do testow z forum
    ifstream wej("C:\\Users\\marti\\Downloads\\ply_testy\\PLY\\ply888.in");
    ifstream wyj("C:\\Users\\marti\\Downloads\\ply_testy\\PLY\\ply888.out");


    wej >> n >> m_gle;
    wej >> naw;

    int exp_val; // expected outcome value
    wyj >> exp_val;

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
    //cout << wy + (int)miej.size()/2 << ' ';
    cout << (wy + (int)miej.size()/2 == exp_val ? "YES" : "NO")<< '\n';
}
