#include "request.h"
#include "err.h"

// Обрабатывает запрос и возвращает код ошибки
err_t handle_request(const request_t request)
{
    err_t rc = OK;
    static figure_t figure = figure_init();

//    rc = load_figure(figure, FILENAME);
//    if (rc)
//        return rc;

    switch (request.code)
    {
        case REQUEST_LOAD:
            rc = load_figure(figure, FILENAME);
            break;
        case REQUEST_MOVE:
            rc = move_figure(figure, request.move);
            break;
        case REQUEST_SCALE:
            rc = scale_figure(figure, request.scale);
            break;
        case REQUEST_TURN:
            rc = turn_figure(figure, request.turn);
            break;
        case REQUEST_DRAW:
            rc = draw_figure(figure, request.canvas);
            break;
        default:
            rc = UNKNOWN_ERR;
            break;
    }

    if (rc)
        return rc;

    rc = save_figure(figure, FILENAME);

    return rc;
}
