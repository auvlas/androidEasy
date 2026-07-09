#include <stdio.h>
#include "sapper_backend/src/cell/cell.h"

int main() {
    cell_t cell = init_cell();
    bool loopback = true;
    while (loopback) {
        int mode = 0;
        scanf ("%d",&mode);
        switch (mode) {
            case 0:
                printf("%i\n", is_min_cell(cell));
                printf("%i\n", is_flag_cell(cell));
                break;
            case 1:
                up_flag_cell(cell);
                break;
            case 2:
                down_flag_cell(cell);
                break;
            case 3:
                up_min_cell(cell);
                break;
            case 4:
                int count_min = 0;
                scanf("%d\n",&count_min);
                set_min_near_cell(cell,count_min);
                break;
            case 5:
                printf("%i\n", get_min_near_cell(cell));
                break;
            case 6:
                loopback = false;
                break;
            default:
                break;
        }
    }
    destroy_cell(cell);
    return 0;
}
