// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int a;
    int b;
    int c;
    int sum = 0;
    const int ROW = 9;
    const int COL = 9;
    int Arr[ROW][COL];
    cout << "Введіть число a" << endl;
    cin >> a;
    cout << "Введіть число b" << endl;
    cin >> b;


    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            Arr[i][j] = a + rand() % (b - a + 1);
            cout << setw(5)<< Arr[i][j] << " ";
        }
        cout << endl;
    }
    //
    /*
    1 2 3 4
    5 6 7 8.
    9 8 7 6.
    1 6 4 6.
    
    */
    for(int n=0; n<ROW; n++){
        int sum = 0;
        for(int j=COL-1; j>(ROW-n-1); j--){
            sum += Arr[j][n];
        }   

        Arr[ROW-1-n][n] = sum;
    }
    cout << endl << "друга хрень:" << endl;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cout << setw(5) << Arr[i][j] << " ";
        }
        cout << endl;
    }

    cout<<"Третя хрень:"<<endl;
    for(int n=0; n<ROW; n++){
        if(n%2==1){
            cout<<setw(5)<<0<<sum;
            continue;
        }

        int sum = 0;
        for(int j=COL-1; j>=0; j--){
            sum += Arr[j][n];
        }   

        cout<<setw(5)<<sum;
    }


    cout << endl << "кінець" << endl;
    system("pause");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
