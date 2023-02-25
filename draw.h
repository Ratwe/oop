#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include "figure.h"

// Определение структуры canvas_t для работы с холстом
struct canvas_t
{
    QGraphicsScene *scene; // Указатель на сцену, на которой рисуется холст
    double width; // Ширина холста
    double height; // Высота холста
};

// Отрисовка линии на холсте
void draw_line(const double x1, const double y1, const double x2, const double y2, const canvas_t &canvas);

// Очистка холста
void clear_canvas(const canvas_t &canvas);

// Отрисовка фигуры на холсте
err_t draw_figure(const figure_t &figure, const canvas_t &canvas);

#endif // DRAW_H
