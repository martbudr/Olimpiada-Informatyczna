#include <iostream>
#include <vector>

using namespace std;

bool possible() {
    
    return true;
}

void printOtherTwo(vector<int>& levels, int n) {
    if (!possible()) {
        cout << "NIE" << '\n';
        return;
    }

}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> levels(n);
    for (int i = 0; i < n; ++i)
        cin >> levels[i];

    printOtherTwo(levels, n);

}
