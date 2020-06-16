#ifndef LK_DESKTOP_H
#define LK_DESKTOP_H

#include <string>

#include "color.hpp"
#include "color_scheme.hpp"
#include "image.hpp"
#include "theme.hpp"

class lk_desktop {
    public:
        bool initialized;
        enum lk_img_mode background_image_mode;
        std::string background_image_file;
        
        lk_theme theme;
};

#endif
