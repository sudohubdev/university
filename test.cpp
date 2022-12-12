#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <locale>
#include <wchar.h>
#include <cwctype>

using namespace std;
int main()
{
    int x;
    cout << "Введіть кількість рядків: ";
    cin >> x;
    int y;
    cout << "Введіть кількість стовпців: ";
    cin >> y;
    int **Arr = new int *[y];
    for (int i = 0; i < y; ++i)
    {
        Arr[i] = new int[x];
    }
    int **Arr1 = new int *[x];
    for (int i = 0; i < x; ++i)
    {
        Arr1[i] = new int[y];
    }
    for (int i = 0; i < x; i++)
    {

        for (int j = 0; j < y; j++)
        {
            Arr[j][i] = rand() % 10;
            cout << setw(5) << Arr[j][i] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            Arr1[x-1-j][i] = Arr[j][i];
        }
    }
    cout << endl;

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            cout << Arr1[j][i] << " ";
        }
        cout << endl;
    }
}