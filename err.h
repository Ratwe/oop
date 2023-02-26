#ifndef ERR_H
#define ERR_H

#define TITLE             "Ошибка"
#define FILE_NAME_ERR_MSG "Не удалось открыть файл!"
#define MEMORY_ERR_MSG    "Не удалось выделить память!"
#define READ_ERR_MSG      "Неверный формат данных в файле!"
#define VALUE_ERR_MSG     "Неверные значения данных в файле!"
#define MOVE_IN_ERR_MSG   "Коэффициенты переноса должны \
                           быть вещественными числами!"
#define SCALE_IN_ERR_MSG  "Коэффициенты масштабирования должны \
                           быть вещественными числами!"
#define TURN_IN_ERR_MSG   "Коэффициенты поворота должны \
                           быть вещественными числами!"
#define NO_DATA_ERR_MSG   "Фигура не загружена!"
#define UNKNOWN_CODE_ERR_MSG "Неизвестная команда!"
#define UNKNOWN_ERR_MSG      "Неизвестная ошибка!"
#define INT_ERR_MSG          "Недопустимое число!"

enum err_t {
    OK,
    FILE_NAME_ERR,
    UNKNOWN_ERR,
    NO_DATA_ERR,
    MEMORY_ERR,
    READ_ERR,
    VALUE_ERR,
    MOVE_ERR,
    SCALE_ERR,
    TURN_ERR,
    UNKNOWN_CODE_ERR,
    INT_ERR,
    PRINT_ERR
};

void handle_error(const err_t code);

#endif // ERR_H
