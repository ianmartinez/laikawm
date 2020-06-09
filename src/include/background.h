#ifndef LK_DESKTOP_H
#define LK_DESKTOP_H

#include "color.h"

enum lk_img_mode {
    LK_IMG_MODE_TILE, // No scaling, anchor top-left and tile
    LK_IMG_MODE_CENTER, // No scaling, center image
    LK_IMG_MODE_COVER, // Scale to fit screen, respecting aspect ratio
    LK_IMG_MODE_STRETCH, // Scale to fit screen, ignoring aspect ratio
}; 

struct lk_desktop {
    bool initialized;
    struct lk_color background_color;
    enum lk_img_mode background_image_mode;
    const char* background_image_file;
};

#endif