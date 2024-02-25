#include "study_in_pink1.h"

bool readFile(
    const string &filename,
    int &HP1,
    int &HP2,
    int &EXP1,
    int &EXP2,
    int &M1,
    int &M2,
    int &E1,
    int &E2,
    int &E3)
{
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open())
    {
        ifs >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
        return true;
    }
    else
    {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Clamp function
int clamp(int a, int b, int c)
{
    if (a < b)
        return b;
    if (a > c)
        return c;
    return a;
}

// Task 1
int firstMeet(int &exp1, int &exp2, int e1)
{
    // Check for conditions
    if (e1 < 0 or e1 > 99)
        return -99;
    exp1 = clamp(exp1, 0, 600);
    exp2 = clamp(exp2, 0, 600);

    // Case 0 <= e1 <= 3
    if (e1 <= 3)
    {
        if (exp2 == 0)
            exp2 += 29;
        else if (exp2 == 1)
            exp2 += 45;
        else if (exp2 == 2)
            exp2 += 75;
        else
            exp2 += 149;

        // Calculate Decision D
        int D = e1 * 3 + exp1 * 7;
        exp1 += !(D & 1) ? ceil(D / 200.0) : -D / 100;
    }
    // Case 4 <= e1 <= 99
    else
    {
        if (e1 <= 19)
            exp2 += ceil(e1 / 4.0 + 19);
        else if (e1 <= 49)
            exp2 += ceil(e1 / 9.0 + 21);
        else if (e1 <= 65)
            exp2 += ceil(e1 / 16.0 + 17);
        else if (e1 <= 79)
        {
            exp2 = clamp(exp2 + ceil(e1 / 4.0 + 19), 0, 600);
            // Check exp2 for bonus of info 2
            exp2 += exp2 > 200 ? ceil(e1 / 9.0 + 21) : 0;
        }
        else
        {
            exp2 = clamp(exp2 + ceil(e1 / 4.0 + 19) + ceil(e1 / 9.0 + 21), 0, 600);
            // Check exp2 for bonus of info 3 and 15% of total exp
            exp2 = exp2 > 400 ? ceil(1.15 * (exp2 + ceil(e1 / 16.0 + 17))) : exp2;
        }

        // exp1 loses e1 exp
        exp1 -= e1;
    }

    exp1 = clamp(exp1, 0, 600);
    exp2 = clamp(exp2, 0, 600);
    return exp1 + exp2;
}

// Task 2
// Events of route 2
void eventsRoute2(int &HP1, int &EXP1, int &M1, int m, int E)
{
    // Buy food and drink
    HP1 = HP1 < 200 ? ceil(HP1 * 1.3) : ceil(HP1 * 1.1);
    M1 -= HP1 < 200 ? 150 : 70;
    if (E and 2 * M1 < m)
        return;
    // Vehicle rental
    M1 -= EXP1 < 400 ? 200 : 120;
    EXP1 = ceil(EXP1 * 1.13);
    if (E and 2 * M1 < m)
        return;
    // Scammed by a homeless
    M1 -= EXP1 < 300 ? 100 : 120;
    EXP1 = ceil(EXP1 * 0.9);
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
    double P1, P2, P3; // Route probabilities
    while (S * S < EXP1)
        S++;
    // Find S nearest to EXP1
    S = EXP1 - (S - 1) * (S - 1) < S * S - EXP1 ? S - 1 : S;

    // Route 1
    P1 = EXP1 >= S ? 1 : ((double)EXP1 / S + 80) / 123;

    // Route 2
    // Check for E2
    if (E2 & 1)
    {
        // Loop of events
        while (2 * M1 >= m)
            eventsRoute2(HP1, EXP1, M1, m, E2 & 1);
        HP1 = ceil(HP1 * 0.83);
        EXP1 = ceil(EXP1 * 1.17);
    }
    else
    {
        eventsRoute2(HP1, EXP1, M1, m, E2 & 1);
    }

    HP1 = clamp(HP1, 0, 666);
    EXP1 = clamp(EXP1, 0, 600);
    M1 = clamp(M1, 0, 3000);
    return HP1 + EXP1 + M1;
}

// Task 3
int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3)
{
    // TODO: Complete this function

    return -1;
}

// Task 4
int checkPassword(const char *s, const char *email)
{
    // TODO: Complete this function

    return -99;
}

// Task 5
int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    // TODO: Complete this function

    return -1;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////