#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

GLuint VBO; //Объявление переменной-идентификатора буфера вершин.

static void RenderSceneCB() //Функция, которая будет вызываться для отрисовки сцены. Внутри функции:
{
    glClear(GL_COLOR_BUFFER_BIT); //Очистка буфера цвета.

    glEnableVertexAttribArray(0); //Включение массива атрибутов вершин.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Привязка буфера вершин.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Указание способа интерпретации данных вершин (здесь: 3 координаты, тип данных float).

    glDrawArrays(GL_TRIANGLES, 0, 3);//Вызов функции отрисовки примитивов (здесь: треугольников).

    glColor3f(1.0f, 1.0f, 1.0f); // ЦВЕТ ТРЕУГОЛЬНИКА
    glDisableVertexAttribArray(0);//Отключение массива атрибутов вершин.

    glutSwapBuffers();//Переключение буферов (для двойной буферизации).
}

//Функция для установки обратного вызова для отрисовки сцены. Здесь она вызывает функцию RenderSceneCB.
static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}
//Функция для создания буфера вершин. Здесь создаются три вершины, затем создается буфер вершин,  привязывается к контексту OpenGL и заполняется данными вершин.

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);  // генерация буфера вершин.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  //привязка буфера вершин к текущему контексту.
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);  //заполнение буфера вершин данными из массива.
}





int main(int argc, char** argv)// это функция main программы, которая принимает аргументы командной строки и возвращает целочисленное значение.
{
    glutInit(&argc, argv);  // инициализирует библиотеку GLUT и передает ей аргументы командной строки.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  //задает режим отображения окна, в данном случае используется двойная буферизация и цветовая модель RGBA.
    glutInitWindowSize(1024, 768);  //устанавливает размеры окна. (ШИРИНА, ВЫСОТА)
    glutInitWindowPosition(100, 100);  //устанавливает позицию окна на экране.
    glutCreateWindow("Samikov D.Z. PRO-231B");  //создает окно с заголовком 

    InitializeGlutCallbacks();  //устанавливает функцию обратного вызова для отрисовки сцены.

    GLenum res = glewInit();  //инициализирует библиотеку GLEW и проверяет наличие всех необходимых расширений OpenGL.
    if (res != GLEW_OK)  //проверяет успешность инициализации GLEW.
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res)); // выводит сообщение об ошибке в поток ошибок.
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //ЦВЕТ ФОНА

    CreateVertexBuffer(); //создает буфер вершин.

    glutMainLoop(); //запускает бесконечный цикл обработки сообщений GLUT.
    return 0;
}
