#ifndef REQUEST_H
#define REQUEST_H

#include "draw.h"

#define filename "D:/Code/QT/lab_01/data.txt"

// Перечисление кодов запросов
enum request_code_t
{
    REQUEST_LOAD,   // Загрузка данных из файла
    REQUEST_MOVE,   // Перемещение объекта
    REQUEST_SCALE,  // Масштабирование объекта
    REQUEST_TURN,   // Поворот объекта
    REQUEST_CANVAS, // Изменение параметров холста
    REQUEST_DRAW,   // Отрисовка на холсте
    REQUEST_QUIT    // Выход из программы
};

// Структура, представляющая запрос
struct request_t
{
    request_code_t code;    // Код запроса
    union                   // Объединение для передачи параметров запроса в зависимости от кода
    {
        move_t move;           // Параметры перемещения объекта
        scale_t scale;         // Параметры масштабирования объекта
        turn_t turn;           // Параметры поворота объекта
        canvas_t canvas;       // Параметры холста
    };
};

// Обрабатывает запрос и возвращает код ошибки
err_t handle_request(const request_t request);

#endif // REQUEST_H
