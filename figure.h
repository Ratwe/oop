#ifndef FIGURE_H
#define FIGURE_H

#include "err.h"
#include "lines.h"
#include "vertex.h"

// Структура, представляющая фигуру
struct figure_t
{
    vertex_t centre;    // Центр фигуры
    vertex_arr_t vertexes;   // Массив вершин фигуры
    lines_arr_t lines;   // Массив связей между вершинами
};


// Псевдоним для типа имени файла
using filename_t = const char*;

// Инициализация вершины
void vertex_init(const figure_t figure);

// Инициализация массива вершин
void vertexes_init(const figure_t figure);

// Получение количества вершин в массиве
size_t get_vertexes_num(const figure_t figure);

// Уничтожение массива вершин
void destroy_vertex_arr(figure_t figure);



// Инициализация массива ребер
void lines_init(const figure_t figure);

// Уничтожение массива ребер
void destroy_lines_arr(figure_t figure);


err_t check_file(FILE* file);

// Инициализация фигуры
figure_t &figure_init(void);

// Загрузка фигуры из файла
err_t load_figure(figure_t &figure, filename_t file_name);
err_t save_figure(figure_t &figure, filename_t file_name);

// Перемещение фигуры
err_t move_figure(figure_t &figure, const move_t &move);

// Масштабирование фигуры
err_t scale_figure(figure_t &figure, const scale_t &scale);

// Поворот фигуры
err_t turn_figure(figure_t &figure, const turn_t &turn);

// Уничтожение фигуры
void destroy_figure(figure_t &figure);

#endif // FIGURE_H
