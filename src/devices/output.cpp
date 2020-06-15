#include "../include/devices/output.hpp"

void lk_output::render_rect(struct wlr_box *box, lk_color *color, float scale) {
    struct wlr_renderer *renderer = wlr_backend_get_renderer(this->wlr_output->backend);

    struct wlr_box box_scaled;
    scale_box(box, &box_scaled, scale);

    float color_array[4];
    color->into_array(color_array);
    wlr_render_rect(renderer, &box_scaled, color_array, this->wlr_output->transform_matrix);
}

void lk_output::render_rect_outline(struct wlr_box *box, lk_color *color, float width, float scale) {    
    struct wlr_box edge;
    memcpy(&edge, box, sizeof(struct wlr_box));
    
    // Top
    edge.height = width;
    render_rect(&edge, color, scale);

    // Bottom
    edge.y = edge.y + box->height - width;
    render_rect(&edge, color, scale);
    
    // Left
    memcpy(&edge, box, sizeof(struct wlr_box));
    edge.width = width;
    render_rect(&edge, color, scale);

    // Right
    edge.x = edge.x + box->width - width;
    render_rect(&edge, color, scale);
}

void lk_output::scale_box(wlr_box *box, wlr_box *scaled_box, float scale) {
    scaled_box->x = static_cast<int>(box->x * scale);
    scaled_box->y = static_cast<int>(box->y * scale);
    scaled_box->width = static_cast<int>(box->width * scale);
    scaled_box->height = static_cast<int>(box->height * scale);
}

void lk_output::scale_box(wlr_box *box, wlr_box *scaled_box) {
    this->scale_box(box, scaled_box, this->wlr_output->scale);
}
