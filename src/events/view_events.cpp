#include "../include/events/view_events.hpp"

void view_request_move(struct wl_listener *listener, void *data) {
    /* This event is raised when a client would like to begin an interactive
     * move, typically because the user clicked on their client-side
     * decorations. Note that a more sophisticated compositor should check the
     * provied serial against a list of button press serials sent to this
     * client, to prevent the client from requesting this whenever they want. */
    lk_view *view = wl_container_of(listener, view, request_move);
    view->request_cursor_operation(LK_CURSOR_MOVE, 0);
}

void view_request_resize(struct wl_listener *listener, void *data) {
    /* This event is raised when a client would like to begin an interactive
     * resize, typically because the user clicked on their client-side
     * decorations. Note that a more sophisticated compositor should check the
     * provied serial against a list of button press serials sent to this
     * client, to prevent the client from requesting this whenever they want. */
    auto event = (struct wlr_xdg_toplevel_resize_event *)data;
    lk_view *view = wl_container_of(listener, view, request_resize);
    view->request_cursor_operation(LK_CURSOR_RESIZE, event->edges);
}
