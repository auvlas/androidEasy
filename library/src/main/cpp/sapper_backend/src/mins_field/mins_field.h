#ifndef __MINS_FIELD__MINS_FIELD__H__
#define __MINS_FIELD__MINS_FIELD__H__

#include <stddef.h>
#include <stdbool.h>

// структура минного поля
struct mins_field;

// Указатель на минное поле для пользователя
typedef struct mins_field * mins_field_t;

// Инициализируем минное поле
mins_field_t init_mins_field(const size_t count_rows, const size_t count_columns, const size_t count_mins);

size_t get_count_mins_mins_field(mins_field_t field);

// Получаем количество мин во круг текушей ячейки
unsigned char get_count_mins_cell_mins_field(mins_field_t field, const size_t row, const size_t column);

// Есть ли мина на текущей ячейки
bool is_min_cell_mins_field(mins_field_t field, const size_t row, const size_t column);

// Ставим флаг
void up_flag_cell_mins_field(mins_field_t field, const size_t row, const size_t column);

// Опускаем флаг
void down_flag_cell_mins_field(mins_field_t field, const size_t row, const size_t column);

// Установлен ли флаг
bool is_flag_cell_mins_field(mins_field_t field, const size_t row, const size_t column);

size_t get_rows_mins_field(mins_field_t field);

size_t get_columns_mins_field(mins_field_t field);

bool get_is_live_mins_field(mins_field_t field);

bool is_victory_mins_field(mins_field_t field);

size_t get_count_empty_mins_field(mins_field_t field);

size_t get_count_empty_open_mins_field(mins_field_t field);

size_t get_count_empty_close_mins_field(mins_field_t field);

unsigned char get_percent_victory_mins_field(mins_field_t field);

bool open_cell_mins_field(mins_field_t field, const size_t row , const size_t column);

bool is_open_cell_mins_field(mins_field_t field, const size_t row , const size_t column);

// Освобождаем ресурсы
void destroy_mins_field(mins_field_t field);


#endif