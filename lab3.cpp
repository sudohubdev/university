#include <iostream>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <stdlib.h>
#include <Windows.h>
#define groupno 3
using namespace std;

//epsilon for float comparison
#define EPS 0.001

/*
  Лабораторна робота 3
  виконав Вітязь Денис
  Варіант 3
*/

/*допоміжні функції*/
double text2nums(std::string input,int index){
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
size_t countcomma(std::string input){
    bool mode = input.find(",") != std::string::npos;
    char mchr = mode ? ',' : ' ';

    return std::count(input.begin(), input.end(), mchr) + 1;
}

double sumfx(double x){//варіант 6
    return 1.0/(1.0+pow(x,2));
}
double prodfx(double x){//варіант 7
    return 1.0/(1.0+pow(x,2));
}
/*задачі*/

void task1(std::string str, double* sum, size_t* count){
    size_t numslen = countcomma(str);
    for(int i=0;i<numslen;i++){
        double n = text2nums(str,i);
        if(n >= 0)  
            *sum = *sum + n;
        else
            (*count)++;
        std::cout<<"номерок: "<<n<<std::endl;
    }
}
void task2(){
    
}
double task3(){

}
bool test(){
    //test task1
    assert(fabs(0 - 0) < EPS);
    
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
    return 0;
}
