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

// Task 1
int firstMeet(int &exp1, int &exp2, int e1)
{
    if (e1 < 0 or e1 > 99)
        return -99;
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
        int D = e1 * 3 + exp1 * 7;
        exp1 = D % 2 == 0 ? ceil((200 * exp1 + D) / 200.0) : exp1 - D / 100;
    }
    else if (e1 <= 99)
    {
        if (e1 <= 19)
            exp2 += ceil(e1 / 4.0 + 19);
        else if (e1 <= 49)
            exp2 += ceil(e1 / 9.0 + 21);
        else if (e1 <= 65)
            exp2 += ceil(e1 / 16.0 + 17);
        else if (e1 <= 79)
        {
            exp2 += ceil(e1 / 4.0 + 19);
            exp2 += exp2 > 200 ? ceil(e1 / 9.0 + 21) : 0;
        }
        else
        {
            exp2 += ceil(e1 / 4.0 + 19) + ceil(e1 / 9.0 + 21);
            exp2 = exp2 > 400 ? ceil(1.15 * (exp2 + ceil(e1 / 16.0 + 17))) : exp2;
        }
        exp1 -= e1;
    }

    return exp1 + exp2;
}

// Task 2
int traceLuggage(int &HP1, int &EXP1, int &M1, int E2)
{
    // TODO: Complete this function

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