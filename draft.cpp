#include <bits/stdc++.h>
using namespace std;
// Clamp function
int clamp(int a, int b, int c)
{
    if (a < b)
        return b;
    if (a > c)
        return c;
    return a;
}
// Task 3
// Maximum value of taxi coordinate's diagonals at a point
int maxDiag(int taxi[10][10], int row, int column)
{
    int res = taxi[row][column];
    int i = column - row >= 0 ? 0 : row - column;
    int j = column - row >= 0 ? column - row : 0;
    while (i < 10 and j < 10)
    {
        res = max(res, taxi[i][j]);
        i++;
        j++;
    }
    i = column + row > 9 ? column + row - 9 : 0;
    j = column + row > 9 ? 9 : column + row;
    while (i < 10 and j >= 0)
    {
        res = max(res, taxi[i][j]);
        i++;
        j--;
    }
    return res;
}
int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3)
{
    // Check for conditions
    if (E3 < 0 or E3 > 99)
        return -99;
    HP1 = clamp(HP1, 0, 666);
    EXP1 = clamp(EXP1, 0, 600);
    HP2 = clamp(HP2, 0, 666);
    EXP2 = clamp(EXP2, 0, 600);

    // Taxi coordinate matrix
    int taxi[10][10];
    int x = 0, y = 0; // Intersect coordinate
    // Taxi moves along rows
    // Row: i, Column: j
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            taxi[i][j] = (E3 * j + i * 2) * (i - j);
            if (taxi[i][j] > E3 * 2)
                x++;
            if (taxi[i][j] < -E3)
                y++;
        }
    }
    while (x > 9)
        x = x % 10 + x / 10;
    while (y > 9)
        y = y % 10 + y / 10;
    // Sherlock's point
    int sher = abs(maxDiag(taxi, x, y));
    // EXP and HP change after the chase
    EXP1 = clamp(ceil(abs(taxi[x][y]) > sher ? EXP1 * 0.88 : EXP1 * 1.12), 0, 600);
    EXP2 = clamp(ceil(abs(taxi[x][y]) > sher ? EXP2 * 0.88 : EXP2 * 1.12), 0, 600);
    HP1 = clamp(ceil(abs(taxi[x][y]) > sher ? HP1 * 0.9 : HP1 * 1.1), 0, 666);
    HP2 = clamp(ceil(abs(taxi[x][y]) > sher ? HP2 * 0.9 : HP2 * 1.1), 0, 666);
    // Return value of the winner of the chase
    return abs(taxi[x][y]) > sher ? taxi[x][y] : sher;
}

int main()
{
    int hp1 = 400, exp1 = 600, hp2 = 350, exp2 = 500, e3 = 99;
    cout << chaseTaxi(hp1, exp1, hp2, exp2, e3);
}
