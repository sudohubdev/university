#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <assert.h>
#include <cassert>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cstring>

// для вінди зрузимо її бібліотеки
// (скоро я мігрую на макос)
#ifdef _WIN32
#include <direct.h>
#include <Windows.h>
#include <commdlg.h>
#endif

#define groupno 3
using namespace std;

/*
  Лабораторна робота 7
  виконав Вітязь Денис
  Варіант 3

  Умова:
  3. Опишіть структуру – рядок залікової книжки (екзаменаційна частина). Сформуйте масив іспитів,
які ви склали. Розробіть програму, яка визначає ваш середній бал, складає список ваших
екзаменаторів і за номером семестру виводить на екран результати складання сесій
*/

struct Exam
{
    unsigned short hours; // максимум 65535 годин, 255 може не вистачити                                     2 байти
    unsigned char grade;  // 255 оцінок або навіть літерою по американському стандарту                       1 байт
    time_t date;          // UNIX дата, к-сть секунд від 1 січня 1970 року                                   4 байти
    size_t subjectlen;    // строки займають різну кількість пам'яті, тому їх довжину варто зберігати,       4 байти
    size_t teacherlen;    // це звичайна практика в багатьох бінарних форматах, таких як PE, ELF, PNG і т.д. 4 байти
    char subject[0];      //                                                                                 ...
    char teacher[];       //                                                                                 ...
};

// давай зробимо свій бінарний формат для зберігання даних!
struct Zalik
{
    char magic[3];          // "ZLK" - магічний заголовок, щоб визначити, що це наш формат    3 байти
    unsigned char version;  // версія формату                                                 1 байт
    unsigned char group;    // номер групи                                                    1 байт
    unsigned char semester; // номер семестру                                                 1 байт
    unsigned char examslen; // кількість екзаменів                                            1 байт
    size_t examsize;        // розмір всіх екзаменів разом                                    4 байти
    Exam exams[];           // масив екзаменів                                                ...
};

// алокуємо пам'ять для залікової книжки
Exam *allocExam(size_t subjectlen, size_t teacherlen)
{
    size_t size = sizeof(Exam) + subjectlen + teacherlen; // розмір структури + розмір двох строк
    // так як структура динамічна, то ми маємо виділити пам'ять для неї у стилі C
    Exam *exam = (Exam *)malloc(size);
    assert(exam != NULL); // перевірка на успішне виділення пам'яті
    exam->subjectlen = subjectlen;
    exam->teacherlen = teacherlen;
    return exam;
}

Zalik *loadZalik(const char *path)
{
    FILE *file = fopen(path, "rb");
    assert(file != NULL); // перевірка на успішне відкриття файлу

    const char *header = "zlk"; // магічний заголовок
    char magic[3];
    fread(magic, 1, 3, file);
    assert(memcmp(magic, header, 3) == 0); // перевірка на правильність магічного заголовка

    unsigned char version, group, semester, exams;
    size_t examsize = 0;
    fread(&version, 1, 1, file);
    assert(version == 1); // перевірка на правильність версії формату
    fread(&group, 1, 1, file);
    fread(&semester, 1, 1, file);
    fread(&exams, 1, 1, file);
    fread(&examsize, 4, 1, file);

    Zalik *zalik = (Zalik *)malloc(sizeof(Zalik) + examsize);
    assert(zalik != NULL); // перевірка на успішне виділення пам'яті
    rewind(file);          // повернемося на початок файлу
    fread(zalik, sizeof(Zalik) + examsize, 1, file);
    fclose(file);
    return zalik;
}

bool saveZalik(const char *path, Zalik *zalik)
{
    FILE *file = fopen(path, "wb");
    assert(file != NULL); // перевірка на успішне відкриття файлу
    fwrite(zalik, sizeof(Zalik) + zalik->examsize, 1, file);
    fclose(file);
    return true;
}

void writeData()
{
    std::string group, semester, exams;
    size_t examsize = 0;
    bool exit = false;
    cout << "Введіть номер групи: ";
    cin >> group;
    cout << endl;

    cout << "Введіть номер семестру: ";
    cin >> semester;
    cout << endl;

    cout << "Розпочніть вводити дані про екзамени" << endl;
    std::vector<Exam *> examslist; // множина екзаменів, ми не знаємо скільки їх буде і з якими даними
    while (!exit)
    {
        string subject, teacher, hours, grade;
        // clear cin
        cin.ignore();
        cout << "Введіть назву предмету: ";
        std::getline(std::cin, subject);

        cin.clear();
        cout << "Введіть прізвище викладача: ";
        std::getline(std::cin, teacher);

        cout << "Введіть кількість годин: ";
        cin >> hours;

        cout << "Введіть оцінку: ";
        cin >> grade;

        Exam *exam = allocExam(subject.length(), teacher.length());
        exam->date = time(NULL);
        exam->hours = atoi(hours.c_str()); // перетворення string в int
        exam->grade = atoi(grade.c_str());

        char *offset = ((char *)exam) + sizeof(Exam);      // зміщення на початок поля subject
        memcpy(offset, subject.c_str(), subject.length()); // пряме копіювання даних
        offset += subject.length();
        memcpy(offset, teacher.c_str(), teacher.length());
        examslist.push_back(exam); // додаємо екзамен в множину
        cout << "Бажаєте продовжити вводити дані? (y/n)" << endl;
        string answer;
        cin >> answer;
        if (answer != "y" && answer != "Y")
            exit = true;
    }

    for (int i = 0; i < examslist.size(); i++)
        examsize += sizeof(Exam) + examslist[i]->subjectlen + examslist[i]->teacherlen; // розраховуємо розмір множини екзаменів

    Zalik *zalik = (Zalik *)malloc(sizeof(Zalik) + examsize);
    assert(zalik != NULL);              // перевірка на успішне виділення пам'яті
    strncpy(zalik->magic, "zlk", 3);    // копіюємо підпис
    zalik->version = 1;                 // версія формату
    zalik->group = atoi(group.c_str()); // перетворення string в int
    zalik->semester = atoi(semester.c_str());
    zalik->examslen = examslist.size();
    zalik->examsize = examsize;

    char *offset = ((char *)zalik) + sizeof(Zalik);
    for (int i = 0; i < examslist.size(); i++)
    {
        memcpy(offset, examslist[i], sizeof(Exam) + examslist[i]->subjectlen + examslist[i]->teacherlen);
        offset += sizeof(Exam) + examslist[i]->subjectlen + examslist[i]->teacherlen;
    }

    string path;
// if linux
#ifdef __linux__
    cout << "Введіть шлях до файлу: " << endl;
    cin >> path;
#endif
// if windows
#ifdef _WIN32
    // збереження файлу
    // тут використовується стандартний діалоговий віконний інтерфейс
    // доречі, тут ми заповнюємо віндовсовську структуру OPENFILENAME
    OPENFILENAME saveFileDialog;
    char szSaveFileName[MAX_PATH];
    ZeroMemory(&saveFileDialog, sizeof(saveFileDialog));
    ZeroMemory(szSaveFileName, sizeof(szSaveFileName));
    saveFileDialog.lStructSize = sizeof(saveFileDialog);
    saveFileDialog.hwndOwner = NULL;
    saveFileDialog.lpstrFilter = "Zalik files (*.zlk)\0*.zlk\0All files (*.*)\0*.*\0";
    saveFileDialog.lpstrFile = szSaveFileName;
    saveFileDialog.nMaxFile = MAX_PATH;
    saveFileDialog.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    saveFileDialog.lpstrDefExt = "zlk";

    if (GetSaveFileName(&saveFileDialog))
        path = saveFileDialog.lpstrFile;
    else
    {
        cout << "Ви не вибрали файл" << endl;
        cout << GetLastError();
        return;
    }
#endif
    saveZalik(path.c_str(), zalik);
    // вивільнення пам'яті
    for (int i = 0; i < examslist.size(); i++)
        free(examslist[i]);
    free(zalik);
}
void readData(const char *path)
{
    Zalik *zalik = loadZalik(path);
    cout << "Номер групи: " << (int)zalik->group << endl;
    cout << "Номер семестру: " << (int)zalik->semester << endl;
    cout << "Кількість екзаменів: " << (int)zalik->examslen << endl;

    double avg = 0;
    size_t offset = 0;
    for (int i = 0; i < zalik->examslen; i++)
    {
        Exam *exam = (Exam *)(((char *)zalik) + sizeof(Zalik) + offset);
        printf("Дата: %s", ctime(&exam->date));
        cout << "Кількість годин: " << exam->hours << endl;
        cout << "Оцінка: " << (int)exam->grade << endl;
        // нуль термінатора у нас нема, використаємо printf
        printf("Назва предмету: %.*s\n", exam->subjectlen, exam->subject);
        printf("Прізвище викладача: %.*s\n", exam->teacherlen, exam->subject + exam->subjectlen);
        avg += exam->grade;
        offset += sizeof(Exam) + exam->subjectlen + exam->teacherlen;
    }
    avg /= zalik->examslen;
    cout << "Середня оцінка: " << avg << endl;
    free(zalik);
}
/*основна функція*/
int main(int argc, char *argv[])
{
    // set console encoding to utf-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // stdin utf-8
    constexpr char cp_utf8[] = ".65001";
    setlocale(LC_ALL, cp_utf8);
    _setmode(_fileno(stdout), 0x4000);
    _setmode(_fileno(stdin), 0x4000);

#endif
    if (argc > 1)
    {
        readData(argv[1]);
        cout << "\nДо побачення!" << endl;
        return 0;
    }

    cout << "Вас вітає програма для роботи з заліковою книжкою!" << endl;
    cout << "Чи бажаєте ви записати дані в залікову книжку? (y/n)";
    char answer;
    cin >> answer;
    cout << endl;
    if (answer == 'y' || answer == 'Y')
        writeData();

    cout << "Чи бажаєте ви прочитати дані з залікової книжки? (y/n)";
    cin >> answer;
    cout << endl;
    if (answer == 'y' || answer == 'Y')
    {
        cout << "Введіть шлях до файлу: " << endl;

        string path;
        cin >> path;
        readData(path.c_str());
    }

    cout << "\nДо побачення!" << endl;

    return 0;
}
