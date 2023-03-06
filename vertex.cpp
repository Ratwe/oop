#include "vertex.h"
#include "err.h"
#include "figure.h"
#include <cmath>
#include <qDebug>

// Функция to_radians() преобразует угол в градусах в радианы.
// Она использует значение PI (3.14159265358979323846),
// чтобы перевести угол в градусах в радианы, так как
// 180 градусов равно PI радианам.
// Функция возвращает результат в радианах.
double to_radians(double angle)
{
    return M_PI / 180 * angle;
}

// Функция vertex_init() инициализирует координаты вершины нулями.
// Она принимает структуру vertex_t и изменяет ее поля.
void vertex_init(vertex_t &vertex)
{
    vertex.x = 0;
    vertex.y = 0;
    vertex.z = 0;
}

// Функция vertexes_init() инициализирует массив вершин нулями.
// Она устанавливает указатель на ноль и длину массива в ноль.
// Функция не изменяет память, зарезервированную для массива.
void vertexes_init(vertex_arr_t &vertexes)
{
    vertexes.data = NULL;
    vertexes.len = 0;
}

// Функция get_vertexes_num() возвращает количество вершин в массиве.
// Она принимает структуру vertex_arr_t и возвращает ее длину.
size_t get_vertexes_num(const vertex_arr_t &vertexes)
{
    return vertexes.len;
}

// Функция allocate_vertex_arr() выделяет память для массива вершин.
// Она принимает структуру vertex_arr_t и выделяет память под
// vertexes.len вершин, используя функцию malloc().
// Если выделение памяти не удалось, функция возвращает MEMORY_ERR.
// Если выделение памяти успешно, функция возвращает OK.
err_t allocate_vertex_arr(vertex_arr_t &vertexes)
{
    vertex_t *buff = (vertex_t *) malloc(sizeof(vertex_t) * vertexes.len);

    if (!buff)
        return MEMORY_ERR;

    vertexes.data = buff;

    return OK;
}

// Функция чтения координат вершины из файла
// Входные параметры: ссылка на структуру вершины, указатель на файл
// Возвращаемое значение: код ошибки (OK, READ_ERR)
err_t read_vertex(vertex_t &vertex, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    if (fscanf(file, "%lf%lf%lf", &vertex.x, &vertex.y, &vertex.z) != 3)
        return READ_ERR;

    return OK;
}

err_t save_vertex(vertex_t &vertex, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    fprintf(file, "%lf %lf %lf\n", vertex.x, vertex.y, vertex.z);

    return OK;
}

// Функция чтения количества вершин из файла
// Входные параметры: ссылка на массив вершин, указатель на файл
// Возвращаемое значение: код ошибки (OK, READ_ERR, VALUE_ERR)
err_t read_vertexes_len(vertex_arr_t &vertexes, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    if (fscanf(file, "%lu", &vertexes.len) != 1)
        return READ_ERR;

    if (!vertexes.len)
        return VALUE_ERR;

    return OK;
}

err_t save_vertexes_len(vertex_arr_t &vertexes, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    fprintf(file, "%lu\n", vertexes.len);

    return OK;
}

// Функция чтения координат всех вершин из файла
// Входные параметры: ссылка на массив вершин, указатель на файл
// Возвращаемое значение: код ошибки (OK, READ_ERR)
err_t read_vertexes_data(vertex_arr_t &vertexes, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    for (size_t i = 0; !rc && i < vertexes.len; i++)
        rc = read_vertex(vertexes.data[i], file);

    return rc;
}

err_t save_vertexes_data(vertex_arr_t &vertexes, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    for (size_t i = 0; !rc && i < vertexes.len; i++)
        rc = save_vertex(vertexes.data[i], file);

    return rc;
}

// Функция чтения всех вершин из файла
// Входные параметры: ссылка на массив вершин, указатель на файл
// Возвращаемое значение: код ошибки (OK, READ_ERR, MEMORY_ERR)
err_t read_vertexes(vertex_arr_t &vertexes, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    rc = read_vertexes_len(vertexes, file);

    if (!rc)
        rc = allocate_vertex_arr(vertexes);

    if (!rc)
        rc = read_vertexes_data(vertexes, file);

    if (rc)
        destroy_vertex_arr(vertexes);

    return rc;
}

err_t save_vertexes(vertex_arr_t &vertexes, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    rc = save_vertexes_len(vertexes, file);

    if (!rc)
        rc = save_vertexes_data(vertexes, file);

    if (rc)
        destroy_vertex_arr(vertexes);

    return rc;
}

// Функция изменения координат вершины на заданное расстояние
// Входные параметры: ссылка на структуру вершины, структура перемещения
// Возвращаемое значение: отсутствует
void move_vertex(vertex_t &vertex, const move_t &move)
{
    vertex.x += move.dx;
    vertex.y += move.dy;
    vertex.z += move.dz;
}

// Функция масштабирования координат вершины относительно центра масштабирования
// Входные параметры: ссылка на структуру вершины, структура центра масштабирования, структура масштабирования
// Возвращаемое значение: отсутствует
void scale_vertex(vertex_t &vertex, const vertex_t centre, const scale_t &scale)
{
    vertex.x = centre.x + scale.kx * (vertex.x - centre.x);
    vertex.y = centre.y + scale.ky * (vertex.y - centre.y);
    vertex.z = centre.z + scale.kz * (vertex.z - centre.z);
}

// Функция поворота вершины вокруг оси X на заданный угол
void xturn_vertex(vertex_t &vertex, const double angle)
{
    double rad_angle = to_radians(angle); // переводим угол из градусов в радианы
    double cos_a = cos(rad_angle); // вычисляем косинус угла
    double sin_a = sin(rad_angle); // вычисляем синус угла
    double tmp_y = vertex.y;

    // производим поворот вершины вокруг оси X через матрицы
    vertex.y = vertex.y * cos_a - vertex.z * sin_a;
    vertex.z = tmp_y * sin_a + vertex.z * cos_a;
}

// Функция поворота вершины вокруг оси Y на заданный угол
void yturn_vertex(vertex_t &vertex, const double angle)
{
    double rad_angle = to_radians(angle); // переводим угол из градусов в радианы
    double cos_a = cos(rad_angle); // вычисляем косинус угла
    double sin_a = sin(rad_angle); // вычисляем синус угла
    double tmp_x = vertex.x;

    // производим поворот вершины вокруг оси Y
    vertex.x = vertex.x * cos_a - vertex.z * sin_a;
    vertex.z = tmp_x * sin_a + vertex.z * cos_a;
}

// Функция поворота вершины вокруг оси Z на заданный угол
void zturn_vertex(vertex_t &vertex, const double angle)
{
    double rad_angle = to_radians(angle); // переводим угол из градусов в радианы
    double cos_a = cos(rad_angle); // вычисляем косинус угла
    double sin_a = sin(rad_angle); // вычисляем синус угла
    double tmp_x = vertex.x;

    // производим поворот вершины вокруг оси Z
    vertex.x = vertex.x * cos_a - vertex.y * sin_a;
    vertex.y = tmp_x * sin_a + vertex.y * cos_a;
}

// Функция перемещения массива вершин на заданное расстояние
err_t move_vertexes(vertex_arr_t &vertexes, const move_t &move)
{
    if (!vertexes.data || !vertexes.len)
        return NO_DATA_ERR; // если массив пуст или его длина равна нулю, возвращаем ошибку

    // производим перемещение каждой вершины массива на заданное расстояние
    for (size_t i = 0; i < vertexes.len; i++)
        move_vertex(vertexes.data[i], move);

    return OK; // если все прошло успешно, возвращаем ОК
}

// Масштабирование массива вершин относительно заданной центральной точки
err_t scale_vertexes(vertex_arr_t &vertexes, const vertex_t &centre, const scale_t &scale)
{
    if (!vertexes.data || !vertexes.len)
        return NO_DATA_ERR;


    for (size_t i = 0; i < vertexes.len; i++)
    {
        // Вычисляем разницу координат вершины и центральной точки
        vertex_t diff = {vertexes.data[i].x - centre.x,
                         vertexes.data[i].y - centre.y,
                         vertexes.data[i].z - centre.z};
        // Масштабируем разницу координат с помощью заданных коэффициентов
        diff.x *= scale.kx;
        diff.y *= scale.ky;
        diff.z *= scale.kz;
        // Перемещаем вершину обратно на место, добавляя координаты центральной точки
        vertexes.data[i].x = diff.x + centre.x;
        vertexes.data[i].y = diff.y + centre.y;
        vertexes.data[i].z = diff.z + centre.z;
    }

    return OK;
}

// Перемещение вершины к центральной точке
void move_to_centre(vertex_t &vertex, const vertex_t &centre)
{
    vertex.x -= centre.x;
    vertex.y -= centre.y;
    vertex.z -= centre.z;
}

// Возвращение вершины на место после перемещения к центральной точке
void move_back(vertex_t &vertex, const vertex_t &centre)
{
    vertex.x += centre.x;
    vertex.y += centre.y;
    vertex.z += centre.z;
}

// Поворот вершины относительно заданной центральной точки
void turn_vertex(vertex_t &vertex, const vertex_t &centre, const turn_t &turn)
{
    // Перемещаем вершину к центральной точке
    move_to_centre(vertex, centre);
    // Поворачиваем вершину вокруг оси X на заданный угол
    xturn_vertex(vertex, turn.x_angle);
    // Поворачиваем вершину вокруг оси Y на заданный угол
    yturn_vertex(vertex, turn.y_angle);
    // Поворачиваем вершину вокруг оси Z на заданный угол
    zturn_vertex(vertex, turn.z_angle);
    // Возвращаем вершину на место
    move_back(vertex, centre);
}

// Поворачивает все вершины в массиве относительно центральной точки
// на углы, заданные в структуре turn.
err_t turn_vertexes(vertex_arr_t &vertexes, const vertex_t &centre, const turn_t &turn)
{
    if (!vertexes.data || !vertexes.len)
        return NO_DATA_ERR;

    for (size_t i = 0; i < vertexes.len; i++)
        turn_vertex(vertexes.data[i], centre, turn);

    return OK;
}

// Освобождает память, выделенную под массив вершин.
void destroy_vertex_arr(vertex_arr_t &vertexes)
{
    free(vertexes.data);
    vertexes_init(vertexes);
}
