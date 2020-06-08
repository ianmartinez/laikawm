#ifndef LK_DESKTOP_H
#define LK_DESKTOP_H

#include "color.h"

struct lk_desktop {
    bool initialized;
    struct lk_color background_color;
};

#endif