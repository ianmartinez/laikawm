#ifndef LK_DESKTOP_H
#define LK_DESKTOP_H

#include <string>

#include "color.hpp"
#include "image.hpp"

class lk_desktop {
    public:
        bool initialized;
        lk_color background_color;
        enum lk_img_mode background_image_mode;
        std::string background_image_file;
};

#endif
