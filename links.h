#ifndef LINKS_H
#define LINKS_H

#include <stdio.h>
#include "err.h"

// Структура, описывающая ребро
struct link_t
{
    size_t vertex1;
    size_t vertex2;
};

// Структура, описывающая массив ребер
struct links_arr_t
{
    link_t *data;
    size_t len;
};

// Инициализация массива ребер
void links_init(links_arr_t &links);

// Чтение массива ребер из файла
err_t read_links(links_arr_t &links, FILE *file);

// Проверка корректности массива ребер
err_t check_links(const links_arr_t &links, const size_t max_vertex_num);

// Уничтожение массива ребер
void destroy_links_arr(links_arr_t &links);

#endif // LINKS_H
