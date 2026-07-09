#include <stdlib.h>
#include "cell.pvt.h"
// при неудаче возвращаем ошибку(иначе 0), везде даже в инициализации
//
// Создаём ячейку
cell_t init_cell(void) {
    cell_t cell = calloc(sizeof(*cell), 1);
    if (cell == NULL)
        goto get_not_memory;
    default_cell(cell);

    return cell;
    free(cell);
get_not_memory:
    return NULL;
}

void default_cell(cell_t cell){
    cell->m_mins_near = 0;
    cell->m_is_min = false;
    cell->m_is_flag = false;
    cell->m_is_open = false;
}
// Ставим флаг
void up_flag_cell(cell_t cell) {
    if (cell != NULL)
        (*cell).m_is_flag = true;
}

// Убираем флаг
void down_flag_cell(cell_t cell) {
    if (cell != NULL)
        (*cell).m_is_flag = false;
}

// Возвращаем есть ли флаг
bool is_flag_cell(cell_t cell) {
    if (cell != NULL)
        return (*cell).m_is_flag;
    return false;
}

// Устанавливаем мину
void up_min_cell(cell_t cell) {
    if (cell != NULL)
        (*cell).m_is_min = true;
}

// Возвращаем есть ли на данной ячейке бомба
bool is_min_cell(cell_t cell) {
    if (cell != NULL)
        return (*cell).m_is_min;
    return false;
}

void open_cell(cell_t cell) {
    if (cell != NULL)
        cell->m_is_open = true;
}

bool is_open_cell(cell_t cell) {
    if (cell != NULL)
        return cell->m_is_open;
    return false;
}

// Записываем сколько мин вокруг
void set_min_near_cell(cell_t cell, unsigned char count_min) {
    if (cell != NULL && count_min <= 8)
        (*cell).m_mins_near = count_min;
}

// Получаем сколько мин вокруг
unsigned char get_min_near_cell(cell_t cell) {
    if (cell != NULL)
        return (*cell).m_mins_near;
    return 0;
}

// Освобождаем ресурсы
void destroy_cell(cell_t cell) {
    if (cell != NULL)
        free(cell);
}
