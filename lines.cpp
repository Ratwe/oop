#include <stdlib.h>

#include "figure.h"
#include "err.h"
#include "lines.h"

void lines_init(lines_arr_t &lines)
{
    lines.data = NULL;
    lines.len = 0;
}


err_t allocate_lines_arr(lines_arr_t &lines)
{
    lines.data = (line_t *) calloc(lines.len, sizeof(line_t));

    if (!lines.data)
        return MEMORY_ERR;

    return OK;
}


err_t check_line(const line_t &line, const size_t max_vertex_num)
{
    if (!line.vertex1 || line.vertex1 > max_vertex_num
        || !line.vertex2 || line.vertex2 > max_vertex_num)
        return VALUE_ERR;

    return OK;
}


err_t check_lines(const lines_arr_t &lines, const size_t max_vertex_num)
{
    err_t rc = OK;

    for (size_t i = 0; !rc && i < lines.len; i++)
        rc = check_line(lines.data[i], max_vertex_num);

    return OK;
}


err_t read_line(line_t &line, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    if (fscanf(file, "%lu%lu", &line.vertex1, &line.vertex2) != 2)
        return READ_ERR;

    return OK;
}

err_t save_line(line_t &line, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    fprintf(file, "%lu %lu\n", line.vertex1, line.vertex2);

    return OK;
}


err_t read_lines_len(lines_arr_t &lines, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    if (fscanf(file, "%lu", &lines.len) != 1)
        return READ_ERR;

    if (!lines.len)
        return VALUE_ERR;

    return OK;
}

err_t save_lines_len(lines_arr_t &lines, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    fprintf(file, "%lu\n", lines.len);

    return OK;
}


err_t read_lines_data(lines_arr_t &lines, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    for (size_t i = 0; !rc && i < lines.len; i++)
        rc = read_line(lines.data[i], file);

    return rc;
}

err_t save_lines_data(lines_arr_t &lines, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    for (size_t i = 0; !rc && i < lines.len; i++)
        rc = save_line(lines.data[i], file);

    return rc;
}


err_t read_lines(lines_arr_t &lines, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    rc = read_lines_len(lines, file);

    if (!rc)
        rc = allocate_lines_arr(lines);

    if (!rc)
        rc = read_lines_data(lines, file);

    if (rc)
        destroy_lines_arr(lines);

    return rc;
}

err_t save_lines(lines_arr_t &lines, FILE *file)
{
    err_t rc = check_file(file);
    if (rc)
        return rc;

    rc = save_lines_len(lines, file);

    if (!rc)
        rc = save_lines_data(lines, file);

    if (rc)
        destroy_lines_arr(lines);

    return rc;
}


void destroy_lines_arr(lines_arr_t &lines)
{
    free(lines.data);
    lines_init(lines);
}
