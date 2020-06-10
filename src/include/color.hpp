#ifndef LK_COLOR_H
#define LK_COLOR_H

class lk_color {
   public:
    float r, g, b, a;
    lk_color();
    lk_color(float r, float g, float b, float a);
    void to_array(float *array);
};

#endif