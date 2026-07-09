#ifndef __CELL__CELL_PVT__H__
#define __CELL__CELL_PVT__H__

#include "cell.h"
// структура ячейки
struct cell {
    unsigned char m_mins_near;
    bool m_is_min : 1;
    bool m_is_flag : 1;
    bool m_is_open : 1;
};

#endif