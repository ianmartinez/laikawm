#ifndef LK_COLOR_H
#define LK_COLOR_H

struct lk_color {
    float r;
    float g;
    float b;
    float a;
};

void lk_color_to_array(struct lk_color *color, float *array);

#endif