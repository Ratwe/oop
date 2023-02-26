#include <QMessageBox>

#include "err.h"

void handle_error(const err_t code)
{
    switch (code)
    {
        case OK:
            break;
        case FILE_NAME_ERR:
            QMessageBox::critical(NULL, TITLE, FILE_NAME_ERR_MSG);
            break;
        case MEMORY_ERR:
            QMessageBox::critical(NULL, TITLE, MEMORY_ERR_MSG);
            break;
        case READ_ERR:
            QMessageBox::critical(NULL, TITLE, READ_ERR_MSG);
            break;
        case VALUE_ERR:
            QMessageBox::critical(NULL, TITLE, VALUE_ERR_MSG);
            break;
        case MOVE_ERR:
            QMessageBox::critical(NULL, TITLE, MOVE_IN_ERR_MSG);
            break;
        case SCALE_ERR:
            QMessageBox::critical(NULL, TITLE, SCALE_IN_ERR_MSG);
            break;
        case TURN_ERR:
            QMessageBox::critical(NULL, TITLE, TURN_IN_ERR_MSG);
            break;
        case NO_DATA_ERR:
            QMessageBox::critical(NULL, TITLE, NO_DATA_ERR_MSG);
            break;
        case UNKNOWN_CODE_ERR:
            QMessageBox::critical(NULL, TITLE, UNKNOWN_CODE_ERR_MSG);
            break;
        case INT_ERR:
            QMessageBox::critical(NULL, TITLE, INT_ERR_MSG);
            break;
        default:
            QMessageBox::critical(NULL, TITLE, UNKNOWN_ERR_MSG);
            break;
    }
}
