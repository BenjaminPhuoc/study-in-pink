#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
struct password
{
    int len;
    int pos;
    int count;
};

int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    string arr_pwds1[num_pwds];
    for (int i = 0; i < num_pwds; i++)
    {
        arr_pwds1[i] = arr_pwds[i];
        cout << arr_pwds1[i] << ' ';
    }
    cout << "\n";
    password pwds[num_pwds] = {0};
    for (int i = 0; i < num_pwds; i++)
    {
        pwds[i].pos = i;
        pwds[i].len = arr_pwds1[i].size();
        for (int j = 0; j < num_pwds; j++)
        {
            if (arr_pwds1[i] == arr_pwds1[j] && i > j)
            {
                pwds[i].count = -1;
                break;
            }
            if (arr_pwds1[i] == arr_pwds1[j])
                pwds[i].count++;
        }
    }
    for (int i = 0; i < num_pwds - 1; i++)
    {
        for (int j = 0; j < num_pwds - i - 1; j++)
        {
            if (pwds[j].count > pwds[j + 1].count)
                swap(pwds[j], pwds[j + 1]);
            else if (pwds[j].count == pwds[j + 1].count)
            {
                if (pwds[j].len > pwds[j + 1].len)
                    swap(pwds[j], pwds[j + 1]);
                else if (pwds[j].len == pwds[j + 1].len)
                {
                    if (pwds[j].pos < pwds[j + 1].pos)
                        swap(pwds[j], pwds[j + 1]);
                }
            }
        }
    }
    return pwds[num_pwds - 1].pos;
}
int main()
{
    const char *arr_pwds[30] = {

        "IExdmOA#RSyl",
        "cDC@bhKvafYLaUZWS",
        "Cj#Auxtn",
        "pWtTTyBMlCk#Hm",
        "$zBPsnncbpQRqNObqX",
        "vLi@rHcmQMLiNMgjpNW",
        "LH$BIPaIxDnbGoqW",
        "Cj#Auxtn",
        "ZJi$neHreYrhxqeoPRM",
        "$zBPsnncbpQRqNObqX",
        "jgtJBp$l%SdiNeP@ok",
        "g%ufVXzkInadaWXoI",
        "ZJi$neHreYrhxqeoPRM",
        "u!AnFNSQroAoyeq$NJ",
        "BDfvst%GYvGXk",
        "LH$BIPaIxDnbGoqW",
        "#xiK$!PVNXAam$d",
        "GxIwCPHY@cpYZLRl#",
        "u!AnFNSQroAoyeq$NJ",
        "pWtTTyBMlCk#Hm",
        "$zBPsnncbpQRqNObqX",
        "$zBPsnncbpQRqNObqX",
        "g%ufVXzkInadaWXoI",
        "$zBPsnncbpQRqNObqX",
        "GxIwCPHY@cpYZLRl#",
        "vLi@rHcmQMLiNMgjpNW",
        "Cj#Auxtn",
        "VaHXlXohu@pYoVC%",
        "uorTT%EDj$",
        "#xiK$!PVNXAam$d"};
    cout << findCorrectPassword(arr_pwds, 30);
}