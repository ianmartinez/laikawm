#ifndef LK_DESKTOP_H
#define LK_DESKTOP_H

#include "color.hpp"
#include <string>

enum lk_img_mode {
    LK_IMG_MODE_TILE,     // No scaling, anchor top-left and tile
    LK_IMG_MODE_CENTER,   // No scaling, center image
    LK_IMG_MODE_COVER,    // Scale to fit screen, respecting aspect ratio
    LK_IMG_MODE_STRETCH,  // Scale to fit screen, ignoring aspect ratio
};

class lk_desktop {
   public:
    bool initialized;
    lk_color background_color;
    enum lk_img_mode background_image_mode;
    std::string background_image_file;
};

#endif