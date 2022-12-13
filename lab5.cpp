#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <cassert>
#include <stdlib.h>
#include <Windows.h>
#include <string>

#define groupno 3
using namespace std;

// epsilon for float comparison
#define EPS 0.00001
// Array size
#define SIZE 9
// Random number range
#define RANDRANGE 100

/*
  Лабораторна робота 5
  виконав Вітязь Денис
  Варіант 3

  Умова:
  3. В новому масиві замініть елементи розташовані над головною діагоналлю симетрично
    елементами, які розташовані під головною діагоналлю. Виведіть новий масив на екран. В новому
    масиві розрахуйте суму всіх елементів, розташованих під головною діагоналлю.
*/

/*допоміжні функції*/
void fillRand(int (&arr)[SIZE][SIZE])
{
    for (int x = 0; x < SIZE; x++)
        for (int y = 0; y < SIZE; y++)
            arr[x][y] = rand() % RANDRANGE;
}

void printarr(int (&arr)[SIZE][SIZE])
{
    // отримуємо хендл консолі для зміни кольору тексту
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            if (x > y)
                SetConsoleTextAttribute(hConsole, 4); // червоний
            else if (x < y)
                SetConsoleTextAttribute(hConsole, 2); // зелений
            else
                SetConsoleTextAttribute(hConsole, 7); // білий
            cout << setw(4) << arr[x][y];
        }
        cout << endl;
    }
}

//

/*задачі*/
unsigned int task1(int (&arr)[SIZE][SIZE])
{
    int sum = 0;
    // ітеруємося по всіх елементах масиву
    for (int x = 0; x < SIZE; x++)
        for (int y = 0; y < SIZE; y++)
        {
            if (x > y)
                arr[y][x] = arr[x][y]; // міняємо елемент над головною діагоналлю на симетричний елемент під головною діагоналлю
            if (x < y)
                sum += arr[x][y]; // елементи під головною діагоналлю додаємо до суми
        }
    return sum;
}
//
bool test()
{
    // test task1
    int arr[SIZE][SIZE];
    // забиваємо масив одиницями
    for (int x = 0; x < SIZE; x++)
        for (int y = 0; y < SIZE; y++)
            arr[x][y] = 1;

    int sum = task1(arr);
    // сума всіх одиничок знизу
    int expected = SIZE * (SIZE - 1) / 2;
    if (sum == expected)
        return true;
    else
        cerr << "отримали суму " << sum << " а очікували " << expected << endl;
    return true;
}

/*основна функція*/
int main(int argc, char *argv[])
{
    int arr[SIZE][SIZE];
    // set console encoding to utf-8
    SetConsoleOutputCP(CP_UTF8);

    // для тестів числа не будуть випадковими
    if (argc > 1)
        srand(1);
    else
        srand(time(NULL));

    fillRand(arr);

    cout << "Масив:" << endl;
    printarr(arr);

    int sum = task1(arr);

    cout << "Масив після виконання завдання:" << endl;
    printarr(arr);
    cout << "Сума елементів під головною діагоналлю: " << sum << endl;
    test();
    return 0;
}
