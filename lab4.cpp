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

//epsilon for float comparison
#define EPS 0.00001

/*
  Лабораторна робота 4
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

bool sorter(double a, double b){ //умова сортування
    return fabs(a) > fabs(b); 
}

void printarr(double *arr, size_t size){ //вивід масиву
    std::cout<<"[";
    for(size_t i = 0; i < size; i++){
        std::cout << arr[i] << (i+1<size?", ":"");
    }
    std::cout << "]" << std::endl;
}

/*задачі*/
double* task1(std::string str,size_t* arrlen, double a, double b){
    //double* - вказівник на масив, *sum - звернення до масиву

    size_t totlen = countcomma(str);//кількість чисел в рядку

    //вибрати пробіжок між a b, зразу порахуємо кількість елементів
    *arrlen = 0;
    for(int i=0; i<totlen; i++){
        double num = text2nums(str,i);
        if(num>=a && num<=b)
            (*arrlen)++;
    }

    //тепер створимо масив
    double* arr = new double[*arrlen];
    //і заповнимо його
    size_t pos = 0;
    for(int i=0; i<totlen; i++){
        double num = text2nums(str,i);
        if(num>=a && num<=b){
            arr[pos] = num;
            pos++;
        }
    }
    std::cout << "Не відсортований масив: ";
    printarr(arr,*arrlen);
    //сортування
    std::sort(arr, arr+(*arrlen), sorter);

    return arr;
}

bool test(){
    //test task1
    double seq[] = {1,2,3,4,5,6,7,-7,-6,-5,-4,-3,-2,-1};
    double res[] = {5,4,3,-2,2,-1,1};
    random_shuffle(&seq[0], &seq[14]);//перемішуємо масив
    std::string in = "";
    for(int i=0; i<14; i++)
        in += std::to_string(seq[i]) + ((i+1<14)?", ":"");
    
    std::cout << "Вхідний рядок: " << in << std::endl;
    
    size_t arrlen;
    double* arr = task1(in, &arrlen, -2, 5);
    std::cout << "Вихідний масив: ";
    printarr(arr, arrlen);
    
    //перевірка
    if(arrlen != 7){
        std::cerr << "Невірна кількість елементів" << std::endl;
        delete[] arr;
        assert(false);
    }
    
    for(int i=0; i<7; i++){
        //різниця між модулями має бути меншою за EPS (порівняння чисел з плаваючою точкою)
        if(fabs( fabs(arr[i]) - fabs(res[i]) ) > EPS){
            std::cerr << "Невірний елемент " << i << std::endl;
            std::cout << "Очікувано: " << res[i] << std::endl;
            std::cout << "Отримано: " << arr[i] << std::endl;
            delete[] arr;
            assert(false);
        }
    }
    
    std::cout<<"Тести пройдено успішно!"<<std::endl;
    delete[] arr;
    return true;
}

/*основна функція*/
int main(){
    //set console encoding to utf-8
    SetConsoleOutputCP(CP_UTF8);
    double a,b;
    std::string buf;   
    double* arr;
    size_t arrlen;

    std::cout<<"Введіть послідовність розділену комами або пробілами: \n";
    std::getline(std::cin, buf);
    
    std::cout<<"Введіть a: ";
    std::cin>>a;

    std::cout<<"Введіть b: "; 
    std::cin>>b;
    std::cout<<std::endl;

    arr = task1(buf, &arrlen, a, b);  

    std::cout<<"Результат: "<<std::endl;
    printarr(arr, arrlen);

    std::cout<<std::endl<<"Запускаємо тести"<<std::endl;
    test();

    delete arr;//вивільнення пам'яті
    return 0;
}
