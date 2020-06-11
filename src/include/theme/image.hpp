#ifndef LK_IMAGE_H
#define LK_IMAGE_H

#include <cairo/cairo.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

enum lk_img_mode {
    LK_IMG_MODE_TILE,     // No scaling, anchor top-left and tile
    LK_IMG_MODE_CENTER,   // No scaling, center image
    LK_IMG_MODE_COVER,    // Scale to fit screen, respecting aspect ratio
    LK_IMG_MODE_STRETCH,  // Scale to fit screen, ignoring aspect ratio
};

#endif
