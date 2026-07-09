#ifndef __CELL__CELL__H__
#define __CELL__CELL__H__

#include <stdbool.h>

// структура ячейки
struct cell;

// Указатель для пользователя на структуру ряда из ячеек
typedef struct cell * cell_t;


// при неудаче возвращаем ошибку(иначе 0), везде даже в инициализации
//
// Создаём ячейку
cell_t init_cell(void);

void default_cell(cell_t cell);

// Ставим флаг

void up_flag_cell(cell_t cell);

// Убираем флаг
void down_flag_cell(cell_t cell);

// Возвращаем есть ли флаг
bool is_flag_cell(cell_t cell);

// Устанавливаем мину
void up_min_cell(cell_t cell);

// Возвращаем есть ли на данной ячейке бомба
bool is_min_cell(cell_t cell);

void open_cell(cell_t cell);

bool is_open_cell(cell_t cell);

// Записываем сколько мин вокруг
void set_min_near_cell(cell_t cell, unsigned char count_min);

// Получаем сколько мин вокруг
unsigned char get_min_near_cell(cell_t cell);

// Освобождаем ресурсы
void destroy_cell(cell_t cell);


#endif
