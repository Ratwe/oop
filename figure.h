#ifndef FIGURE_H
#define FIGURE_H

#include "err.h"
#include "vertex.h"
#include "links.h"

// Псевдоним для типа имени файла
using filename_t = const char*;

// Структура, представляющая фигуру
struct figure_t
{
    vertex_t centre;    // Центр фигуры
    vertex_arr_t vertexes;   // Массив вершин фигуры
    links_arr_t links;   // Массив связей между вершинами
};

// Инициализация фигуры
figure_t &figure_init(void);

// Загрузка фигуры из файла
err_t load_figure(figure_t &figure, filename_t file_name);

// Перемещение фигуры
err_t move_figure(figure_t &figure, const move_t &move);

// Масштабирование фигуры
err_t scale_figure(figure_t &figure, const scale_t &scale);

// Поворот фигуры
err_t turn_figure(figure_t &figure, const turn_t &turn);

// Уничтожение фигуры
void destroy_figure(figure_t &figure);

#endif // FIGURE_H
