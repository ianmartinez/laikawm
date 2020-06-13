#include "../include/xwayland/xwayland_view.hpp"

#include <float.h>

lk_view_constraints lk_xwayland_view::get_constraints() {
    double min_width, min_height, max_width, max_height;
    auto surface = this->wlr_xwayland_surface;
    auto size_hints = surface->size_hints;

    if (size_hints != NULL) {
        min_width = (size_hints->min_width > 0) ? size_hints->min_width : DBL_MIN;
        max_width = (size_hints->max_width > 0) ? size_hints->max_width : DBL_MAX;
        min_height = (size_hints->min_height > 0) ? size_hints->min_height : DBL_MIN;
        max_height = (size_hints->max_height > 0) ? size_hints->max_height : DBL_MAX;
    } else {
        min_width = DBL_MIN;
        max_width = DBL_MAX;
        min_height = DBL_MIN;
        max_height = DBL_MAX;
    }

    return lk_view_constraints {
        .min_width = min_width,
        .min_height = min_height,
        .max_width = max_width,
        .max_height = max_height
    };
}
