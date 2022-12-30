#include <iostream>
using namespace std;
int main()
{
    int x;
    cout << "GIVE ME YOUR GRADE OR SPANKIE";
    cin >> x;
    if (92 <= x && x <= 100)
    {
        cout << "Excelent! you got an A";
    }
    if (83 <= x && x <= 91)
    {
        cout << "Good job!, B is nice";
    }
    if (75 <= x && x <= 82)
    {
        cout << "C, atleast you pass, it's ok";
    }
    if (0 <= x && x < 75)
    {
        cout << "D?? SPANKING TIME";
    }
    if (x > 100 or x < 0)
    {
        cout << "shit lie, tell truth!";
    }
    system("pause");
}