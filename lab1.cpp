#include <iostream>
#include <cmath>
#include <assert.h>
#include <Windows.h>
#define groupno 3
using namespace std;
//epsilon for float comparison
#define EPS 0.001

/*
  Лабораторна робота 1
  виконав Вітязь Денис
  Варіант 3
*/

//структура вектор для зберігання даних
struct vec2{
    double x;
    double y;
};
double task1(float x){
    return 5.6 * fabs(x) + ( x/1.8 + tan(3*x)) / (1.5*(x+2));
}
vec2 task2(){
    vec2 a = {0, 0};
    vec2 b = {groupno, groupno-1};
    vec2 c = {-groupno, groupno+1};
  
    double aa = sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
    double bb = sqrt(pow(c.x-b.x, 2) + pow(c.y-b.y, 2));
    double cc = sqrt(pow(c.x-a.x, 2) + pow(c.y-a.y, 2));

    double p=(aa+bb+cc)/2;  
    double bisector = 2*sqrt(aa*cc*p*(p-bb))/(aa+cc);
    double radius = sqrt((p-aa)*(p-bb)*(p-cc)/p);

    //return 2 values at once using vector!
    return {bisector, radius};
}
bool test(){
    //test task1
    assert(fabs(task1(0) - 0) < EPS);
    assert(fabs(task1(1) - 5.692) < EPS);
    //task2
    vec2 res = task2();
    assert(fabs(res.x - 2.879) < EPS);//bisector
    assert(fabs(res.y - 1.205) < EPS);//radius
    std::cout<<"Тести пройдено успішно!"<<std::endl;
    return true;
}
int main(){
    //set console encoding to utf-8
    SetConsoleOutputCP(CP_UTF8);
    float x;
    std::cout<<"Введіть значення x: ";
    std::cin>>x;
    double y = task1(x);
    std::cout<<"Результат: "<<y<<std::endl;
    vec2 res = task2();
    std::cout<<"Довжина бісектриси: "<<res.x<<std::endl;
    std::cout<<"Радіус кола, що вписаний в трикутник: "<<res.y<<std::endl;
    test();
    return 0;
}
