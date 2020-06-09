#include "color.h"

void lk_color_to_array(struct lk_color *color, float array[static 4]) {
    array[0] = color->r;
    array[1] = color->g;
    array[2] = color->b;
    array[3] = color->a;
}