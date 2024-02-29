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
bool isSubstring(const char *s, const char *se)
{
    int i = 0, j = 0;
    while (s[i] != '\0')
    {
        if (s[i] == se[j])
        {
            while (s[i] == se[j] and se[j] != '\0')
            {
                i++;
                j++;
            }
            if (se[j] == '\0')
                return 1;
            j = 0;
        }
        i++;
    }
    return 0;
}
int main()
{
    const char *s = "jiowfjopiaejwgoipvjnweAH";
    const char *se = "ipkjn";
    cout << isSubstring(s, se);
    // cout << fixed << setprecision(20) << (330 * 110 / 100.0);
}
