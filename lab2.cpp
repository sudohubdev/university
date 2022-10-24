#include <iostream>
#include <cmath>
#include <assert.h>
#include <Windows.h>
#define groupno 3
using namespace std;
//epsilon for float comparison
#define EPS 0.001

/*
  Лабораторна робота 2
  виконав Вітязь Денис
  Варіант 3
*/

//структура вектор для зберігання даних
struct vec2{
    double x;
    double y;
};
bool task1(float x, float y){
    //перевіряємо х, він завжди у діапазоні [0, 1]
    if(x<0 || x>1) return false;
    //верхній квадратик (у між 0 та 1)
    if(y>=0 && y<=1) return true;
    //нижня чверть кола (у між 0 та -1, радіус <= 1)
    if(y< 0 && y>=-1 && (y*y+x*x)<=1) return true;
    return false;
}
int task2(int x, int y){ 
    switch (x)
    {
    case 0:
        //коли повертаємо значення то можна і без break
        switch(y){
            case 0: return 2;
            case 1: return 0;
            case 2: return 0;
            default: throw std::invalid_argument("y має бути в діапазоні [0, 2]");
        }
        break;
    case 1:
        switch(y){
            case 0: return 2;
            case 1: return 2;
            case 2: return 0;
            default: throw std::invalid_argument("y має бути в діапазоні [0, 2]");
        } 
        break;
    case 2:
        switch(y){
            case 0: return 1;
            case 1: return 0;
            case 2: return 2;
            default: throw std::invalid_argument("y має бути в діапазоні [0, 2]");
        }
        break;

    default:
        throw invalid_argument("x має бути в діапазоні [0, 2]");
    }
}
void test(char *argv[]){
    float x,y;
    x = atof(argv[1]);
    y = atof(argv[2]);
    bool type = argv[3][0] == '1';
    if(type){
        if(task1(x,y))
            std::cout<<"1"<<std::endl;
        else
            std::cout<<"0"<<std::endl;
    }
    else{
        std::cout<<task2(x,y)<<std::endl;
    }
}
int main(int argc, char *argv[]){
    //необхідно для тестів
    if(argc>1){
        test(argv);
        return 0;
    }
    float x,y;
    bool res,rpt;
    char * ask;
    
    //set console encoding to utf-8
    SetConsoleOutputCP(CP_UTF8);
    std::cout<<"##############"<<std::endl;
    std::cout<<"# Завдання 1 #"<<std::endl;
    std::cout<<"##############"<<std::endl;

    task1:
    std::cout<<"Введіть значення координати x: ";
    std::cin>>x;
    std::cout<<"Введіть значення координати y: ";
    std::cin>>y;
    res = task1(x,y);
    std::cout<<"Точка "<<(res?"":"не ")<<"входить до заштрихованої ділянки"<<std::endl<<std::endl;
    
    std::cout<<"Чи бажаєте ви перевірити іншу точку? (Y/n): ";
    std::cin>>ask;
    if(ask[0]=='y' || ask[0]=='Y')
        goto task1;
    

    std::cout<<"##############"<<std::endl;
    std::cout<<"# Завдання 2 #"<<std::endl;
    std::cout<<"##############"<<std::endl;
   
    std::cout<<"Введіть значення x: ";
    std::cin>>x;
    std::cout<<"Введіть значення y: ";
    std::cin>>y;
    res = task2(x,y);
    std::cout<<"Результат: "<<res<<std::endl<<std::endl;
    std::cout<<"Програма завершила роботу, чи хочете ви запустити юніт-тести? (Y/n): ";
    std::cin>>ask;
    if(ask[0]=='y' || ask[0]=='Y')
        system("python tests.py");
    return 0;
}
