#include "draw.h"

// Функция, проецирующая вершину на центр холста
void project_to_centre(vertex_t &vertex, const canvas_t &canvas)
{
    vertex.x += canvas.width / 2;
    vertex.y += canvas.height / 2;
}

// Функция, рисующая линию на холсте
void draw_canvas_line(const vertex_t &vertex1, const vertex_t &vertex2, const canvas_t &canvas)
{
    canvas.scene->addLine(vertex1.x, vertex1.y, vertex2.x, vertex2.y);
}

// Геттер вершины
vertex_t get_vertex(const vertex_arr_t &vertexes, const int num)
{
    return vertexes.data[num - 1];
}

// Функция, рисующая линию между двумя вершинами на холсте
void draw_line(const line_t &line, const vertex_arr_t &vertexes, const canvas_t &canvas)
{
    vertex_t vertex1 = get_vertex(vertexes, line.vertex1);
    vertex_t vertex2 = get_vertex(vertexes, line.vertex2);

    // Проецируем вершины на центр холста
    project_to_centre(vertex1, canvas);
    project_to_centre(vertex2, canvas);

    // Рисуем линию между вершинами
    draw_canvas_line(vertex1, vertex2, canvas);
}

// Функция, рисующая все линии фигуры на холсте
err_t draw_lines(const lines_arr_t &lines, const vertex_arr_t &vertexes, const canvas_t &canvas)
{
    // Проверяем наличие данных
    if (!lines.data || !lines.len || !vertexes.data || !vertexes.len)
        return NO_DATA_ERR;

    // Рисуем каждую линию в массиве
    for (size_t i = 0; i < lines.len; i++)
        draw_line(lines.data[i], vertexes, canvas);

    return OK;
}

// Функция, рисующая всю фигуру на холсте
err_t draw_figure(const figure_t &figure, const canvas_t &canvas)
{
    // Очищаем холст перед отрисовкой фигуры
    clear_canvas(canvas);

    // Рисуем все линии фигуры
    err_t rc = draw_lines(figure.lines, figure.vertexes, canvas);

    return rc;
}

// Очистить холст
void clear_canvas(const canvas_t &canvas)
{
    canvas.scene->clear();
}
