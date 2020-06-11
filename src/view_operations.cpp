#include "include/view_operations.hpp"

/**
 * TODO: Move to lk_view::request_operation(enum lk_cursor_mode mode, uint32_t edges)
 */
void view_request_operation(lk_view *view, enum lk_cursor_mode mode, uint32_t edges) {
    /* This function sets up an interactive move or resize operation, where the
     * compositor stops propegating pointer events to clients and instead
     * consumes them itself, to move or resize windows. */
    lk_server *server = view->server;
    struct wlr_surface *focused_surface =
            server->seat->pointer_state.focused_surface;
    if (view->xdg_surface->surface != focused_surface) {
        /* Deny move/resize requests from unfocused clients. */
        return;
    }
    server->grabbed_view = view;
    server->has_grabbed_view = true;
    server->cursor_mode = mode;

    if (mode == LK_CURSOR_MOVE) {
        view_move(server, view);
    } else {
        view_resize(server, view, edges);
    }
}

void view_request_move(struct wl_listener *listener, void *data) {
    /* This event is raised when a client would like to begin an interactive
     * move, typically because the user clicked on their client-side
     * decorations. Note that a more sophisticated compositor should check the
     * provied serial against a list of button press serials sent to this
     * client, to prevent the client from requesting this whenever they want. */
    lk_view *view = wl_container_of(listener, view, request_move);
    view_request_operation(view, LK_CURSOR_MOVE, 0);
}

void view_request_resize(struct wl_listener *listener, void *data) {
    /* This event is raised when a client would like to begin an interactive
     * resize, typically because the user clicked on their client-side
     * decorations. Note that a more sophisticated compositor should check the
     * provied serial against a list of button press serials sent to this
     * client, to prevent the client from requesting this whenever they want. */
    auto event = (struct wlr_xdg_toplevel_resize_event *)data;
    lk_view *view = wl_container_of(listener, view, request_resize);
    view_request_operation(view, LK_CURSOR_RESIZE, event->edges);
}

/**
 * TODO: Make into lk_view::move(), because
 * the server can be accessed through lk_view->server-> anyway.
 */
void view_move(lk_server *server, lk_view *view) {
    server->grab_x = server->cursor->x - view->x;
    server->grab_y = server->cursor->y - view->y;
}

/**
 * TODO: Same as above: lk_view::resize(uint32_t edges)
 */
void view_resize(lk_server *server, lk_view *view, uint32_t edges) {
    struct wlr_box geo_box;
    wlr_xdg_surface_get_geometry(view->xdg_surface, &geo_box);

    double border_x = (view->x + geo_box.x) + ((edges & WLR_EDGE_RIGHT) ? geo_box.width : 0);
    double border_y = (view->y + geo_box.y) + ((edges & WLR_EDGE_BOTTOM) ? geo_box.height : 0);
    server->grab_x = server->cursor->x - border_x;
    server->grab_y = server->cursor->y - border_y;

    server->grab_geobox = geo_box;
    server->grab_geobox.x += view->x;
    server->grab_geobox.y += view->y;

    server->resize_edges = edges;
}

