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
        if (e1 == 0)
            exp2 += 29;
        else if (e1 == 1)
            exp2 += 45;
        else if (e1 == 2)
            exp2 += 75;
        else
            exp2 += 149;
        // Calculate decision D
        int D = e1 * 3 + exp1 * 7;
        exp1 += ceil(!(D & 1) ? D / 200.0 : -D / 100);
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
            exp2 = clamp(ceil(exp2 + e1 / 4.0 + 19), 0, 600);
            // Check exp2 for bonus of info 2
            exp2 += ceil(exp2 > 200 ? e1 / 9.0 + 21 : 0);
        }
        else
        {
            exp2 = clamp(ceil(ceil(exp2 + e1 / 4.0 + 19) + e1 / 9.0 + 21), 0, 600);
            // Check exp2 for bonus of info 3 and 15% of total exp
            exp2 = ceil(exp2 > 400 ? (115 / 100.0) * ceil(exp2 + e1 / 16.0 + 17) : exp2);
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
    M1 = clamp(HP1 < 200 ? M1 - 150 : M1 - 70, 0, 3000);
    HP1 = clamp(ceil(HP1 < 200 ? HP1 * 130 / 100.0 : HP1 * 110 / 100.0), 0, 666);
    if (E and 2 * M1 < m) // E2 is odd and payment > 50%
        return;
    if (!E and !M1) // E2 is even and M1 = 0
        return;
    // Vehicle rental
    M1 = clamp(EXP1 < 400 ? M1 - 200 : M1 - 120, 0, 3000);
    EXP1 = clamp(ceil(EXP1 * 113 / 100.0), 0, 600);
    if (E and 2 * M1 < m) // E2 is odd and payment > 50%
        return;
    if (!E and !M1) // E2 is even and M1 = 0
        return;
    // Homeless's blunder
    M1 = clamp(EXP1 < 300 ? M1 - 100 : M1 - 120, 0, 3000);
    EXP1 = clamp(ceil(EXP1 * 90 / 100.0), 0, 600);
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
    while (S * S <= EXP1)
        S++;
    // Find S nearest to EXP1
    S = EXP1 - (S - 1) * (S - 1) < S * S - EXP1 ? S - 1 : S;

    // Route 1
    // Probability of route 1
    double P1 = EXP1 >= S * S ? 1 : ((double)EXP1 / (S * S) + 80) / 123;

    // Route 2
    // Check if M1 != 0
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
    HP1 = clamp(ceil(HP1 * 83 / 100.0), 0, 666);
    EXP1 = clamp(ceil(EXP1 * 117 / 100.0), 0, 600);
    // Recalculation of nearest perfect quare
    S = 0;
    while (S * S <= EXP1)
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
        EXP1 = ceil(EXP1 * 75 / 100.0);
    else
    {
        double P4 = (P1 + P2 + P3) / 3;
        HP1 = ceil(P4 < 0.5 ? HP1 * 85 / 100.0 : HP1 * 90 / 100.0);
        EXP1 = ceil(P4 < 0.5 ? EXP1 * 115 / 100.0 : EXP1 * 120 / 100.0);
    }

    HP1 = clamp(HP1, 0, 666);
    EXP1 = clamp(EXP1, 0, 600);
    M1 = clamp(M1, 0, 3000);
    return HP1 + EXP1 + M1;
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
    EXP1 = clamp(ceil(abs(taxi[x][y]) > sher ? EXP1 * 88 / 100.0 : EXP1 * 112 / 100.0), 0, 600);
    EXP2 = clamp(ceil(abs(taxi[x][y]) > sher ? EXP2 * 88 / 100.0 : EXP2 * 112 / 100.0), 0, 600);
    HP1 = clamp(ceil(abs(taxi[x][y]) > sher ? HP1 * 90 / 100.0 : HP1 * 110 / 100.0), 0, 666);
    HP2 = clamp(ceil(abs(taxi[x][y]) > sher ? HP2 * 90 / 100.0 : HP2 * 110 / 100.0), 0, 666);
    // Return value of the winner of the chase
    return abs(taxi[x][y]) > sher ? taxi[x][y] : sher;
}

// Task 4
// Find substring
char *substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char *)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;
}
// Check if se is a substring of s
int isSubstring(const char *se, const char *s)
{
    if (!strlen(se))
        return 1;
    int i = 0, j = 0;
    while (s[i] != '\0')
    {
        if (s[i] == se[j])
        {
            int init = i;
            while (s[i] == se[j] and se[j] != '\0')
            {
                i++;
                j++;
            }
            if (se[j] == '\0')
                return init + 1;
            j = 0;
            i = init;
        }
        i++;
    }
    return 0;
}
int consecutiveChar(const char *s, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] == s[i + 1] and s[i] == s[i + 2])
            return i + 1;
    }
    return 0;
}
int checkPassword(const char *s, const char *email)
{
    int n1 = strlen(s), n2 = strlen(email);
    if (n1 < 8)
        return -1;
    if (n1 > 20)
        return -2;
    // Find se
    int pos = 0;
    for (int i = 0; i < n2; i++)
    {
        if (email[i] == '@')
            pos = i;
    }
    const char *se = substr(email, 0, pos);
    int substringPos = isSubstring(se, s);
    if (substringPos)
        return -(300 + substringPos - 1);
    int consecutivePos = consecutiveChar(s, n1);
    if (consecutivePos)
        return -(400 + consecutivePos - 1);
    int illegal = 0; // Check if s contains illegal characters
    bool found = 0;  // Check if s contains special characters
    for (int i = 0; i < n1; i++)
    {
        if (s[i] == '@' or s[i] == '#' or s[i] == '%' or s[i] == '$' or s[i] == '!')
        {
            found = 1;
            continue;
        }
        if (s[i] >= 48 and s[i] <= 57 or s[i] >= 65 and s[i] <= 90 or s[i] >= 97 and s[i] <= 122)
            continue;
        illegal = illegal == 0 ? i + 1 : min(illegal, i + 1);
    }
    if (!found)
        return -5;
    if (illegal)
        return illegal - 1;
    return -10;
}

// Task 5
// Define a new map datatype
struct node
{
    const char *pwd;
    int freq;
    int pos;
    node *next;
};
struct map
{
private:
    node *root;

public:
    map() : root(nullptr) {}
    void insert(const char *pwd, int freq, int pos)
    {
        // Check if key already exists
        node *current = root;
        while (current != nullptr)
        {
            if (strcmp(current->pwd, pwd) == 0)
            {
                // Update value if key exists
                current->freq = freq;
                current->pos = min(pos, current->pos);
                return;
            }
            current = current->next;
        }
        // Key doesn't exist, create a new node
        node *newNode = new node{pwd, freq, pos, root};
        root = newNode;
    }
    int getFreq(const char *pwd)
    {
        node *current = root;
        while (current != nullptr)
        {
            if (strcmp(current->pwd, pwd) == 0)
                return current->freq;
            current = current->next;
        }
        return 0;
    }
    int getPos(const char *pwd)
    {
        node *current = root;
        while (current != nullptr)
        {
            if (strcmp(current->pwd, pwd) == 0)
                return current->pos;
            current = current->next;
        }
        return 0;
    }
};
int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    // Map for storing passwords' frequencies
    map m;
    for (int i = 0; i < num_pwds; i++)
        m.insert(arr_pwds[i], m.getFreq(arr_pwds[i]) + 1, i);
    // Sort passwords by frequency -> length -> postion
    for (int i = 0; i < num_pwds - 1; i++)
    {
        for (int j = 0; j < num_pwds - i - 1; j++)
        {
            int a1 = m.getFreq(arr_pwds[j]);
            int b1 = m.getFreq(arr_pwds[j + 1]);
            if (a1 > b1)
                swap(arr_pwds[j], arr_pwds[j + 1]);
            else if (a1 == b1)
            {
                int a2 = strlen(arr_pwds[j]);
                int b2 = strlen(arr_pwds[j + 1]);
                if (a2 > b2)
                    swap(arr_pwds[j], arr_pwds[j + 1]);
                else if (a2 == b2)
                {
                    if (m.getPos(arr_pwds[j]) < m.getPos(arr_pwds[j + 1]))
                        swap(arr_pwds[j], arr_pwds[j + 1]);
                }
            }
        }
    }
    // The last value after the sorting is the result
    return m.getPos(arr_pwds[num_pwds - 1]);
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////