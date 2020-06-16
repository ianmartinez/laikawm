#ifndef LK_DEFAULT_THEME_H
#define LK_DEFAULT_THEME_H

#include "theme.hpp"
#include "color.hpp"
#include "color_scheme.hpp"

/**
 * The default color scheme to fall back to.
 */
lk_color_scheme DEFAULT_COLORS = {
    .background = lk_color(0.0, 0.5, 0.7, 1.0),
    
    .window_active_border = lk_color(0.0, 0.0, 0.0, 1.0),
    .window_active_titlebar = lk_color(0.1, 0.1, 0.1, 1.0),
    .window_active_titlebar_text = lk_color(1.0, 1.0, 1.0, 1.0),
    .window_inactive_border = lk_color(0.9, 0.9, 0.9, 1.0),
    .window_inactive_titlebar = lk_color(1.0, 1.0, 1.0, 1.0),
    .window_inactive_titlebar_text = lk_color(0.5, 0.5, 0.5, 1.0),
        
    .panel_border = lk_color(0.4, 0.4, 0.4, 1.0),
    .panel_fill = lk_color(0.5, 0.5, 0.5, 1.0),
    .panel_text = lk_color(0.0, 0.0, 0.0, 1.0)
};

/**
 * The default theme to fall back to.
 */
lk_theme LK_DEFAULT_THEME = {
    .color_scheme = DEFAULT_COLORS,
    .border_width = 3,
    .titlebar_height = 24
};

#endif
