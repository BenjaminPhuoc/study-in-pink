#include <bits/stdc++.h>
using namespace std;

int main()
{
    int e1, exp1;
    cin >> e1 >> exp1;
    int D = e1 * 3 + exp1 * 7;
    exp1 = D % 2 == 0 ? ceil((200 * exp1 + D) / 200.0) : exp1 - D / 100;
    cout << D << ' ' << exp1;
}