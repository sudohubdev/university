#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>

#define groupno 3
using namespace std;

//epsilon for float comparison
#define EPS 0.001
//euler constant
const double Euler = std::exp(1.0);

/*
  Лабораторна робота 3
  виконав Вітязь Денис
  Варіант 3
*/

/*допоміжні функції*/
double text2nums(std::string input,int index){ //перетворення тексту в числа
    //може бути розділена або пробілами або комами
    bool mode = input.find(",") != std::string::npos;
    char mchr = mode ? ',' : ' ';
    //mode 0 - space separated
    //mode 1 - comma separated

    size_t pos = 0;
    size_t prevpos = 0;
    size_t i = 0;
    std::string number;
    while (pos<input.length()){
        //входження розділювача
        pos = input.find_first_of(mchr, prevpos);
        if(pos == std::string::npos){
            //як нема розділювача то це кінець
            pos = input.length();
        }
        //вирізаємо число
        number = input.substr(prevpos, pos-prevpos);
        // stod - строка в double
        if(i == index){
            return std::stod(number);
        }
        prevpos = pos+1;
        i++;
    }
    return 0;
}
size_t countcomma(std::string input){ //кількість чисел в рядку
    bool mode = input.find(",") != std::string::npos;
    char mchr = mode ? ',' : ' ';//можемо розділювати або пробілами або комами

    return std::count(input.begin(), input.end(), mchr) + 1;
}

double sumfx(double x){//варіант 6 - сума функцій
    return ((x-1.8)*sin(3*x)) / ((1.5*x+3)*(x+7)) + 4.2 * powf(Euler,-1.2*x);
}

double prodfx(double x){//варіант 7 - добуток функцій
    return 7 * powf(Euler, -3.3*x) + (5.5*x + 3*cos(4*x)) / (4.3*(2*x+5.1));
}

double tabfx(double x, double y){//3 завдання - таблиця значень функцій
    return log(x + sqrt(x*x + y*y));
}

/*задачі*/
void task1(std::string str, double* sum, size_t* count){
    //double* - вказівник на змінну, *sum - звернення до змінної
    size_t numslen = countcomma(str);
    for(int i=0;i<numslen;i++){
        //дістаємо число
        double n = text2nums(str,i);
        //додаємо до суми або до кількості
        if(n >= 0)  
            *sum = *sum + n;
        else
            (*count)++;
    }
}

double task2(){
    double a=0;
    double b=1;
    /* 
       i+8
        Σ sumfx(x) = for(int x=i;x<=i+8;x++) a+=sumfx(x);
       x=i
    */
    for(int x=groupno;x<=groupno+8;x++)
        a += sumfx(x);
    std::cout << "DEBUG: a = " << a << std::endl;
    /* 
       i+5
        П prodfx(x) = for(int x=i;x<=i+5;x++) b*=prodfx(x);
       x=i
    */
    for(int x=groupno;x<=groupno+5;x++)
        b *= prodfx(x);
    std::cout << "DEBUG: b = " << b << std::endl;

    //Z=tg(b) - a
    return tan(b) - a;
}

double task3(){
    //ln(x+/(x2+y2)) 1 3 0 1 0.05
    double a = 1;
    double b = 3;
    double c = 0;
    double d = 1;
    double h = 0.05;
    
    //шапка таблиці
    std::cout << "x" << std::setw(6) << "y" << std::setw(11) << "f(x,y)" << std::endl;
    for(int i=0;i<20;i++) std::cout << "_";
    std::cout << std::endl;
    
    for(double x=a; x<b+h; x+=h){
        for(double y=c; y<d+h; y+=h){
            //setw встановлює ширину поля для рівного виводу
            std::cout << std::setw(6) << std::left << x;
            std::cout << std::setw(6) << std::left << y;
            std::cout << std::setw(8) << std::left << tabfx(x,y) << std::endl;
        }
        //якщо протабулювали всі х тоді не треба питати
        if(x+h > b) break;
        Sleep(200);
        std::cout<<"Продовжити? (esc - вихід, return - продовжити)"<<std::endl;
        while(true){
            //чекаємо на подію клавіатури
            if(GetAsyncKeyState(VK_ESCAPE)) return 0;
            if(GetAsyncKeyState(VK_RETURN)) break;
        }
    }
}
bool test(){
    //test task1
    std::string seq = "1,2,3,4,5,-5,-4,-3,-2,-1";
    double sum = 0;
    size_t count = 0;
    task1(seq, &sum, &count);
    assert(sum == 15);
    assert(count == 5);

    //test task2
    assert(fabs(task2() + 0.172856) < EPS);

    //test task3
    assert(fabs(tabfx(1,1) - 0.881374) < EPS);
    
    std::cout<<"Тести пройдено успішно!"<<std::endl;
    return true;
}

/*основна функція*/
int main(){
    //set console encoding to utf-8
    SetConsoleOutputCP(CP_UTF8);

    std::string buf;   
    double sum = 0;
    size_t count = 0;
    std::cout<<"Введіть послідовність розділену комами або пробілами: \n";
    std::getline(std::cin, buf);
    task1(buf, &sum, &count);    
    std::cout<<"Сума: "<<sum<<std::endl;
    std::cout<<"Кількість від'ємних: "<<count<<std::endl;
    std::cout<<std::endl;


    std::cout<<"Значення Z: "<<task2()<<std::endl;
    std::cout << std::endl;
    

    //clear key buffer
    while(GetAsyncKeyState(VK_RETURN)){}
    std::cout << "Таблиця значень функції: " << std::endl;
    task3();
    //clear key buffer
    while(GetAsyncKeyState(VK_RETURN)){}


    std::cout<<std::endl<<"Запускаємо тести"<<std::endl;
    test();
    return 0;
}
