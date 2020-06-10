#include "include/color.hpp"

void lk_color_to_array(struct lk_color *color, float *array) {
    array[0] = color->r;
    array[1] = color->g;
    array[2] = color->b;
    array[3] = color->a;
}