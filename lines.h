#ifndef LINES_H
#define LINES_H

#include <stdio.h>
#include "err.h"

// Структура, описывающая ребро
struct line_t
{
    size_t vertex1;
    size_t vertex2;
};

// Структура, описывающая массив ребер
struct lines_arr_t
{
    line_t *data;
    size_t len;
};

// Чтение массива ребер из файла
err_t read_lines(lines_arr_t &lines, FILE *file);
err_t save_lines(lines_arr_t &lines, FILE *file);

// Проверка корректности массива ребер
err_t check_lines(const lines_arr_t &lines, const size_t max_vertex_num);

#endif // LINES_H
