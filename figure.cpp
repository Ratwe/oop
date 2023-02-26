#include "figure.h"
#include "vertex.h"

// Функция для инициализации фигуры, возвращает ссылку на статический объект
// Инициализирует центр фигуры, массив вершин и массив рёбер
figure_t &figure_init(void)
{
    static figure_t tmp_figure;

    vertex_init(tmp_figure.centre);         // Инициализация центра фигуры
    vertexes_init(tmp_figure.vertexes);     // Инициализация массива вершин
    links_init(tmp_figure.links);           // Инициализация массива рёбер

    return tmp_figure;                      // Возвращает ссылку на статический объект
}

// Функция для чтения фигуры из файла
// Принимает ссылку на структуру фигуры и указатель на открытый файл для чтения
// Читает центр фигуры, массив вершин и массив рёбер из файла
err_t read_figure(figure_t &figure, FILE *file)
{
    figure = figure_init(); // Инициализация фигуры

    err_t rc = OK;

    // Чтение центра фигуры
    if ((rc = read_vertex(figure.centre, file)))
        return rc;

    // Чтение массива вершин
    if ((rc = read_vertexes(figure.vertexes, file)))
        return rc;

    // Чтение массива рёбер
    if ((rc = read_links(figure.links, file)))
    {
        destroy_vertex_arr(figure.vertexes);
        return rc;
    }

    // Проверка связности фигуры
    if ((rc = check_links(figure.links, get_vertexes_num(figure.vertexes))))
        destroy_figure(figure);

    printf("read %p, %d, %p, %d\n", figure.links.data, figure.links.len, figure.vertexes.data, figure.vertexes.len);

    return rc;
}

// Функция для загрузки фигуры из файла
// Принимает ссылку на структуру фигуры и имя файла для чтения
// Открывает файл, читает фигуру из него и закрывает файл
// Если чтение прошло успешно, обновляет фигуру
err_t load_figure(figure_t &figure, filename_t file_name)
{
    printf("filename = %s\n", file_name);

    FILE *file = fopen(file_name, "r");

    printf("file = %p\n", file);

    if (!file)
        return FILE_NAME_ERR;

    figure_t tmp_figure;

    err_t rc = read_figure(tmp_figure, file); // Чтение фигуры из файла

    fclose(file);

    if (!rc)
    {
        destroy_figure(figure);
        figure = tmp_figure;        // Обновление фигуры
    }

    printf("returning\n");
    return rc;
}

// Перемещение фигуры
err_t move_figure(figure_t &figure, const move_t &move)
{
    move_vertex(figure.centre, move);
    err_t rc = move_vertexes(figure.vertexes, move);
    return rc;
}

// Масштабирование фигуры
err_t scale_figure(figure_t &figure, const scale_t &scale)
{
    err_t rc = scale_vertexes(figure.vertexes, figure.centre, scale);
    return rc;
}

// Поворот фигуры
err_t turn_figure(figure_t &figure, const turn_t &turn)
{
    err_t rc = turn_vertexes(figure.vertexes, figure.centre, turn);
    return rc;
}

// Уничтожение фигуры
void destroy_figure(figure_t &figure)
{
    vertex_init(figure.centre);
    destroy_vertex_arr(figure.vertexes);
    destroy_links_arr(figure.links);
}
