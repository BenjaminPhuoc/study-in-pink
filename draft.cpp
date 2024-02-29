#include <bits/stdc++.h>
using namespace std;
// Clamp function
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
    {
        cout << "too short\n";
        return -1;
    }
    if (n1 > 20)
    {
        cout << "too long\n";
        return -2;
    }
    // Find se
    int pos = 0;
    for (int i = 0; i < n2; i++)
    {
        if (email[i] == '@')
            pos = i;
    }
    const char *se = substr(email, 0, pos);
    cout << se << ' ' << s << '\n';
    int substringPos = isSubstring(se, s);
    cout << substringPos << '\n';
    if (substringPos)
    {
        cout << "s contains se, pos = " << substringPos - 1 << "\n";
        return -(300 + substringPos - 1);
    }

    int consecutivePos = consecutiveChar(s, n1);
    if (consecutivePos)
    {
        cout << "s contains consecutive chars, pos = " << consecutivePos - 1 << "\n";
        return -(400 + consecutivePos - 1);
    }
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
    {
        cout << "s doesn't contain special char\n";
        return -5;
    }
    if (illegal)
    {
        cout << "s contains illegal char, pos = " << illegal - 1 << "\n";
        return illegal - 1;
    }
    cout << "s is legal\n";
    return -10;
}
int main()
{
    const char *s = "Gbcccg1cc";
    const char *email = "ccg1@dgc$";
    cout << checkPassword(s, email);
    // cout << fixed << setprecision(20) << (330 * 110 / 100.0);
}
