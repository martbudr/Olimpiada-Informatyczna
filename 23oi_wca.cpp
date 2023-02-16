#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 5e5 + 1;
int n;
int k;
long long ans = 0;

int len(int k)
{
    return log2(k)+1;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    priority_queue<int> Q;
    for(int i=0; i<n; ++i){
        cin >> k;
        k *= 2;

        int x = len(k);
        int ones_amt = 0;
        for(int j=x-1; j>=0; --j){
            if(k & (1<<j))
                ones_amt++;
            else break;
        }
        ans += 2*(x-ones_amt-1);
        Q.push((1<<(ones_amt+1)) - 2);
    }

    bool A_turn = true;
    while(!Q.empty()){
        int curr = Q.top();
        Q.pop();

        if(A_turn){
            ans += 2*(len(curr)-1) + 1;
            A_turn = false;
        }
        else if(curr == 2){
            ans += 2;
            A_turn = false;
        }
        else{
            ans += 3;
            A_turn = true;
            Q.push(curr/2 - 1);
        }
    }

    cout << ans << '\n';
}
