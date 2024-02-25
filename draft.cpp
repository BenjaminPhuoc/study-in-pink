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

// Task 2
// Events of route 2
void eventsRoute2(int &HP1, int &EXP1, int &M1, int m, int E)
{
    // Buy food and drink
    HP1 = clamp(ceil(HP1 < 200 ? HP1 * 1.3 : HP1 * 1.1), 0, 666);
    M1 = clamp(HP1 < 200 ? M1 - 150 : M1 - 70, 0, 3000);
    if (E and 2 * M1 < m) // E2 is odd and payment > 50%
        return;
    if (!E and !M1) // E2 is even and M1 = 0
        return;
    // Vehicle rental
    M1 = clamp(EXP1 < 400 ? M1 - 200 : M1 - 120, 0, 3000);
    EXP1 = clamp(ceil(EXP1 * 1.13), 0, 600);
    if (E and 2 * M1 < m) // E2 is odd and payment > 50%
        return;
    if (!E and !M1) // E2 is even and M1 = 0
        return;
    // Homeless's blunder
    M1 = clamp(EXP1 < 300 ? M1 - 100 : M1 - 120, 0, 3000);
    EXP1 = clamp(ceil(EXP1 * 0.9), 0, 600);
}
int traceLuggage(int &HP1, int &EXP1, int &M1, int E2)
{
    // Check for conditions
    if (E2 < 0 or E2 > 99)
        return -99;
    HP1 = clamp(HP1, 0, 666);
    EXP1 = clamp(EXP1, 0, 600);
    M1 = clamp(M1, 0, 3000);

    int S = 0, m = M1; // Perfect square number S, initial money m
    // double P1, P2, P3; // Route probabilities
    while (S * S < EXP1)
        S++;
    // Find S nearest to EXP1
    S = EXP1 - (S - 1) * (S - 1) < S * S - EXP1 ? S - 1 : S;

    // Route 1
    // Probability of route 1
    double P1 = EXP1 >= S * S ? 1 : ((double)EXP1 / (S * S) + 80) / 123;

    // Route 2
    // Check if M1 = 0
    if (M1)
    {
        // Check for E2 parity
        if (E2 & 1) // odd
        {
            // Loop of events
            while (2 * M1 >= m)
                eventsRoute2(HP1, EXP1, M1, m, 1);
        }
        else // even

            eventsRoute2(HP1, EXP1, M1, m, 0);
    }
    // HP and EXP status update
    HP1 = clamp(ceil(HP1 * 0.83), 0, 666);
    EXP1 = clamp(ceil(EXP1 * 1.17), 0, 600);
    // Recalculation of nearest perfect quare
    S = 0;
    while (S * S < EXP1)
        S++;
    S = EXP1 - (S - 1) * (S - 1) < S * S - EXP1 ? S - 1 : S;
    // Probability of route 2
    double P2 = EXP1 >= S * S ? 1 : ((double)EXP1 / (S * S) + 80) / 123;

    // Route 3
    int P[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11}; // Array of probabilities
    // Probability of route 3
    double P3 = E2 < 10 ? P[E2] / 100.0 : P[(E2 % 10 + E2 / 10) % 10] / 100.0;
    // Check for probabilities
    if (P1 == 1 and P2 == 1 and P3 == 1)
        EXP1 = ceil(EXP1 * 0.75);
    else
    {
        double P4 = (P1 + P2 + P3) / 3;
        HP1 = ceil(P4 < 0.5 ? HP1 * 0.85 : HP1 * 0.9);
        EXP1 = ceil(P4 < 0.5 ? EXP1 * 1.15 : EXP1 * 1.2);
    }

    HP1 = clamp(HP1, 0, 666);
    EXP1 = clamp(EXP1, 0, 600);
    M1 = clamp(M1, 0, 3000);
    cout << "HP1 = " << HP1 << "\nEXP1 = " << EXP1 << "\nM1 = " << M1 << "\nP1 = " << P1 << "\nP2 = " << P2 << "\nP3 = " << P3 << "\n";
    return HP1 + EXP1 + M1;
}
int main()
{
    int hp1 = 333, exp1 = 333, m1 = 2222, e2 = 31;
    // cin >> hp1 >> exp1 >> m1 >> e2;
    cout << traceLuggage(hp1, exp1, m1, e2);
}