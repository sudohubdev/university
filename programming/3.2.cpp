#pragma comment(lib,"glew32s.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//підключаємо бібіліотеки (послідовність)

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<gl/GL.h>
#include<GL/glu.h>
#include<iostream>
#include <sstream>
//роботу виконав Chatgpt під кураторством Вітязя Дениса та рецензовано віжуал студіо
using namespace std;

int Wi = 800, Hi = 600;//розміри вікна

const int splinepoints = 80;
const int flowerpoints = 27;
int totalpoints=0;
GLfloat points[][2] = {
    {0.3871, 0.1353},
    {0.3333, 0.1688},
    {0.4264, 0.3755},
    {0.4032, 0.4017},
    {0.2270, 0.2576},
    {0.1368, 0.3173},
    {0.1484, 0.4308},
    {0.4017, 0.5021},
    {0.4192, 0.5473},
    {0.1804, 0.6666},
    {0.1994, 0.7772},
    {0.2751, 0.8253},
    {0.4570, 0.5895},
    {0.5225, 0.5866},
    {0.6186, 0.8238},
    {0.7161, 0.8355},
    {0.7933, 0.7161},
    {0.5691, 0.5312},
    {0.5953, 0.4788},
    {0.8427, 0.4483},
    {0.8340, 0.3114},
    {0.7510, 0.2576},
    {0.5496, 0.4013},
    {0.5196, 0.3813},
    {0.5065, 0.1280},
    {0.3901, 0.1368},
    {0.3871, 0.1353},
    {0.3333, 0.1688},
    {0.4264, 0.3755},
    {0.4032, 0.4017}};


GLfloat pointsBSpline[3000][2];
GLfloat normals[3000][2];
//інтерполяційна функція Б сплайну (рекурсивна)
float B0(float u){
    return float(pow(1-u, 3) / 6.0);
}

float B1(float u){
    return float((3 * pow(u, 3) - 6 * pow(u, 2) + 4) / 6.0);
}

float B2(float u){
    return float((-3 * pow(u, 3) + 3 * pow(u, 2) + 3 * u + 1) / 6.0);
}

float B3(float u){
    return float(pow(u, 3) / 6.0);
}

void computeBSpline(){
    int count = 0;
    for (int i = 0; i < flowerpoints; i++)
    {
        cout << "Computing for P" << i << " P " << i + 1 << " P " << i + 2 << " P " << i + 3 << endl;
        for (int j = 0; j < splinepoints; j++)
        {

            float u = float(j) / float(splinepoints);
            int aa = (i + 1) % flowerpoints;
            int bb = (i + 2) % flowerpoints;
            int cc = (i + 3) % flowerpoints;

            float Qx = B0(u) * points[i][0] + B1(u) * points[aa][0] + B2(u) * points[bb][0] + B3(u) * points[cc][0];
            float Qy = B0(u) * points[i][1] + B1(u) * points[aa][1] + B2(u) * points[bb][1] + B3(u) * points[cc][1];

            pointsBSpline[count][0] = Qx;
            pointsBSpline[count][1] = Qy;
            //calc normals
            float Qx1 = B0(u + 0.01) * points[i][0] + B1(u + 0.01) * points[aa][0] + B2(u + 0.01) * points[bb][0] + B3(u + 0.01) * points[cc][0];
            float Qy1 = B0(u + 0.01) * points[i][1] + B1(u + 0.01) * points[aa][1] + B2(u + 0.01) * points[bb][1] + B3(u + 0.01) * points[cc][1];
            
            float dx = Qx1 - Qx;
            float dy = Qy1 - Qy;
            float len = sqrt(dx*dx + dy*dy);
            normals[count][0] = dy / len;
            normals[count][1] = -dx / len;
            //cout << count << '(' << Qx << ", " << Qy << ")\n";
            count++;
        }
    }
    totalpoints = count;
    cout << "Computed " << count << " points!\n";
}

//головна функція
int main(void)
{
    //кирилиця
    setlocale(LC_ALL, "Russian");
    GLFWwindow* window;

    for(int i=0;i<31;i++)
    {
        //convert from 0,1 to -1,1
        points[i][0] = points[i][0]*2-1;
        points[i][1] = points[i][1]*2-1;
    }

    /* ініціалізація віконної бібліотеки */
    if (!glfwInit())
        return -1;


    /* створення вікна */
    window = glfwCreateWindow(Wi, Hi, "GL", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // вказуємо вікно для малювання 
    glfwMakeContextCurrent(window);

    //нова технологія, пишеться обовязково перед glew
    glewExperimental = GL_TRUE;
    //ініціалізуємо glew і перевіряємо - виводимо повідомлення про помилку і зупиняємо програму
    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew не ініціалізовано" << std::endl;
        glfwTerminate();
        system("pause");
        return -1;
    }


    //область і позиція малювання
    glfwGetFramebufferSize(window, &Wi, &Hi);
    glViewport(0, 0, Wi, Hi);

    //рахуємо Б-сплайн
    computeBSpline();

    //Головний цикл
    while (!glfwWindowShouldClose(window)) //поки вікно не закрито
    {
        //колір очистки вікна тобто фоновий колір
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //малюємо точки квітки

        for (int i = 0; i < flowerpoints; i++)
        {
            glBegin(GL_QUADS);
            //2px dot using rectangles
            glVertex3f(points[i][0] - 0.01, points[i][1] - 0.01, 0);
            glVertex3f(points[i][0] + 0.01, points[i][1] - 0.01, 0);
            glVertex3f(points[i][0] + 0.01, points[i][1] + 0.01, 0);
            glVertex3f(points[i][0] - 0.01, points[i][1] + 0.01, 0);
            glEnd();
        }
        //малюємо червоні лінії
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < flowerpoints; i++)
        {
            glVertex3f(points[i][0], points[i][1], 0);
        }
        glEnd();

        //малюємо Б-сплайн
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < totalpoints; i++)
        {
            glVertex3f(pointsBSpline[i][0], pointsBSpline[i][1], 0);
        }
        glEnd();
        //малюємо нормалі Б-сплайну
        glColor3f(1.0, 1.0, 1.0);
        for (int i = 0; i < totalpoints; i+=10)
        {
            glBegin(GL_LINES);
            glVertex3f(pointsBSpline[i][0], pointsBSpline[i][1], 0);
            glVertex3f(pointsBSpline[i][0] + normals[i][0] * 0.1, pointsBSpline[i][1] + normals[i][1] * 0.1, 0);
            glEnd();
        }

        // перемикання буферів
        glfwSwapBuffers(window); 
        //події
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

