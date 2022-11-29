#include <iostream>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <locale>
#include <wchar.h>
#include <cwctype>

using namespace std;
#define groupno 3

#define alphabet 33
/*
  Лабораторна робота 6
  виконав Вітязь Денис
  Варіант 3

  Умова:
  Виведіть символи, які зустрічаються у вихідному реченні по одному разу
*/

/*
    Змусити вивід українських символів працювати
    Джерело: https://stackoverflow.com/questions/22950412/c-cant-get-wcout-to-print-unicode-and-leave-cout-working
*/

// штуки для вінди
#ifndef MS_STDLIB_BUGS
#if (_MSC_VER || __MINGW32__ || __MSVCRT__)
#define MS_STDLIB_BUGS 1
#else
#define MS_STDLIB_BUGS 0
#endif
#endif

#if MS_STDLIB_BUGS
#include <io.h>
#include <fcntl.h>
#endif

// ця функція зробить вивід українських символів
void init_locale(void)
{
#if MS_STDLIB_BUGS
    // використаємо UTF16, в нього влазять українські символи
    constexpr char cp_utf16le[] = ".1200";
    setlocale(LC_ALL, cp_utf16le);
    // stdout - стандартний вивід, stdin - стандартний ввід
    _setmode(_fileno(stdout), 0x10000);
    _setmode(_fileno(stdin), 0x10000);
#else
    // The correct locale name may vary by OS, e.g., "en_US.utf8".
    constexpr char locale_name[] = "";
    setlocale(LC_ALL, locale_name);
    std::locale::global(std::locale(locale_name)); // лінукси використовують трохи іншу штуку
    std::wcin.imbue(std::locale())
        std::wcout.imbue(std::locale());
#endif
}

/*задачі*/
std::wstring task1(std::wstring in)
{
    std::wstring out = L"";
    for (wchar_t &chr : in)
    {
        if (!std::iswalpha(chr) && chr < 128 && 0)
            continue;

        if (out.find(chr) == std::wstring::npos)
            out.append(1, chr);
    }
    return out;
}

bool test()
{
    // test task1
    std::wstring test1 = L"скажи слово паляниця";
    std::wstring test1_out = L"скажи ловпянц";
    std::wstring test1_res = task1(test1);
    if (test1_res != test1_out)
    {
        std::wcout << L"task1 провалився!" << std::endl;
        std::wcout << L"очікували: " << test1_out << std::endl;
        std::wcout << L"отримали: " << test1_res << std::endl;
        return false;
    }
    return true;
}

/*основна функція*/
int main(int argc, char *argv[])
{
    init_locale();
    /*
        wstring - wide string, тобто широкий рядок, тобто рядок, який може містити українські символи
        L"..." - це широкий рядок, він має префікс L
        в основному якщо в функції є літера w - це означає, що вона працює з широкими рядками
        все інше працює так само
    */
    std::wstring input;
    std::wcout << L"Введіть речення: ";
    std::getline(std::wcin, input);
    std::wcout << L"Результат: " << task1(input) << std::endl;

    test();
    return 0;
}
