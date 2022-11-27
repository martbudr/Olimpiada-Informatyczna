#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<double> numbers(n);

    string input;
    for (int i = 0; i < n; ++i) {
        string first, second;
        char delimeter('/');
        getline(cin, first, delimeter);
        getline(cin, second);

        int dividend, divider;
        istringstream(first) >> dividend;
        istringstream(second) >> divider;

        numbers[i] = dividend / (double)divider;
    }

    sort(numbers.begin(), numbers.end());

    if (numbers[0] + numbers[1] <= numbers[n - 1]) cout << "NIE" << '\n';
    else cout << "TAK" << '\n';
}
