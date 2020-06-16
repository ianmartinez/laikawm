#include "include/box.hpp"

/**
 * Scale all dimensions of a box by a fixed value.
 */
void scale_box(wlr_box *box, wlr_box *scaled_box, float scale) {
    scaled_box->x = static_cast<int>(box->x * scale);
    scaled_box->y = static_cast<int>(box->y * scale);
    scaled_box->width = static_cast<int>(box->width * scale);
    scaled_box->height = static_cast<int>(box->height * scale);
}

/**
 * Grow a box's sides from the left, right, top, and bottom.
 */
void grow_box_sides(struct wlr_box *box, int l, int r, int t, int b) {
    box->x -= l;
    box->width += l + r;
    box->y -= t;
    box->height += t + b;
}

/**
 * Grow a box from all sides with a constant value.
 */
void grow_box_all_sides(struct wlr_box *box, int value) {
    grow_box_sides(box, value, value, value, value);
}

/**
 * Grow a box's sides, with left and right the same value and
 * top and bottom the same value.
 */
void grow_box_sides_lr_tb(struct wlr_box *box, int lr, int tb) {
    grow_box_sides(box, lr, lr, tb, tb);
}
