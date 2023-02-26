#include "draw.h"

// Функция, проецирующая вершину на центр холста
void project_to_centre(vertex_t &vertex, const double width,const double height)
{
    vertex.x += width / 2;
    vertex.y += height / 2;
}

// Функция, рисующая линию на холсте
void draw_line(const double x1, const double y1, const double x2, const double y2, const canvas_t &canvas)
{
    printf("canvas.scene->addLine(%d, %d, %d, %d)\n", x1, y1, x2, y2);
    canvas.scene->addLine(x1, y1, x2, y2);
}

// Функция, рисующая линию между двумя вершинами на холсте
void draw_link(const link_t &link, const vertex_arr_t &vertexes, const canvas_t &canvas)
{
    printf("%d - %d\n", link.vertex1, link.vertex2);
    vertex_t vertex1 = vertexes.data[link.vertex1 - 1];
    vertex_t vertex2 = vertexes.data[link.vertex2 - 1];

    // Проецируем вершины на центр холста
    project_to_centre(vertex1, canvas.width, canvas.height);
    project_to_centre(vertex2, canvas.width, canvas.height);

    // Рисуем линию между вершинами
    draw_line(vertex1.x, vertex1.y, vertex2.x, vertex2.y, canvas);
}

// Функция, рисующая все линии фигуры на холсте
err_t draw_links(const links_arr_t &links, const vertex_arr_t &vertexes, const canvas_t &canvas)
{
    // Проверяем наличие данных
    if (!links.data || !links.len || !vertexes.data || !vertexes.len)
    {
        printf("NO_DATA_ERR\n");
        printf("%p, %d, %p, %d\n", links.data, links.len, vertexes.data, vertexes.len);
        return NO_DATA_ERR;
    }

    // Рисуем каждую линию в массиве
    for (size_t i = 0; i < links.len; i++)
        draw_link(links.data[i], vertexes, canvas);

    return OK;
}

// Функция, рисующая всю фигуру на холсте
err_t draw_figure(const figure_t &figure, const canvas_t &canvas)
{
    // Очищаем холст перед отрисовкой фигуры
    clear_canvas(canvas);

    // Рисуем все линии фигуры
    err_t rc = draw_links(figure.links, figure.vertexes, canvas);

    return rc;
}

// Очистить холст
void clear_canvas(const canvas_t &canvas)
{
    canvas.scene->clear();
}
