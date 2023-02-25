#ifndef REQUEST_H
#define REQUEST_H

#include "draw.h"
#include "figure.h"

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
        filename_t filename;   // Имя файла (используется при запросе на загрузку данных из файла)
        move_t move;           // Параметры перемещения объекта
        scale_t scale;         // Параметры масштабирования объекта
        turn_t turn;           // Параметры поворота объекта
        canvas_t canvas;       // Параметры холста
    };
};


#endif // REQUEST_H
