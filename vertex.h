#ifndef VERTEXES_H
#define VERTEXES_H

#include <stdio.h>
#include "err.h"

// Структура, представляющая вершину в трехмерном пространстве
struct vertex_t
{
    double x;   // Координата x
    double y;   // Координата y
    double z;   // Координата z
};

// Структура, представляющая массив вершин
struct vertex_arr_t
{
    vertex_t *data;   // Указатель на массив вершин
    size_t len;   // Длина массива вершин
};

// Структура, представляющая вектор перемещения
struct move_t
{
    double dx;   // Компонента смещения по оси x
    double dy;   // Компонента смещения по оси y
    double dz;   // Компонента смещения по оси z
};

// Структура, представляющая вектор масштабирования
struct scale_t
{
    double kx;   // Коэффициент масштабирования по оси x
    double ky;   // Коэффициент масштабирования по оси y
    double kz;   // Коэффициент масштабирования по оси z
};

// Структура, представляющая вектор поворота
struct turn_t
{
    double x_angle;   // Угол поворота вокруг оси x
    double y_angle;   // Угол поворота вокруг оси y
    double z_angle;   // Угол поворота вокруг оси z
};

// Инициализация вершины
void vertex_init(vertex_t &vertex);

// Инициализация массива вершин
void vertexes_init(vertex_arr_t &vertexes);

// Получение количества вершин в массиве
size_t get_vertexes_num(const vertex_arr_t &vertexes);

// Чтение вершины из файла
err_t read_vertex(vertex_t &vertex, FILE *file);
err_t save_vertex(vertex_t &vertex, FILE *file);

// Чтение массива вершин из файла
err_t read_vertexes(vertex_arr_t &vertexes, FILE *file);
err_t save_vertexes(vertex_arr_t &vertexes, FILE *file);

// Перемещение вершины
void move_vertex(vertex_t &vertex, const move_t &move);

// Перемещение массива вершин
err_t move_vertexes(vertex_arr_t &vrtxs, const move_t &move);

// Масштабирование массива вершин относительно центра
err_t scale_vertexes(vertex_arr_t &vrtxs, const vertex_t &centre,
                     const scale_t &scale);

// Поворот массива вершин относительно центра
err_t turn_vertexes(vertex_arr_t &vrtxs, const vertex_t &centre,
                    const turn_t &turn);

// Уничтожение массива вершин
void destroy_vertex_arr(vertex_arr_t &vertexes);

#endif // VERTEXES_H
