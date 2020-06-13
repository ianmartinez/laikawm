#ifndef LK_RECT_H
#define LK_RECT_H

#include <stdint.h>

struct lk_point {
    uint16_t x;
    uint16_t y;
};

struct lk_rect {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
};

struct lk_size {
    uint16_t width;
    uint16_t height;
};

struct lk_sides {
    uint16_t top;
    uint16_t bottom;
    uint16_t left;
    uint16_t right;
};

struct lk_view_constraints {
    double min_width;
    double min_height;
    double max_width;
    double max_height;
};

#endif

