#include "mins_field.h"
#include "sapper_backend/src/row/row.h"
#include <stdlib.h>
#include <time.h>

// структура минного поля
struct mins_field {
    row_t * m_rows;
    size_t m_count_rows;
    size_t m_count_columns;
    size_t m_count_mins;
    bool m_is_live : 1;
    size_t m_empty;
    size_t m_empty_open;
    size_t m_empty_close;
};

// Инициализируем минное поле
mins_field_t init_mins_field(const size_t count_rows, const size_t count_columns, const size_t count_mins) {
    size_t index_rows = 0;
    size_t index_columns = 0;
    size_t index_mins = 0;
    mins_field_t field = NULL;
    size_t * array_mins = NULL;

    if (count_rows < 1)
        goto null_rows;

    if (count_columns < 1)
        goto null_columns;

    if (count_mins > count_rows * count_columns)
        goto very_most_mins;

    array_mins = calloc(sizeof(*array_mins), count_rows);
    if (array_mins == NULL)
        goto get_not_array_mins;
    field = calloc(sizeof(*field), 1);
    if (field == NULL)
        goto get_not_memory;
    field->m_is_live = true;
    field->m_empty = count_rows * count_columns - count_mins;
    field->m_empty_open = 0;
    field->m_empty_close = field->m_empty;
    field->m_rows=calloc(sizeof(*field->m_rows), count_rows);
    if (field->m_rows == NULL)
        goto get_not_array;
    field->m_count_rows = count_rows;
    field->m_count_columns = count_columns;
    field->m_count_mins = count_mins;
    srand(time(NULL));
    for(index_mins = 0; index_mins < count_mins;index_mins++)
        array_mins[rand()%count_rows] += 1;

    for(index_rows = 0; index_rows < count_rows;index_rows++) {
        field->m_rows[index_rows] = init_row(count_columns, array_mins[index_rows]);
        if (field->m_rows[index_rows] == NULL) {
            size_t index_free = 0;
            for (index_free = 0; index_free < index_rows; index_free++) {
                destroy_row(field->m_rows[index_free]);
            }
            goto get_not_row;
        }
    }

    free(array_mins);

    for (index_columns = 0; index_columns < count_columns; index_columns++)
        set_count_mines_near_cell_row(NULL, field->m_rows[0], field->m_rows[1], index_columns);
    
    for (index_rows = 1;index_rows < (count_rows - 1); index_rows++)
        for(index_columns = 0;index_columns <count_columns;index_columns++)
            set_count_mines_near_cell_row(field->m_rows[index_rows - 1], field->m_rows[index_rows], field->m_rows[index_rows + 1], index_columns);


    for (index_columns = 0; index_columns < count_columns; index_columns++)
        set_count_mines_near_cell_row(field->m_rows[count_rows - 2], field->m_rows[count_rows - 1], NULL, index_columns);
    return field;

    for (index_rows = 0; index_rows < field->m_count_rows; index_rows++) {
        destroy_row(field->m_rows[index_rows]);
    }
get_not_row:
    free(field->m_rows);
get_not_array:
    free(field);
get_not_memory:
    free(array_mins);
get_not_array_mins:
very_most_mins:
null_columns:
null_rows:
    return NULL;
}

size_t get_count_mins_mins_field(mins_field_t field) {
    if (field != NULL)
        return field->m_count_mins;
    return 0;
}

// Получаем количество мин во круг текушей ячейки
unsigned char get_count_mins_cell_mins_field(mins_field_t field, const size_t row, const size_t column) {
    if (field !=NULL && row <field->m_count_rows)
        return get_count_mines_near_cell_row(field->m_rows[row],column);
    return 0;
}

// Есть ли мина на текущей ячейки
bool is_min_cell_mins_field(mins_field_t field, const size_t row, const size_t column) {
    if (field !=NULL && row <field->m_count_rows)
        return is_min_cell_row(field->m_rows[row],column);
    return false;
}

// Ставим флаг
void up_flag_cell_mins_field(mins_field_t field, const size_t row, const size_t column) {
    if (field !=NULL && row <field->m_count_rows)
        up_flag_cell_row(field->m_rows[row],column);
}

// Опускаем флаг
void down_flag_cell_mins_field(mins_field_t field, const size_t row, const size_t column) {
    if (field !=NULL && row <field->m_count_rows)
        down_flag_cell_row(field->m_rows[row],column);
}

// Установлен ли флаг
bool is_flag_cell_mins_field(mins_field_t field, const size_t row, const size_t column) {
    if(field !=NULL && row < field->m_count_rows)
        return is_flag_cell_row(field->m_rows[row],column);
    return false;
}

size_t get_rows_mins_field(mins_field_t field) {
    if(field != NULL)
        return field->m_count_rows;
    return 0;
}

size_t get_columns_mins_field(mins_field_t field) {
    if(field != NULL)
        return field->m_count_columns;
    return 0;
}

bool get_is_live_mins_field(mins_field_t field) {
    if (field != NULL)
        return field->m_is_live;
    return false;
}

bool is_victory_mins_field(mins_field_t field) {
    if (field != NULL)
        return field->m_empty_close == 0 && field->m_is_live;
    return false;
}

size_t get_count_empty_mins_field(mins_field_t field) {
    if (field != NULL)
        return field->m_empty;
    return 0;
}

size_t get_count_empty_open_mins_field(mins_field_t field) {
    if (field != NULL)
        return field->m_empty_open;
    return 0;
}

size_t get_count_empty_close_mins_field(mins_field_t field) {
    if (field != NULL)
        return field->m_empty_close;
    return 0;
}

unsigned char get_percent_victory_mins_field(mins_field_t field) {
    if (field != NULL) {
        return (get_count_empty_open_mins_field(field) * 100) /
                (get_count_empty_mins_field(field));
    }
    return 0;
}

static void step_success(mins_field_t field) {
    if (field != NULL) {
        field->m_empty_open++;
        field->m_empty_close--;
    }
}

bool open_cell_mins_field(mins_field_t field, const size_t row , const size_t column) {
    if(field !=NULL && row < field->m_count_rows) {
        if (is_min_cell_row(field->m_rows[row],column)) {
            field->m_is_live = false;
        } else {
            step_success(field);
            open_cell_row(field->m_rows[row],column);
        }
        return !field->m_is_live;
    }
    return false;
}

bool is_open_cell_mins_field(mins_field_t field, const size_t row , const size_t column) {
    if(field !=NULL && row < field->m_count_rows)
        return is_open_cell_row(field->m_rows[row],column);
    return false;
}

// Освобождаем ресурсы
void destroy_mins_field(mins_field_t field) {
    size_t index_rows = 0;
    if (field != NULL) {
        for(index_rows = 0;index_rows<field->m_count_rows;index_rows++)
            destroy_row(field->m_rows[index_rows]);
        free(field->m_rows);
        free(field);
    }
}
