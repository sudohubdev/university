/*
Увага!!! Виконуємо перші два завдання!
1. Усі необхідні дані для функцій повинні передаватися як параметри.
2.  Використовувати глобальні змінні у функціях неприпустимо.
3. Неприпустимо в одну функцію вписати і створення масиву, і його заповнення, і сортування, і інші маніпуляції з масивом. В такому разі вона буде неуніверсальною, її не можна буде використати ще раз,  бо якась дія обов"язково буде лишня. Функція повинна виконувати одну завершену дію. 
Як додатковий матеріал до лекції: ravesli.com ур.12, 13, 14, 19, 96, 97, 98, 99, 100
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <cassert>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#endif
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
  Лабораторна робота 8
  виконав Вітязь Денис
  Варіант 3

  Умова:
   Перше завдання з лаби 5:
    1)В новому масиві замініть елементи розташовані над головною діагоналлю симетрично
    елементами, які розташовані під головною діагоналлю. Виведіть новий масив на екран. В новому
    масиві розрахуйте суму всіх елементів, розташованих під головною діагоналлю.

    2)Опишіть функцію f(x, y), яка перевіряє, чи можливо пере-
    ставивши літери в слові х отримати слово y. Розробіть
    програму, що знаходить такі слова в наборі слів

    3)Для завдання 3 (див. табл. 8.1. Задача 3) напишіть програму табулювання функції, заданої
    рекурентною формулою, де k – натуральне число. Розробіть рекурсивний алгоритм обчислення
    функції.
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
    // портування програм - це головний біль. у мене вимикають світло, так що я не маю бути привязаним до конкретної платформи
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
#ifdef _WIN32
            if (x > y)
                SetConsoleTextAttribute(hConsole, 4); // червоний
            else if (x < y)
                SetConsoleTextAttribute(hConsole, 2); // зелений
            else
                SetConsoleTextAttribute(hConsole, 7); // білий
#endif
            cout << setw(4) << arr[x][y];
        }
        cout << endl;
    }
}

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

bool task2(wstring x, wstring y)
{
    // перевіряємо, чи однакові літери
    // підхід Сі для юнікода не працює, використаємо можливості stl
    // auto розіменовується автоматично, в заліжності від ОС: (char або wchar_t)
    for (auto c : x)
        if (y.find(c) == wstring::npos)
            return false;
    return true;
}

int task3(int k)
{
    /*
    f(0)=1, f(1)=1,
    f(x+2)=2*f(x+1)-(x+1);
    x = k - 2
    f(k) = 2*f(k-1)-(k-1)
    */
    int result;
    if (k == 0 || k == 1)
        result = 1;
    else
        result = 2 * task3(k - 1) - (k - 1);
    cout << "f(" << k << ")=" << result << endl;
    return result;
}

bool test()
{

    return true;
}

/*основна функція*/
int main(int argc, char *argv[])
{
    // set console encoding to utf-8 (включаємо як необхідно для вінди, юнікси по дефолту пишуть в utf-8)
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // для тестів числа не будуть випадковими
    if (argc > 1)
        srand(1);
    else
        srand(time(NULL));

    // задача з масивом
    int arr[SIZE][SIZE];
    fillRand(arr);
    cout << "Масив:" << endl;
    printarr(arr);

    int sum = task1(arr);

    cout << "Масив після виконання завдання:" << endl;
    printarr(arr);
    cout << "Сума елементів під головною діагоналлю: " << sum << endl;
    // задача 2 зі словами
    wstring x, y;
    cout << "Введіть слово x: ";
    getline(wcin, x);
    cout << "Введіть слово y: ";
    getline(wcin, y);

    cout << "Чи є слово x підмножиною слова y? " << (task2(x, y) ? "Так" : "Ні") << endl;
    // задача 3 з рекурсією
    int k;
    cout << "Введіть число k: ";
    cin >> k;
    task3(k);
    system("pause");
    return 0;
}
