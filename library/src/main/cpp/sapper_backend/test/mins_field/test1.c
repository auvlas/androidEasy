#include <stdio.h>
#include "sapper_backend/src/mins_field/mins_field.h"

void show_field(mins_field_t field) {
    size_t row = 0 ,column = 0;
    size_t const row_end = get_rows_mins_field(field);
    size_t const column_end = get_columns_mins_field(field);
    for (row = 0; row < row_end;row++) {
        for(column = 0; column < column_end; column++)
            printf("%c ", is_open_cell_mins_field(field, row, column) ? 
                    '0' + get_count_mins_cell_mins_field(field,row , column) : 
                    (is_flag_cell_mins_field(field, row, column) ? '/' : '*'));
        printf("\n");
    }
}

bool do_step(mins_field_t field) {
    size_t row = 0;
    size_t column = 0;
    int action = 0;
    printf("введите строку\n");
    scanf ("%zu",&row);
    printf("введите столбец\n");
    scanf ("%zu",&column);
invalid_action:
    printf("введите действие\n");
    printf("0 - открыть ячейку\n");
    printf("1 - поставить/опустить флаг\n");
    printf("2 - отмена\n"); 
    scanf("%hhd",&action);
    switch (action) {
        case 0: 
            return open_cell_mins_field(field , row , column);
            break;
        case 1:
            if (is_flag_cell_mins_field(field, row , column))
                down_flag_cell_mins_field(field , row , column);
            else
                up_flag_cell_mins_field(field , row , column);
            break;
        case 2:
            break;
        default:
            goto invalid_action;
    }
    return true;
}

int main(void) {
    mins_field_t field = NULL;
    size_t count_rows = 0,count_columns = 0 , count_mins = 0;
    bool loopback = true;
    int mode = 0;
    printf("введите количество строк\n");
    scanf ("%zu", &count_rows);
    printf("введите количество столбцов\n");
    scanf("%zu", &count_columns);
    printf("введите количество мин\n");
    scanf ("%zu", &count_mins);
    field = init_mins_field(count_rows, count_columns, count_mins);
    while(loopback) {
        switch (mode) {
            case 0:
                printf("0 - подсказка\n");
                printf("1 - показать поле\n");
                printf("2 - сделать ход\n");
                printf("3 - выход\n");
                break;
            case 1:
                show_field(field);
                break;
            case 2:
                if (!do_step(field)) {
                    printf("invalid\n");
                    goto end;
                } else if (is_victory_mins_field(field)) {
                    printf("You win\n");
                    goto end;
                }
                break;
            case 3:
                loopback = false;
                continue;
                break;
        }
        scanf("%hhd", &mode);
    }
end:
    destroy_mins_field(field);
}
