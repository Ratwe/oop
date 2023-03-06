#include "figure.h"
#include "vertex.h"
#include "figure.h"

err_t open_file(const char *file_name, FILE **file, const char* mode)
{
    FILE *buff = fopen(file_name, mode);
    if (!buff)
        return FILE_NAME_ERR;

    *file = buff;

    return OK;
}

err_t check_file(FILE* file)
{
    if (!file) {
        return ERR_BADF; // Bad file descriptor
    }

    if (ferror(file)) {
        clearerr(file); // clear error flag
        return ERR_IO; // I/O error
    }

    if (feof(file)) {
        clearerr(file); // clear EOF flag
        return ERR_EOF; // End of file
    }

    return OK; // no error
}


// Функция для инициализации фигуры, возвращает ссылку на статический объект
// Инициализирует центр фигуры, массив вершин и массив рёбер
figure_t &figure_init(void)
{
    static figure_t tmp_figure;

    vertex_init(tmp_figure.centre);         // Инициализация центра фигуры
    vertexes_init(tmp_figure.vertexes);     // Инициализация массива вершин
    lines_init(tmp_figure.lines);           // Инициализация массива рёбер

    return tmp_figure;                      // Возвращает ссылку на статический объект
}

// Функция для чтения фигуры из файла
// Принимает ссылку на структуру фигуры и указатель на открытый файл для чтения
// Читает центр фигуры, массив вершин и массив рёбер из файла
err_t read_figure(figure_t &figure, FILE *file)
{
    // !!! проверка файла - недоверяем
    check_file(file);

    figure = figure_init(); // Инициализация фигуры

    err_t rc = OK;

    // Чтение центра фигуры
    if ((rc = read_vertex(figure.centre, file)))
        return rc;

    // Чтение массива вершин
    if ((rc = read_vertexes(figure.vertexes, file)))
        return rc;

    // Чтение массива рёбер
    if ((rc = read_lines(figure.lines, file)))
    {
        destroy_vertex_arr(figure.vertexes);
        return rc;
    }

    // Проверка связности фигуры
    if ((rc = check_lines(figure.lines, get_vertexes_num(figure.vertexes))))
        destroy_figure(figure);

    return rc;
}

// Функция для загрузки фигуры из файла
// Принимает ссылку на структуру фигуры и имя файла для чтения
// Открывает файл, читает фигуру из него и закрывает файл
// Если чтение прошло успешно, обновляет фигуру
err_t load_figure(figure_t &figure, filename_t file_name)
{
    // !!!! в отдельную функцию
    FILE *file = NULL;
    err_t rc = open_file(file_name, &file, "r");

    if (rc)
        return rc;

    figure_t tmp_figure;

    rc = read_figure(tmp_figure, file); // Чтение фигуры из файла

    fclose(file);

    if (!rc)
    {
        destroy_figure(figure);
        figure = tmp_figure;        // Обновление фигуры
    }

    return rc;
}

// Сохраняем данные фигуры в файл
err_t save_figure(figure_t &figure, filename_t file_name)
{
    FILE *file = NULL;
    err_t rc = open_file(file_name, &file, "w");

    if (rc)
        return rc;

    figure_t tmp_figure;

    if ((rc = save_vertex(figure.centre, file)))
        return rc;

    if ((rc = save_vertexes(figure.vertexes, file)))
        return rc;

    if ((rc = save_lines(figure.lines, file)))
        return rc;

    fclose(file);

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
    destroy_lines_arr(figure.lines);
}
