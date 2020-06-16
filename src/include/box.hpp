#ifndef LK_BOX_H
#define LK_BOX_H

#include "wl_includes.hpp"

void scale_box(wlr_box *box, wlr_box *scaled_box, float scale);
void grow_box_sides(struct wlr_box *box, int l, int r, int t, int b);
void grow_box_all_sides(struct wlr_box *box, int value);
void grow_box_sides_lr_tb(struct wlr_box *box, int lr, int tb);

#endif
