#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
// Define a map
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
/*
pink#pink   2   1
pink@123    3   2
1234#xyz    1   0
123!pink    1   3
*/
int main()
{
    // map m;

    // m.insert("apple", 5);
    // m.insert("banana", 10);
    // m.insert("orange", 7);

    // cout << "freq of apple: " << m.getValue("apple") << endl;
    // cout << "Value of banana: " << m.getValue("banana") << endl;
    // cout << "Value of orange: " << m.getValue("orange") << endl;
    // cout << "Value of not exist: " << m.getValue("orangee") << endl;
    // return 0;
    const char *arr_pwds[7] = {"pink@123", "123!pink", "1234#xyz", "pink#pink", "pink#pink",
                               "pink@123"};
    cout << findCorrectPassword(arr_pwds, 6);
}