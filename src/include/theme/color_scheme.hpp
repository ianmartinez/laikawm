#ifndef LK_COLOR_SCHEME_H
#define LK_COLOR_SCHEME_H

#include "color.hpp"

class lk_color_scheme {
public:
    /**
     * Desktop
     */
    lk_color background;
    
    /**
     * Window
     */
    lk_color window_active_border;
    lk_color window_active_titlebar;
    lk_color window_active_titlebar_text;
    lk_color window_inactive_border;
    lk_color window_inactive_titlebar;
    lk_color window_inactive_titlebar_text;
    
    /**
     * Panel
     */
    lk_color panel_border;
    lk_color panel_fill;
    lk_color panel_text;
};

#endif
