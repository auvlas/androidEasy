#include "row.h"
#include "sapper_backend/src/cell/cell.h"
#include <stdlib.h>
#include <stdint.h>


// структура строки
struct row {
    cell_t * m_cells;
    size_t m_count_cells;
};

// Недоступная пользователю функция для установки одной мины(предобъявление) должна вызываться только в add_mines_row()
void add_mine_row(row_t row);

// Недоступная пользователю функция для установки нескольких мины(предобъявление) должна вызываться только в init_row()
void add_mines_row(row_t row, const size_t count_mines);

// при неудаче возвращаем ошибку(иначе 0), везде даже в инициализации
//
// Создаём строку, с переданным количеством ячеек
row_t init_row(const size_t count_cells, const size_t count_mines) {
    size_t index_cell = 0;
    row_t row = calloc(sizeof(*row),1);

    if (count_cells < 1)
        goto null_cells;
    if (row == NULL)
        goto get_not_memory;
    row->m_cells = calloc(sizeof(*row->m_cells), count_cells);
    if (row->m_cells == NULL)
        goto get_not_array;
    (*row).m_count_cells = count_cells;
    for(index_cell = 0;index_cell<count_cells;index_cell++) {
        row->m_cells[index_cell] = init_cell();
        if (row->m_cells[index_cell] == NULL) {
            size_t index_free = 0;
            for (index_free = 0; index_free < index_cell; index_free++) {
                destroy_cell(row->m_cells[index_free]);
            }
            goto get_not_cell;
        }
    }
    add_mines_row(row,count_mines);
    return row;

    for (index_cell = 0; index_cell < row->m_count_cells; index_cell++) {
        destroy_cell(row->m_cells[index_cell]);
    }
get_not_cell:
    free(row->m_cells);
get_not_array:
    free(row);
get_not_memory:
null_cells:
    return NULL;
}

// Рандомно ставим одну мину на свободную ячейку
void add_mine_row(row_t row) {
    if (row == NULL || row->m_cells == NULL)
        return;
    cell_t *cell_ptr = row->m_cells + (rand() % (*row).m_count_cells);
    cell_t * const cell_ptr_cpy = cell_ptr;
    cell_t *cell_begin = row->m_cells;
    cell_t *cell_end = cell_begin + row->m_count_cells;
    for (; cell_ptr < cell_begin + row->m_count_cells; cell_ptr++)
        if (!is_min_cell(*cell_ptr))
            goto cell_free;
    cell_ptr = cell_begin;
    for (; cell_ptr < cell_ptr_cpy; cell_ptr++)
        if (!is_min_cell(*cell_ptr))
            goto cell_free;
    return;
cell_free:
    up_min_cell(*cell_ptr);
}

// Рандомно ставим несколько мин на свободные ячейки (Несколько раз вызываем add_mine_rows())
void add_mines_row(row_t row, const size_t count_mines) {
    size_t index = 0;
    if (row != NULL)
        for(index = 0; index < count_mines; index++)
            add_mine_row(row);
}

// Ставим флаг на ячейку с переданным индексом
void up_flag_cell_row(row_t row, const size_t index_cell) {
    if (row != NULL && row->m_cells != NULL && index_cell < (*row).m_count_cells)
        up_flag_cell(row->m_cells[index_cell]);
}

// Убираем флаг на ячейку с переданным индексом
void down_flag_cell_row(row_t row, const size_t index_cell) {
    if (row != NULL && row->m_cells != NULL && index_cell < (*row).m_count_cells)
        down_flag_cell(row->m_cells[index_cell]);
}

// Является ли ячейка с индексом миной
bool is_min_cell_row(row_t row, const size_t index_cell) {
    if (row !=NULL && row->m_cells != NULL && index_cell < (*row).m_count_cells)
        return is_min_cell(row->m_cells[index_cell]);
    return false;
}

// Стоит ли флаг на ячейке с переданным индексом
bool is_flag_cell_row(row_t row, const size_t index_cell) {
    if (row !=NULL && row->m_cells != NULL && index_cell < (*row).m_count_cells)
        return is_flag_cell(row->m_cells[index_cell]);
    return false;
}

void open_cell_row(row_t row , const size_t index_cell) {
    if (row != NULL && row->m_cells != NULL && index_cell < (*row).m_count_cells)
        open_cell(row->m_cells[index_cell]);
}

bool is_open_cell_row(row_t row ,const size_t index_cell) {
    if (row != NULL && row->m_cells != NULL && index_cell < (*row).m_count_cells)
        return is_open_cell(row->m_cells[index_cell]);
    return false;
}

// Возврашаем количество мин в окружающих ячейках
unsigned char get_count_mines_near_cell_row(row_t row, const size_t index_cell) {
    if (row != NULL && row->m_cells != NULL && index_cell < (*row).m_count_cells)
        return get_min_near_cell(row->m_cells[index_cell]);
    return 0;
}

// Записываем в ячейку сколько мин в ней плюс окружающих клетках
void set_count_mines_near_cell_row(row_t top /* Верх */, \
        row_t central /* Центер */, row_t bottom /* Низ */, const size_t index_cell) {
    unsigned char count_min = 0;

    if (central == NULL && index_cell < central->m_count_cells)
        return;

    if (top != NULL && index_cell < top->m_count_cells) {
        if (index_cell != 0)
            count_min += is_min_cell(top->m_cells[index_cell - 1]);
        count_min += is_min_cell(top->m_cells[index_cell]);
        if (index_cell + 1 < top->m_count_cells)
            count_min += is_min_cell(top->m_cells[index_cell + 1]);
    }
    if (index_cell != 0)
        count_min += is_min_cell(central->m_cells[index_cell - 1]);
    if (index_cell + 1 < central->m_count_cells)
        count_min += is_min_cell(central->m_cells[index_cell + 1]);
    if (bottom != NULL && index_cell < bottom->m_count_cells) {
        if (index_cell != 0)
            count_min += is_min_cell(bottom->m_cells[index_cell - 1]);
        count_min += is_min_cell(bottom->m_cells[index_cell]);
        if (index_cell + 1 < bottom->m_count_cells)
            count_min += is_min_cell(bottom->m_cells[index_cell + 1]);
    }
    set_min_near_cell(central->m_cells[index_cell], count_min);
}

// Освобождаем ресурсы
void destroy_row(row_t row) {
    size_t index_cell = 0;
    if (row != NULL) {
        for(index_cell = 0;index_cell<row->m_count_cells;index_cell++)
            destroy_cell(row->m_cells[index_cell]);
        free(row->m_cells);
        free(row);
    }
}
